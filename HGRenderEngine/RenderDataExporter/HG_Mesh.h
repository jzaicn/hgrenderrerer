#pragma once
#include "HG_BaseModel.h"
class HG_Mesh
{
public:
	HG_Mesh(void);
	~HG_Mesh(void);

private:
	EH_Mesh* create();

public:
	void saveTo(_Out_ EH_Mesh& mesh);
	void loadFrom(const EH_Mesh& mesh);

private:
	GETSET(EH_Mesh*,mesh);

	GETSET(uint_t,num_verts);
	GETSET(uint_t,num_faces);

	GETSET(HG_Vec3List,verts);
	GETSET(HG_Vec3List,normals);
	GETSET(HG_Vec2List,uvs);

	GETSET(HG_UintList,face_indices);	

};

