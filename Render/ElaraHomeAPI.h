/**************************************************************************
 * Copyright (C) 2017 Rendease Co., Ltd.
 * All rights reserved.
 *
 * This program is commercial software: you must not redistribute it 
 * and/or modify it without written permission from Rendease Co., Ltd.
 *
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * End User License Agreement for more details.
 *
 * You should have received a copy of the End User License Agreement along 
 * with this program.  If not, see <http://www.rendease.com/licensing/>
 *************************************************************************/

#pragma once

/** This file includes a set of APIs to simplify integrating Elara 
 * renderer for interior design software.
 * It should be straightforward to port the implementation of this 
 * API to any programming language.
 */

/* Extern "C" */
#ifdef __cplusplus
#	define EH_EXTERN extern "C"
#else
#	define EH_EXTERN extern
#endif

/* Exporting and importing */
/* EI_HOME_EXPORTS must NOT be defined by users */
#ifdef _MSC_VER
#	if defined ELARA_HOME_EXPORTS
#		define EH_XAPI	__declspec(dllexport)
#	else
#		define EH_XAPI	__declspec(dllimport)
#	endif
#else
#	define EH_XAPI		__attribute__((visibility("default")))
#endif
//E#define EH_API EH_EXTERN EH_XAPI
#define EH_API EH_EXTERN 



/* Data types */
#ifndef uint_t
typedef unsigned int uint_t;
#define uint_t uint_t
#endif

typedef float EH_RGB[3];
typedef float EH_RGBA[4];
typedef float EH_Vec[3];
typedef float EH_Vec2[2];
typedef float EH_Mat[16];



/** Log message Severity
 */
enum EH_Severity
{
	EH_INFO = 0, 
	EH_WARNING, 
	EH_ERROR, 
	EH_FATAL, 
	EH_DEBUG
};

/** Render quality presets
 */
enum EH_RenderQuality
{
	EH_MEDIUM = 0,		/**< medium quality good for most situations */
	EH_FAST,			/**< very fast preview rendering */
	EH_HIGH,			/**< super high quality rendering but slow */
};

/** Light types.
 */
enum EH_LightType
{
	EH_LIGHT_PORTAL = 0,		/**< Sky portal to be added outside window */
	EH_LIGHT_QUAD,				/**< rectangular light */
	EH_LIGHT_SPHERE,			/**< spherical light */
	EH_LIGHT_IES,				/**< Light with IES distribution */
};



/** A utility for converting UTF-16 string into UTF-8, because Elara 
 * only accepts UTF-8 strings.
 * The caller is responsible for free'ing the returned string.
 */
EH_API char *EH_utf16_to_utf8(const wchar_t *str);

/** A utility function to convert the arguments of command line into 
 * UTF-8, such that Elara can correctly handle file path.
 */
EH_API void EH_convert_native_arguments(int argc, const char *argv[]);



/** The exporting context.
 */
typedef void * EH_Context;

/** Create exporting context, initialize its parameters.
 */
EH_API EH_Context *EH_create();

/** Delete exporting context, free all of its resources.
 */
EH_API void EH_delete(EH_Context *ctx);



/** The exporting options for user to fill
 */
struct EH_ExportOptions
{
	bool base85_encoding;	/**< Use Base85 encoding? */
	bool left_handed;		/**< Is source data in left-handed space? */
};

/** Begin exporting, set options which are effective 
 * during the exporting process.
 * \param filename The ESS filename to create.
 * \param opt The export options
 */
EH_API void EH_begin_export(EH_Context *ctx, const char *filename, const EH_ExportOptions *opt);
/** End exporting, clean up resources only valid during 
 * the exporting process.
 */
EH_API void EH_end_export();


/** The callback to log messages during exporting.
 */
typedef void (*EH_LogCallback)(EH_Severity severity, const char *msg);
/** The callback to update exporting progress. To cancel 
 * the exporting process, return false for this function.
 */
typedef bool (*EH_ProgressCallback)(float progress);

/** Set log callback.
 */
void EH_set_log_callback(EH_Context *ctx, EH_LogCallback cb);
/** Set progress callback.
 */
void EH_set_progress_callback(EH_Context *ctx, EH_ProgressCallback cb);



/** The render options for user to fill
 */
struct EH_RenderOptions
{
	EH_RenderQuality quality;
};

/** Set current render options.
 */
EH_API void EH_set_render_options(EH_Context *ctx, const EH_RenderOptions *opt);



/** The camera data for user to fill
 */
