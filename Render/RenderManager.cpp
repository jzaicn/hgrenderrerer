#include "StdAfx.h"
#include "RenderManager.h"
//#include "HgLog/HgLog.h"
#include "ei.h"
#include "ei_timer.h"
#include "ei_dataflowx.h"
#include "ei_base_bucket.h"

RenderManager* RenderManager::render = NULL;
#define MSG_QUEUE_WAIT_TIME		50

RenderManager::RenderManager(void)
{
}


RenderManager::~RenderManager(void)
{
}

RenderManager& RenderManager::getInstance()
{
	if (!render)
	{
		render = new RenderManager();
		if (!render)
		{
			throw std::runtime_error("创建管理器失败");
		}
	}
	return *render;
}

void RenderManager::saveImage(CString path)
{
	
}

//////////////////////////////////////////////////////////////////////////
// 导出ess文件

void RenderManager::saveESS(CString path)
{
	EH_begin_export(m_core.get_renderContext(),path.GetBuffer(),m_exportOptions.get_exportOption());
}

void RenderManager::breakSaveESS()
{
	EH_end_export();
}


void RenderManager::initialRenderCore()
{
	
}



//////////////////////////////////////////////////////////////////////////
// 操作控制

struct RenderManager::RenderProcess
{
	eiProcess					base;
	eiThreadHandle				renderThread;
	eiRWLock					*bufferLock;
	std::vector<eiColor>		originalBuffer;
	eiInt						imageWidth;
	eiInt						imageHeight;
	eiRenderParameters			*render_params;
	eiBool						interactive;
	eiBool						progressive;
	eiBool						target_set;
	eiVector					up_vector;
	eiVector					camera_target;
	eiScalar					min_target_dist;
	eiScalar					last_job_percent;
	eiTimer						first_pixel_timer;
	eiBool						is_first_pass;

	RenderProcess(
		eiInt res_x, 
		eiInt res_y, 
		eiRenderParameters *_render_params, 
		eiBool _interactive, 
		eiBool _progressive)
	{
		init_callbacks();
		renderThread = NULL;
		bufferLock = ei_create_rwlock();
		imageWidth = res_x;
		imageHeight = res_y;
		render_params = _render_params;
		interactive = _interactive;
		progressive = _progressive;
		target_set = EI_FALSE;
		up_vector = ei_vector(0.0f, 0.0f, 1.0f);
		camera_target = 0.0f;
		min_target_dist = 0.0f;
		last_job_percent = 0.0f;
		const eiColor blackColor = ei_color(0.0f);
		originalBuffer.resize(imageWidth * imageHeight, blackColor);
	}

	~RenderProcess()
	{
		ei_delete_rwlock(bufferLock);
	}

	static void rprocess_pass_started(eiProcess *process, eiInt pass_id)
	{
	}	
	
	static void rprocess_pass_finished(eiProcess *process, eiInt pass_id)
	{
		RenderProcess *rp = (RenderProcess *)process;

		if (rp->is_first_pass)
		{
			ei_timer_stop(&(rp->first_pixel_timer));
			printf("Time to first pass: %d ms\n", rp->first_pixel_timer.duration);
			rp->is_first_pass = EI_FALSE;
		}
	}

	static void rprocess_info(
		eiProcess *process, 
		const char *text)
	{
	}
	
	
	//const eiInt TARGET_LEN = 4;
	static eiColor whiteColor()
	{
		eiColor whiteColor = {1.0f, 1.0f, 1.0f};
		return whiteColor;
	}
	#define TARGET_LEN  4

