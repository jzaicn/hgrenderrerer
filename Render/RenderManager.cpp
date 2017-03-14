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

}

void RenderManager::startRenderCore()
{

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