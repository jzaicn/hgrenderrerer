#pragma once
#include "HG_BaseModel.h"

class HG_MeshTriangle :public HG_BaseModel
{
public:
	HG_MeshTriangle()
	{
		set_t1(0);
		set_t1(0);
		set_t1(0);
		set_material(-1);
	};
	HG_MeshTriangle(UINT t1,UINT t2,UINT t3,UINT material = -1)
	{
		set_t1(t1);
		set_t1(t2);
		set_t1(t3);
		set_material(material);
	};
public:
	GETSET(UINT,t1);				// ¶¥µãindex
	GETSET(UINT,t2);
	GETSET(UINT,t3);
	GETSET(UINT,material) ;			//²ÄÖÊindex
};

class HG_Mesh
{
public:
	HG_Mesh(void);
	~HG_Mesh(void);

private:
	GETSET(std::vector<HG_MeshTriangle>,faces);
	GETSET(std::vector<HG_Vec3>,verts);
	GETSET(std::vector<HG_Vec3>,normals);
	GETSET(std::vector<HG_Vec2>,uvs);
	GETSET(std::string,unique_code)
};