	static void rprocess_job_started(
		eiProcess *process, 
		const eiTag job, 
		const eiThreadID threadId)
	{
		RenderProcess *rp = (RenderProcess *)process;

		if (rp->progressive)
		{
			return;
		}

		if (ei_db_type(job) != EI_TYPE_JOB_BUCKET)
		{
			return;
		}

		eiDataAccessor<eiBucketJob> pJob(job);
		if (pJob->pass_id <= EI_PASS_GI_CACHE_PROGRESSIVE)
		{
			return;
		}

		const eiInt left = pJob->rect.left;
		const eiInt right = pJob->rect.right;
		const eiInt top = pJob->rect.top;
		const eiInt bottom = pJob->rect.bottom;
		const eiInt imageWidth = rp->imageWidth;
		const eiInt imageHeight = rp->imageHeight;
		eiColor *originalBuffer = &(rp->originalBuffer[0]);
		ei_read_lock(rp->bufferLock);
		{
			for (eiInt j = left; j < left + TARGET_LEN; ++j)
			{
				originalBuffer[(imageHeight - 1 - top) * imageWidth + j] = whiteColor();
				originalBuffer[(imageHeight - 1 - bottom) * imageWidth + j] = whiteColor();
			}
			for (eiInt j = right; j > right - TARGET_LEN; --j)
			{
				originalBuffer[(imageHeight - 1 - top) * imageWidth + j] = whiteColor();
				originalBuffer[(imageHeight - 1 - bottom) * imageWidth + j] = whiteColor();
			}
			for (eiInt j = top; j < top + TARGET_LEN; ++j)
			{
				originalBuffer[(imageHeight - 1 - j) * imageWidth + left] = whiteColor();
				originalBuffer[(imageHeight - 1 - j) * imageWidth + right] = whiteColor();
			}
			for (eiInt j = bottom; j > bottom - TARGET_LEN; --j)
			{
				originalBuffer[(imageHeight - 1 - j) * imageWidth + left] = whiteColor();
				originalBuffer[(imageHeight - 1 - j) * imageWidth + right] = whiteColor();
			}
		}
		ei_read_unlock(rp->bufferLock);
	}

	static void rprocess_job_finished(
		eiProcess *process, 
		const eiTag job, 
		const eiInt job_state, 
		const eiThreadID threadId)
	{
		RenderProcess *rp = (RenderProcess *)process;

		if (ei_db_type(job) != EI_TYPE_JOB_BUCKET)
		{
			return;
		}

		eiDataAccessor<eiBucketJob> pJob(job);
		if (job_state == EI_JOB_CANCELLED)
		{
			return;
		}

		if (pJob->pass_id <= EI_PASS_GI_CACHE_PROGRESSIVE)
		{
			eiInt GI_cache_samples = (EI_PASS_GI_CACHE_PROGRESSIVE + 1) - pJob->pass_id;
			if ((GI_cache_samples % 4) != 0)
			{
				return;
			}
		}

		eiFrameBufferCache	infoFrameBufferCache;
		eiFrameBufferCache	colorFrameBufferCache;

		ei_framebuffer_cache_init(
			&infoFrameBufferCache, 
			pJob->infoFrameBuffer, 
			pJob->pos_i, 
			pJob->pos_j, 
			pJob->point_spacing, 
			pJob->pass_id, 
			NULL);
		ei_framebuffer_cache_init(
			&colorFrameBufferCache, 
			pJob->colorFrameBuffer, 
			pJob->pos_i, 
			pJob->pos_j, 
			pJob->point_spacing, 
			pJob->pass_id, 
			&infoFrameBufferCache);

		const eiRect4i & fb_rect = infoFrameBufferCache.m_rect;

		/* write bucket updates into the original buffer */
		const eiInt imageWidth = rp->imageWidth;
		const eiInt imageHeight = rp->imageHeight;
		eiColor *originalBuffer = &(rp->originalBuffer[0]);
		originalBuffer += ((imageHeight - 1 - pJob->rect.top) * imageWidth + pJob->rect.left);
		ei_read_lock(rp->bufferLock);
		{
			for (eiInt j = fb_rect.top; j < fb_rect.bottom; ++j)
			{
				for (eiInt i = fb_rect.left; i < fb_rect.right; ++i)
				{
					ei_framebuffer_cache_get_final(
						&colorFrameBufferCache, 
						i, 
						j, 
						&(originalBuffer[i - fb_rect.left]));
				}
				originalBuffer -= imageWidth;
			}
		}
		ei_read_unlock(rp->bufferLock);

		ei_framebuffer_cache_exit(&colorFrameBufferCache);
		ei_framebuffer_cache_exit(&infoFrameBufferCache);
	}

