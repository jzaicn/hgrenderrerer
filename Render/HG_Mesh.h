#pragma once
#include "BaseModel.h"
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
	GETSET(uint_t,face_indices);	

	GETSET_VECTYPE(EH_Vec,verts);
	GETSET_VECTYPE(EH_Vec,normals);
	GETSET_VECTYPE(EH_Vec2,uvs);


};

