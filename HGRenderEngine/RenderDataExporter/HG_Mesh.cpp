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