	void init_callbacks()
	{
		base.pass_started = rprocess_pass_started;
		base.pass_finished = rprocess_pass_finished;
		base.job_started = rprocess_job_started;
		base.job_finished = rprocess_job_finished;
		base.info = rprocess_info;
	}

	void update_render_view(eiInt frameWidth, eiInt frameHeight)
	{
		eiInt cropWidth = imageWidth;
		eiInt cropHeight = imageHeight;
		eiInt offsetX = 0;
		if (frameWidth > imageWidth)
		{
			offsetX = (frameWidth - imageWidth) / 2;
		}
		eiInt offsetY = 0;
		if (frameHeight > imageHeight)
		{
			offsetY = (frameHeight - imageHeight) / 2;
		}
		offsetY = frameHeight - (offsetY + imageHeight);
		const eiColor *pixels = &(originalBuffer[0]);
		if (offsetY < 0)
		{
			pixels += (-offsetY * imageWidth);
			cropHeight -= (-offsetY);
			offsetY = 0;
		}
		ei_display_clear_viewport(frameWidth, frameHeight);
		ei_write_lock(bufferLock);
		{
			ei_display_draw_pixels(offsetX, offsetY, cropWidth, cropHeight, pixels);
		}
		ei_write_unlock(bufferLock);
	}
};

EI_THREAD_FUNC RenderManager::render_callback(void *param)
{
	eiRenderParameters *render_params = (eiRenderParameters *)param;

	ei_job_register_thread();

	ei_render_run(render_params->root_instgroup, render_params->camera_inst, render_params->options);

	ei_job_unregister_thread();

	return (EI_THREAD_FUNC_RESULT)EI_TRUE;
}

