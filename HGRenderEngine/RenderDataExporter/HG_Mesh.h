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



	virtual std::string get_classname() override;


	virtual void save(Json::Value& out) override;


	virtual void load(const Json::Value& in) override;

public:
	GETSET(UINT,t1);				
	GETSET(UINT,t2);
	GETSET(UINT,t3);
	GETSET(UINT,material) ;			
};

class HG_Mesh :public HG_BaseModel
{
public:
	HG_Mesh(void);
	~HG_Mesh(void);


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

