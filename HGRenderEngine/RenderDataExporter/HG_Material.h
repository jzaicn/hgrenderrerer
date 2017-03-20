#pragma once
#include "HG_BaseModel.h"
class HG_Material
{
public:
	HG_Material(void);
	~HG_Material(void);

private:
	EH_Material* create();

public:
	void saveTo(_Out_ EH_Material& material);
	void loadFrom(const EH_Material& material);

private:
	GETSET(EH_Material*,material);

	//�������
	GETSET(bool,backface_cull);			

	//������
	GETSET(float,diffuse_weight);
	GETSET_VECTYPE(EH_RGB,diffuse_color);
	GETSET(CString,diffuse_tex);	
	GETSET(float,diffuse_tex_repeat);	
	GETSET(float,roughness);
	GETSET(float,backlight);

	//���淴��
	GETSET(float,specular_weight);
	GETSET_VECTYPE(EH_RGB,specular_color);
	GETSET(CString,specular_tex);	
	GETSET(float,specular_tex_repeat);	
	GETSET(float,glossiness);
	GETSET(float,specular_fresnel);
	GETSET(float,anisotropy);
	GETSET(float,rotation);

	//͸��
	GETSET(float,transp_weight);		
	GETSET(bool,transp_invert_weight);
	GETSET(CString,transp_tex);		
	GETSET(float,transp_tex_repeat);	

	//����
	GETSET(float,bump_weight);
	GETSET(CString,bump_tex);		
	GETSET(float,bump_tex_repeat);		
	GETSET(bool,normal_bump);			

	//����
	GETSET(float,mirror_weight);
	GETSET_VECTYPE(EH_RGB,mirror_color);
	GETSET(float,mirror_fresnel);

	//����
	GETSET(float,refract_weight);
	GETSET(bool,refract_invert_weight);
	GETSET_VECTYPE(EH_RGB,refract_color);
	GETSET(float,ior);
	GETSET(float,refract_glossiness);



};