void RenderManager::display_callback(eiInt frameWidth, eiInt frameHeight, void *param)
{
	RenderProcess *rp = (RenderProcess *)param;

	ei_sleep(MSG_QUEUE_WAIT_TIME);

// 	if (rp->interactive)
// 	{
// 		eiScalar offset[2];
// 		eiInt drag_button;
// 		eiInt drag_mode = ei_display_get_mouse_move(offset, &drag_button);
// 
// 		if (drag_mode == EI_DRAG_MODE_NONE)
// 		{
// 			ei_display_get_scroll_offset(offset);
// 			offset[0] *= -20.0f;
// 			offset[1] *= -20.0f;
// 			drag_mode = EI_DRAG_MODE_SHIFT;
// 			drag_button = EI_DRAG_BUTTON_LEFT;
// 		}
// 
// 		if (drag_mode != EI_DRAG_MODE_NONE && 
// 			drag_button != EI_DRAG_BUTTON_RIGHT && 
// 			(offset[0] != 0.0f || offset[1] != 0.0f))
// 		{
// 			if (rp->renderThread != NULL) /* is rendering */
// 			{
// 				/* cancel current rendering */
// 				ei_job_abort(EI_TRUE);
// 				ei_wait_thread(rp->renderThread);
// 				ei_delete_thread(rp->renderThread);
// 				rp->renderThread = NULL;
// 
// 				ei_render_cleanup();
// 			}
// 
// 			/* modify viewport parameters */
// 			const char *cam_inst_name = rp->render_params->camera_inst;
// 			if (cam_inst_name != NULL)
// 			{
// 				eiBool need_init;
// 				eiNode *cam_inst = ei_edit_node(cam_inst_name, &need_init);
// 
// 				eiIndex xform_pid = ei_node_find_param(cam_inst, "transform");
// 				eiIndex motion_xform_pid = ei_node_find_param(cam_inst, "motion_transform");
// 				eiMatrix xform_val = *ei_node_get_matrix(cam_inst, xform_pid);
// 
// 				eiVector camera_pos = point_transform(ei_vector(0.0f, 0.0f, 0.0f), xform_val);
// 				eiVector cam_up = normalize(vector_transform(ei_vector(0.0f, 1.0f, 0.0f), xform_val));
// 				eiVector cam_right = normalize(vector_transform(ei_vector(1.0f, 0.0f, 0.0f), xform_val));
// 				eiVector cam_dir = normalize(vector_transform(ei_vector(0.0f, 0.0f, -1.0f), xform_val));
// 				if (!rp->target_set) /* initialize camera to align with original view */
// 				{
// 					eiVector abs_cam_up = ei_vector(absf(cam_up.x), absf(cam_up.y), absf(cam_up.z));
// 					eiInt up_axis = abs_cam_up.max_axis();
// 					rp->up_vector = 0.0f;
// 					rp->up_vector[up_axis] = sign(cam_up[up_axis]);
// 					printf("Up vector set to [%f %f %f]\n", rp->up_vector.x, rp->up_vector.y, rp->up_vector.z);
// 					eiVector obj_center = ei_vector(0.0f, 0.0f, 0.0f);
// 					/* use absolute value to ensure camera target is always in front of camera direction */
// 					eiScalar focal_dist = absf(point_plane_dist(camera_pos, -cam_dir, obj_center));
// 					printf("Initial focal distance: %f\n", focal_dist);
// 					rp->camera_target = camera_pos + cam_dir * focal_dist;
// 					rp->min_target_dist = 0.01f * dist(camera_pos, rp->camera_target);
// 					rp->target_set = EI_TRUE;
// 				}
// 				eiVector target_vec = camera_pos - rp->camera_target;
// 				eiScalar target_dist = normalize_len(target_vec, target_vec);
// 
// 				if ((drag_button == EI_DRAG_BUTTON_LEFT && drag_mode == EI_DRAG_MODE_CTRL) || 
// 					(drag_button == EI_DRAG_BUTTON_MIDDLE && drag_mode == EI_DRAG_MODE_NORMAL)) /* pan */
// 				{
// 					rp->camera_target += cam_right * (-0.001f * offset[0] * max(rp->min_target_dist, target_dist));
// 					rp->camera_target += cam_up * (0.001f * offset[1] * max(rp->min_target_dist, target_dist));
// 				}
// 				else if (drag_button == EI_DRAG_BUTTON_LEFT && drag_mode == EI_DRAG_MODE_SHIFT) /* zoom */
// 				{
// 					target_dist += 0.002f * offset[1] * max(rp->min_target_dist, target_dist);
// 				}
// 				else
// 				{
// 					/* make horizontal speed slower when approaching up vector */
// 					eiScalar horiz_speed = 1.0f - 0.7f * absf(dot(rp->up_vector, target_vec));
// 					target_vec = vector_transform(target_vec, rotate(radians(offset[0] * -0.2f * horiz_speed), cam_up));
// 					target_vec = vector_transform(target_vec, rotate(radians(offset[1] * -0.2f), cam_right));
// 				}
// 
// 				camera_pos = rp->camera_target + target_vec * target_dist;
// 				eiVector camera_dir_z = target_vec;
// 				eiVector camera_dir_x = cross(rp->up_vector, camera_dir_z);
// 				if (absf(dot(rp->up_vector, camera_dir_z)) > 0.99f) /* fix up vector precision issue */
// 				{
// 					eiVector fixed_up = cross(camera_dir_z, cam_right);
// 					camera_dir_x = cross(fixed_up, camera_dir_z);
// 				}
// 				if (dot(cam_right, camera_dir_x) < 0.0f) /* fix sudden flip when approaching up vector */
// 				{
// 					camera_dir_x = - camera_dir_x;
// 				}
// 				eiVector camera_dir_y = cross(camera_dir_z, camera_dir_x);
// 
// 				xform_val = ei_matrix(
// 					camera_dir_x.x, camera_dir_x.y, camera_dir_x.z, 0.0f, 
// 					camera_dir_y.x, camera_dir_y.y, camera_dir_y.z, 0.0f, 
// 					camera_dir_z.x, camera_dir_z.y, camera_dir_z.z, 0.0f, 
// 					camera_pos.x, camera_pos.y, camera_pos.z, 1.0f);
// 
// 				ei_node_set_matrix(cam_inst, xform_pid, &xform_val);
// 				ei_node_set_matrix(cam_inst, motion_xform_pid, &xform_val);
// 
// 				ei_end_edit_node(cam_inst);
// 			}
// 
// 			/* start a new rendering */
// 			ei_timer_reset(&(rp->first_pixel_timer));
// 			ei_timer_start(&(rp->first_pixel_timer));
// 			rp->is_first_pass = EI_TRUE;
// 			ei_render_prepare();
// 
// 			rp->renderThread = ei_create_thread(render_callback, rp->render_params, NULL);
// 			ei_set_low_thread_priority(rp->renderThread);
// 		}
// 	}

	if (!ei_job_aborted())
	{
		/* display render progress */
		const eiScalar job_percent = (eiScalar)ei_job_get_percent();
		if (absf(rp->last_job_percent - job_percent) >= 0.5f)
		{
			printf("Render progress: %.1f %% ...\n", job_percent);
			rp->last_job_percent = job_percent;
		}
	}

	rp->update_render_view(frameWidth, frameHeight);
}

