#pragma once
#include "HG_BaseModel.h"

class HG_MeshTriangle :public HG_BaseModel
{
public:
	HG_MeshTriangle()
	{
		set_t1(0);
		set_t2(0);
		set_t3(0);
		set_material(-1);
	};
	HG_MeshTriangle(UINT t1,UINT t2,UINT t3,int material = -1)
	{
		set_t1(t1);
		set_t2(t2);
		set_t3(t3);
		set_material(material);
	};

	HG_MeshTriangle(const HG_MeshTriangle& other)	
	{
		set_t1(other.get_t1());
		set_t2(other.get_t2());
		set_t3(other.get_t3());
		set_material(other.get_material());
	}
	
	HG_MeshTriangle& operator=(const HG_MeshTriangle &other)	
	{
		set_t1(other.get_t1());
		set_t2(other.get_t2());
		set_t3(other.get_t3());
		set_material(other.get_material());
		return *this;
	}

	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

public:
	GETSET(UINT,t1);				
	GETSET(UINT,t2);
	GETSET(UINT,t3);
	GETSET(int,material) ;			
};

class HG_Mesh :public HG_BaseModel
{
public:
	HG_Mesh(void);
	~HG_Mesh(void);

	HG_Mesh(const HG_Mesh& other)	
	{
		set_faces(other.get_faces());
		set_verts(other.get_verts());
		set_normals(other.get_normals());
		set_uvs(other.get_uvs());
		set_unique_code(other.get_unique_code());
	}
	
	HG_Mesh& operator=(const HG_Mesh &other)	
	{
		set_faces(other.get_faces());
		set_verts(other.get_verts());
		set_normals(other.get_normals());
		set_uvs(other.get_uvs());
		set_unique_code(other.get_unique_code());
		return *this;
	}

	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

private:
	GETSET(std::vector<HG_MeshTriangle>,faces);
	GETSET(std::vector<HG_Vec3>,verts);
	GETSET(std::vector<HG_Vec3>,normals);
	GETSET(std::vector<HG_Vec2>,uvs);
	GETSET(std::string,unique_code)
};