struct EH_Camera
{
	float fov;
	float near_clip;
	float far_clip;
	unsigned image_width;
	uint_t image_height;
	EH_Mat view_to_world;	/**< View to world transform matrix */
	bool cubemap_render;	/**< Render a 6x1 cubemap? */
};

/** Set current camera to render.
 */
EH_API void EH_set_camera(EH_Context *ctx, const EH_Camera *cam);



/** The triangle mesh data for user to fill
 */
struct EH_Mesh
{
	uint_t num_verts;
	uint_t num_faces;
	const EH_Vec *verts;
	const EH_Vec *normals;
	const EH_Vec2 *uvs;
	const uint_t *face_indices;		/** Should have (num_faces * 3) indices */
};

/** Add a triangle mesh to the scene.
 * \param name The name of the mesh
 * \param The mesh data
 */
EH_API void EH_add_mesh(EH_Context *ctx, const char *name, const EH_Mesh *mesh);



/** The material data for user to fill
 */
struct EH_Material
{
	bool backface_cull;			/**< Use backface cull? */

	/* Diffuse layer */
	float diffuse_weight;
	EH_RGB diffuse_color;		/**< Diffuse color */
	const char *diffuse_tex;	/**< The filename of diffuse texture */
	float diffuse_tex_repeat;	/**< The repeat scale of diffuse texture */
	float roughness;
	float backlight;

	/* Specular layer */
	float specular_weight;
	EH_RGB specular_color;	/**< Specular color */
	const char *specular_tex;	/**< The filename of specular texture */
	float specular_tex_repeat;	/**< The repeat scale of specular texture */
	float glossiness;
	float specular_fresnel;
	float anisotropy;
	float rotation;

	/* Transparency layer */
	float transp_weight;		/**< Transparency weight */
	bool transp_invert_weight;
	const char *transp_tex;		/**< The filename of transparency texture */
	float transp_tex_repeat;	/**< The repeat scale of transparency texture */

	/* Bump mapping */
	float bump_weight;
	const char *bump_tex;		/**< The texture for bump mapping */
	float bump_tex_repeat;		/**< The repeat scale of bump texture */
	bool normal_bump;			/**< The bump texture is actually a normal map? */

	/* Mirror layer */
	float mirror_weight;
	EH_RGB mirror_color;
	float mirror_fresnel;

	/* Refraction layer */
	float refract_weight;
	bool refract_invert_weight;
	EH_RGB refract_color;
	float ior;
	float refract_glossiness;
};

/** Add a material to the scene.
 * \param name The name of the material.
 * \param mtl The material data.
 */
EH_API void EH_add_material(EH_Context *ctx, const char *name, const EH_Material *mtl);



/** The mesh instance data for user to fill
 */
struct EH_MeshInstance
{
	const char *mesh_name;	/**< The name of the mesh which we reference to */
	EH_Mat mesh_to_world;	/**< Mesh local space to world space transform */
	const char *mtl_name;	/**< The name of the material which we reference to */
};

/** Instance a mesh into the scene.
 * \param name The name of the mesh instance
 * \param The mesh instance data
 */
EH_API void EH_add_mesh_instance(EH_Context *ctx, const char *name, const EH_MeshInstance *inst);



/** The light data for user to fill
 */
struct EH_Light
{
	EH_LightType type;
	const char *ies_filename;	/**< Only used for IES light type */
	float intensity;
	EH_Vec2 size;				/**< Use size[0] as radius for sphere light, 
									 Use size[0] as width and use size[0] as 
									 height for quad light */
	EH_Mat light_to_world;		/**< Light local space to world space transform */
};

/** Add a light to the scene.
 * \param name The name of the light
 * \param lgt The light data.
 */
EH_API void EH_add_light(EH_Context *ctx, const char *name, const EH_Light *lgt);



/** The sky data for user to fill
 */
struct EH_Sky
{
	bool enabled;
	float intensity;
	const char *hdri_name;
	float hdri_rotation;
};

/** Set the current sky environment.
 */
EH_API void EH_set_sky(EH_Context *ctx, const EH_Sky *sky);



/** The sun data for user to fill
 */
struct EH_Sun
{
	bool enabled;
	float intensity;
	EH_RGB color;
	float soft_shadow;
	EH_Vec2 dir;			/**< dir[0] is theta angle, 
							     dir[1] is phi angle, both in radians */
};

/** Set the current sun parameters.
 */
EH_API void EH_set_sun(EH_Context *ctx, const EH_Sun *sun);

