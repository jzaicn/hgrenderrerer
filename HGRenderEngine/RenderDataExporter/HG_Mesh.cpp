#include "StdAfx.h"
#include "HG_Mesh.h"
#include <stdexcept>

HG_Mesh::HG_Mesh(void)
{
	set_num_verts(0);
	set_num_faces(0);
	//set_face_indices(0);
	//clear_verts();
	//clear_normals();
	//clear_uvs();

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
	EH_Mesh* val = (EH_Mesh*)(malloc(sizeof(EH_Mesh)));
	if (!val)
	{
		throw std::runtime_error("EH_Mesh ´´½¨Ê§°Ü");
	}
	saveTo(*val);
	return val;
}

void HG_Mesh::saveTo(_Out_ EH_Mesh& mesh)
{
	mesh.num_verts = get_num_verts();
	mesh.num_faces = get_num_faces();
	mesh.verts = get_verts().toArray();
	mesh.normals = get_normals().toArray();
	mesh.uvs = get_uvs().toArray();
	
	mesh.face_indices = m_face_indices.toArray();
}

void HG_Mesh::loadFrom(const EH_Mesh& mesh )
{
	set_num_verts(mesh.num_verts);
	set_num_faces(mesh.num_faces); 
	m_verts.fromArray(mesh.verts,mesh.num_verts);
	m_normals.fromArray(mesh.normals,mesh.num_faces);
	m_uvs.fromArray(mesh.uvs,mesh.num_faces);
	m_face_indices.fromArray(mesh.face_indices,mesh.num_faces * 3);
}
