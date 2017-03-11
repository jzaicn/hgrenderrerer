#include "StdAfx.h"
#include "HG_Mesh.h"
#include <stdexcept>

HG_Mesh::HG_Mesh(void)
{
	GETSET(uint_t,num_verts);
	GETSET(uint_t,num_faces);
	GETSET(uint_t,face_indices);	

	GETSET_VECTYPE(EH_Vec,verts);
	GETSET_VECTYPE(EH_Vec,normals);
	GETSET_VECTYPE(EH_Vec2,uvs);

	set_num_verts(0);
	set_num_faces(0);
	set_face_indices(0);
	clear_verts();
	clear_normals();
	clear_uvs();

	set_mesh(create());
}


HG_Mesh::~HG_Mesh(void)
{
	if (get_mesh())
	{
		free(get_mesh());
		set_mesh(NULL);
	}
}

EH_Mesh* HG_Mesh::create()
{
	HG_Mesh* val = (HG_Mesh*)(malloc(sizeof(HG_Mesh)));
	if (!val)
	{
		throw std::runtime_error("HG_Mesh ´´½¨Ê§°Ü");
	}
	saveTo(*val);
	return val;
}

void HG_Mesh::saveTo(_Out_ EH_Mesh& mesh)
{
	mesh.verts = get_num_verts();
	mesh.num_faces = get_num_faces();
	get_verts(mesh.verts);
	get_normals(mesh.normals);
	get_uvs(mesh.uvs);
	mesh.face_indices = get_face_indices();
}

void HG_Mesh::loadFrom(const EH_Mesh& mesh )
{
	set_num_verts(mesh.verts);
	set_num_faces(mesh.num_faces);
	set_verts(mesh.verts);
	set_normals(mesh.normals);
	set_uvs(mesh.uvs);
	set_face_indices(mesh.face_indices);
}
