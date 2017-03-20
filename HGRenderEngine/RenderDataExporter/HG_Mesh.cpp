#include "StdAfx.h"
#include "HG_Mesh.h"
#include <stdexcept>

HG_Mesh::HG_Mesh(void)
{
	set_faces(std::vector<HG_MeshTriangle>());
	set_verts(std::vector<HG_Vec3>());
	set_normals(std::vector<HG_Vec3>());
	set_uvs(std::vector<HG_Vec2>());	
}


HG_Mesh::~HG_Mesh(void)
{
}


std::string HG_MeshTriangle::get_classname()
{
	return "HG_MeshTriangle";
}
void HG_MeshTriangle::save(Json::Value& out)
{
	out["t1"] = get_t1();
	out["t2"] = get_t2();
	out["t3"] = get_t3();
	out["material"] = get_material();
}

void HG_MeshTriangle::load(const Json::Value& in)
{
	set_t1(in["t1"].asUInt());
	set_t2(in["t2"].asUInt());
	set_t3(in["t3"].asUInt());
	set_material(in["material"].asUInt());
}



std::string HG_Mesh::get_classname()
{
	return "HG_Mesh";
}

void HG_Mesh::save(Json::Value& out)
{
	JsonVectorSave(HG_MeshTriangle,faces);
	JsonVectorSave(HG_Vec3,verts);
	JsonVectorSave(HG_Vec3,normals);
	JsonVectorSave(HG_Vec2,uvs);

	out["unique_code"] = get_unique_code();
}


void HG_Mesh::load(const Json::Value& in)
{
	
	JsonVectorLoad(HG_MeshTriangle,faces);
	JsonVectorLoad(HG_Vec3,verts);
	JsonVectorLoad(HG_Vec3,normals);
	JsonVectorLoad(HG_Vec2,uvs);

	set_unique_code(in["unique_code"].asString());

}