void RenderManager::startRenderCore()
{
	bool ignore_render = true;
	bool display = true;
	bool interactive = false;
	bool force_render = false;
	bool resolution_overridden = false;

	int res_x = 800;
	int res_y = 600;

	CString filename = "E:\\HGRENDER\\Elara_SDK_1_0_76\\bin\\default.ess";

	if (!ei_parse2(filename, ignore_render || display || interactive || force_render))
	{
		ei_error("Failed to parse file: %s\n", filename);
		throw std::runtime_error("Failed to parse file");
	}

	eiRenderParameters render_params;
	memset(&render_params, 0, sizeof(render_params));
	eiBool get_render_params = EI_FALSE;
	get_render_params = ei_get_last_render_params(&render_params);

	if (display || interactive || force_render)
	{
		ei_info("Start display and rendering...\n");

		eiRenderParameters render_params;
		memset(&render_params, 0, sizeof(render_params));
		eiBool get_render_params = EI_FALSE;
// 		if (force_render)
// 		{
// 			strncpy(render_params.root_instgroup, force_render_root_name.c_str(), EI_MAX_NODE_NAME_LEN - 1);
// 			strncpy(render_params.camera_inst, force_render_cam_name.c_str(), EI_MAX_NODE_NAME_LEN - 1);
// 			strncpy(render_params.options, force_render_option_name.c_str(), EI_MAX_NODE_NAME_LEN - 1);
// 			get_render_params = EI_TRUE;
// 		}
// 		else
		{
			get_render_params = ei_get_last_render_params(&render_params);
		}
		if (!get_render_params)
		{
			ei_error("Cannot get last render parameters.\n");
		}
		else
		{
			eiTag cam_inst_tag = ei_find_node(render_params.camera_inst);
			if (cam_inst_tag != EI_NULL_TAG)
			{
				eiDataAccessor<eiNode> cam_inst(cam_inst_tag);
				eiTag cam_item_tag = ei_node_get_node(cam_inst.get(), ei_node_find_param(cam_inst.get(), "element"));
				if (cam_item_tag != EI_NULL_TAG)
				{
					eiDataAccessor<eiNode> cam_item(cam_item_tag);
					if (!resolution_overridden)//修改图像分辨率
					{
						res_x = ei_node_get_int(cam_item.get(), ei_node_find_param(cam_item.get(), "res_x"));
						res_y = ei_node_get_int(cam_item.get(), ei_node_find_param(cam_item.get(), "res_y"));
					}
					eiBool progressive = EI_FALSE;
					eiTag opt_item_tag = ei_find_node(render_params.options);
					if (opt_item_tag != EI_NULL_TAG)
					{
						eiDataAccessor<eiNode> opt_item(opt_item_tag);
						progressive = ei_node_get_bool(opt_item.get(), ei_node_find_param(opt_item.get(), "progressive"));
					}
// 					if (force_progressive || interactive)
// 					{
// 						progressive = EI_TRUE;
// 					}

					//核心运行类 
					RenderProcess rp(res_x, res_y, &render_params, interactive, progressive);

// 					if (interactive)
// 					{
// 						ei_verbose("warning");
// 
// 						if (ei_find_node(render_params.options) != EI_NULL_TAG)
// 						{
// 							eiBool need_init;
// 							eiNode *opt_node = ei_edit_node(render_params.options, &need_init);
// 
// 							ei_node_enum(opt_node, "accel_mode", "large");
// 
// 							eiInt max_samples = 1;
// 							eiIndex max_samples_pid = ei_node_find_param(opt_node, "max_samples");
// 							if (max_samples_pid != EI_NULL_TAG)
// 							{
// 								max_samples = ei_node_get_int(opt_node, max_samples_pid);
// 							}
// 							printf("AA samples: %d\n", max_samples);
// 
// 							eiInt diffuse_samples = 1;
// 							eiIndex diffuse_samples_pid = ei_node_find_param(opt_node, "diffuse_samples");
// 							if (diffuse_samples_pid != EI_NULL_TAG)
// 							{
// 								diffuse_samples = ei_node_get_int(opt_node, diffuse_samples_pid);
// 							}
// 							printf("Diffuse samples: %d\n", diffuse_samples);
// 
// 							eiInt sss_samples = 1;
// 							eiIndex sss_samples_pid = ei_node_find_param(opt_node, "sss_samples");
// 							if (sss_samples_pid != EI_NULL_TAG)
// 							{
// 								sss_samples = ei_node_get_int(opt_node, sss_samples_pid);
// 							}
// 							printf("SSS samples: %d\n", sss_samples);
// 
// 							eiInt volume_indirect_samples = 1;
// 							eiIndex volume_indirect_samples_pid = ei_node_find_param(opt_node, "volume_indirect_samples");
// 							if (volume_indirect_samples_pid != EI_NULL_TAG)
// 							{
// 								volume_indirect_samples = ei_node_get_int(opt_node, volume_indirect_samples_pid);
// 							}
// 							printf("Volume indirect samples: %d\n", volume_indirect_samples);
// 
// 							eiInt random_lights = 1;
// 							eiIndex random_lights_pid = ei_node_find_param(opt_node, "random_lights");
// 							if (random_lights_pid != EI_NULL_TAG)
// 							{
// 								random_lights = ei_node_get_int(opt_node, random_lights_pid);
// 							}
// 							printf("Random lights: %d\n", random_lights);
// 
// 							eiInt max_dist_samples = max(diffuse_samples, max(sss_samples, volume_indirect_samples));
// 							if (max_samples > 16)
// 							{
// 								max_samples *= max(1, max_dist_samples / (max_samples / 16));
// 							}
// 							else
// 							{
// 								max_samples *= max_dist_samples;
// 							}
// 
// 							printf("Interactive samples: %d\n", max_samples);
// 							ei_node_set_int(opt_node, max_samples_pid, max_samples);
// 
// 							ei_node_int(opt_node, "diffuse_samples", 1);
// 							ei_node_int(opt_node, "sss_samples", 1);
// 							ei_node_int(opt_node, "volume_indirect_samples", 1);
// 							if (random_lights <= 0 || random_lights > 16)
// 							{
// 								ei_node_int(opt_node, "random_lights", 16);
// 							}
// 							ei_node_bool(opt_node, "progressive", EI_TRUE);
// 
// 							ei_end_edit_node(opt_node);
// 						}
// 					}

					ei_job_set_process(&(rp.base));
					ei_timer_reset(&(rp.first_pixel_timer));
					ei_timer_start(&(rp.first_pixel_timer));
					rp.is_first_pass = EI_TRUE;
					ei_render_prepare();
					{
						rp.renderThread = ei_create_thread(render_callback, &render_params, NULL);
						ei_set_low_thread_priority(rp.renderThread);

						if (display)
						{
							ei_display(display_callback, &rp, res_x, res_y);
						}

						ei_wait_thread(rp.renderThread);
						ei_delete_thread(rp.renderThread);
						rp.renderThread = NULL;
					}
					ei_render_cleanup();
					ei_job_set_process(NULL);
				}
			}
		}

		ei_info("Finished display and rendering.\n");
	}
}


