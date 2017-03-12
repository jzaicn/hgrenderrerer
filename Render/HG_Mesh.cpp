#include "StdAfx.h"
#include "HG_Mesh.h"
#include <stdexcept>

HG_Mesh::HG_Mesh(void)
{
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
	EH_Mesh* val = (EH_Mesh*)(malloc(sizeof(EH_Mesh)));
	if (!val)
	{
		throw std::runtime_error("EH_Mesh 创建失败");
	}
	saveTo(*val);
	return val;
}

void HG_Mesh::saveTo(_Out_ EH_Mesh& mesh)
{
	mesh.num_verts = get_num_verts();
	mesh.num_faces = get_num_faces();
	get_verts(*mesh.verts);
	get_normals(*mesh.normals);
	get_uvs(*mesh.uvs);
	*mesh.face_indices = get_face_indices();//TODO: 这里小心，外部创建的数组来的
}

void HG_Mesh::loadFrom(const EH_Mesh& mesh )
{
	set_num_verts(mesh.num_verts);
	set_num_faces(mesh.num_faces); 
	set_verts(*mesh.verts);	//TODO: 这里小心，外部创建的数组来的
	set_normals(*mesh.normals);
	set_uvs(*mesh.uvs);
	set_face_indices(*mesh.face_indices);//TODO: 这里小心，外部创建的数组来的
}
