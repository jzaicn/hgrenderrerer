#include "StdAfx.h"
#include "HG_Material.h"
#include <stdexcept>

HG_Material::HG_Material(void)
{
	set_backface_cull(false);

	set_diffuse_weight(0.5);
	clear_diffuse_color();
	set_diffuse_tex("");
	set_diffuse_tex_repeat(1.0);
	set_roughness(0.0);
	set_backlight(0.0);

	set_specular_weight(1.0);
	clear_specular_color();
	set_specular_tex("");	
	set_specular_tex_repeat(1.0);	
	set_glossiness(0.0);
	set_specular_fresnel(0.0);
	set_anisotropy(0.0);
	set_rotation(0.0);


	set_transp_weight(1.0);		
	set_transp_invert_weight(false);
	set_transp_tex("");		
	set_transp_tex_repeat(1.0);	


	set_bump_weight(1.0);
	set_bump_tex("");		
	set_bump_tex_repeat(1.0);		
	set_normal_bump(true);			


	set_mirror_weight(1.0);
	clear_mirror_color();
	set_mirror_fresnel(0.0);


	set_refract_weight(1.0);
	set_refract_invert_weight(0.0);
	clear_refract_color();
	set_ior(0.0);
	set_refract_glossiness(0.0);

	set_material(create());
}


HG_Material::~HG_Material(void)
{
	if (get_material())
	{
		free(get_material());
		set_material(NULL);
	}
}

EH_Material* HG_Material::create()
{
	EH_Material* material = (EH_Material*)(malloc(sizeof(EH_Material)));
	if (!material)
	{
		throw std::runtime_error("EH_Material ´´½¨Ê§°Ü");
	}
	saveTo(*material);
	return material;

}

void HG_Material::saveTo(_Out_ EH_Material& material)
{
	material.backface_cull = get_backface_cull();

	material.diffuse_weight = get_diffuse_weight();
	get_diffuse_color(material.diffuse_color);
	material.diffuse_tex = get_diffuse_tex().GetBuffer();
	material.diffuse_tex_repeat = get_diffuse_tex_repeat();
	material.roughness = get_roughness();
	material.backlight = get_backlight();

	material.specular_weight = get_specular_weight();
	get_specular_color(material.specular_color);
	material.specular_tex = get_specular_tex().GetBuffer();	
	material.specular_tex_repeat = get_specular_tex_repeat();	
	material.glossiness = get_glossiness();
	material.specular_fresnel = get_specular_fresnel();
	material.anisotropy = get_anisotropy();
	material.rotation = get_rotation();


	material.transp_weight = get_transp_weight();		
	material.transp_invert_weight = get_transp_invert_weight();
	material.transp_tex = get_transp_tex().GetBuffer();		
	material.transp_tex_repeat = get_transp_tex_repeat();	


	material.bump_weight = get_bump_weight();
	material.bump_tex = get_bump_tex().GetBuffer();		
	material.bump_tex_repeat = get_bump_tex_repeat();		
	material.normal_bump = get_normal_bump();			


	material.mirror_weight = get_mirror_weight();
	get_mirror_color(material.mirror_color);
	material.mirror_fresnel = get_mirror_fresnel();


	material.refract_weight = get_refract_weight();
	material.refract_invert_weight = get_refract_invert_weight();
	get_refract_color(material.refract_color);
	material.ior = get_ior();
	material.refract_glossiness = get_refract_glossiness();
}

void HG_Material::loadFrom(const EH_Material& material)
{
	set_backface_cull(material.backface_cull);

	set_diffuse_weight(material.diffuse_weight);
	set_diffuse_color(material.diffuse_color);
	set_diffuse_tex(material.diffuse_tex);
	set_diffuse_tex_repeat(material.diffuse_tex_repeat);
	set_roughness(material.roughness);
	set_backlight(material.backlight);

	set_specular_weight(material.specular_weight);
	set_specular_color(material.specular_color);
	set_specular_tex(material.specular_tex);	
	set_specular_tex_repeat(material.specular_tex_repeat);	
	set_glossiness(material.glossiness);
	set_specular_fresnel(material.specular_fresnel);
	set_anisotropy(material.anisotropy);
	set_rotation(material.rotation);


	set_transp_weight(material.transp_weight);		
	set_transp_invert_weight(material.transp_invert_weight);
	set_transp_tex(material.transp_tex);		
	set_transp_tex_repeat(material.transp_tex_repeat);	


	set_bump_weight(material.bump_weight);
	set_bump_tex(material.bump_tex);		
	set_bump_tex_repeat(material.bump_tex_repeat);		
	set_normal_bump(material.normal_bump);			


	set_mirror_weight(material.mirror_weight);
	set_mirror_color(material.mirror_color);
	set_mirror_fresnel(material.mirror_fresnel);


	set_refract_weight(material.refract_weight);
	set_refract_invert_weight(material.refract_invert_weight);
	set_refract_color(material.refract_color);
	set_ior(material.ior);
	set_refract_glossiness(material.refract_glossiness);
}