void RenderManager::pauseRenderCore()
{

}

void RenderManager::stopRenderCore()
{

}

void RenderManager::useRenderOption()
{

}

//////////////////////////////////////////////////////////////////////////
// 设置资源
#if 1
// 添加摄像机到场景中
void RenderManager::useCamera()
{
	for (UINT i = (UINT)m_camera.size() - 1; i >= 0 ; i--)
	{
		HG_Camera camera = m_camera.at(i);
		EH_set_camera(m_core.get_renderContext(),camera.get_camera());
	}
}

// 添加场景中所有mesh实例
void RenderManager::useMesh()
{
	for (auto it = m_mesh.begin() ; it!= m_mesh.end() ; ++it)
	{
		CString name = it->first;
		HG_Mesh mesh = it->second;
		EH_add_mesh(m_core.get_renderContext(),name.GetBuffer(),mesh.get_mesh());
	}
}
// 添加场景中所有材质实例
void RenderManager::useMaterial()
{
	for (auto it = m_material.begin() ; it!= m_material.end() ; ++it)
	{
		CString name = it->first;
		HG_Material material = it->second;
		EH_add_material(m_core.get_renderContext(),name.GetBuffer(),material.get_material());
	}
	
}
// 添加场景中所有mesh所在位置
void RenderManager::useMeshInstance()
{
	for (auto it = m_meshInstance.begin() ; it!= m_meshInstance.end() ; ++it)
	{
		CString name = it->first;
		HG_MeshInstance inst = it->second;
		EH_add_mesh_instance(m_core.get_renderContext(),name.GetBuffer(),inst.get_meshInstance());
	}
}

void RenderManager::useLight()
{
	for (auto it = m_light.begin() ; it!= m_light.end() ; ++it)
	{
		CString name = it->first;
		HG_Light light = it->second;
		EH_add_light(m_core.get_renderContext(),name.GetBuffer(),light.get_light());
	}
}

//设置天空
void RenderManager::useSky()
{
	for (UINT i = 0; i < m_sky.size() ; i++)
	{
		HG_Sky sky = m_sky.at(i);
		EH_set_sky(m_core.get_renderContext(),sky.get_sky());
	}
}

//设置天空
void RenderManager::useSun()
{
	for (UINT i = 0; i < m_sun.size() ; i++)
	{
		HG_Sun sun = m_sun.at(i);	
		EH_set_sun(m_core.get_renderContext(),sun.get_sun());
	}
}

#endif
//////////////////////////////////////////////////////////////////////////
// 设置关联句柄

#if 1
void RenderManager::initialRenderLog()
{
	EH_set_log_callback(m_core.get_renderContext(),(RenderManager::loggingCallBack));
}

void RenderManager::initialRenderProc()
{
	EH_set_progress_callback(m_core.get_renderContext(),(RenderManager::processingCallBack));
}

//////////////////////////////////////////////////////////////////////////
// 响应句柄

void RenderManager::loggingCallBack(EH_Severity severity, const char *msg)
{
	//HGLOG_DEBUG("level %d : %s",severity,msg);
	return;
}

bool RenderManager::processingCallBack(float progress)
{
	//HGLOG_DEBUG("processingCallBack %f",progress);
	return true;
}

#endif