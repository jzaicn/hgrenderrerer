#pragma once

#include <vector>
#include "JsonCpp/json.h"

#define GETSET(type,name)\
private: type m_##name;\
public: type get_##name() const {return this->m_##name;}\
public: void set_##name(type _arg){this->m_##name=_arg;}\
public:	type& ref_##name() { return this->m_##name; }\
private:

// 	#define GETSET_VECTYPE(type,name)\
// 	private: type m_##name; \
// 	public: void get_##name(type& val) { for (UINT i = 0; i < sizeof(type) ; i++) { val[i] = m_##name[i] ; } } \
// 	public: void set_##name(const type& val) { for (UINT i = 0; i < sizeof(type) ; i++) { m_##name[i] = val[i]; } } \
// 	public: float get_##name##_at(UINT _i) { return m_##name[_i] ; } \
// 	public: float set_##name##_at(UINT _i,float val) { m_##name[_i] = val; } \
// 	void clear_##name() { for (UINT i = 0;i<sizeof(type);i++) { m_##name[i] = 0; } }\
// 	private:
// 
// 	#define CREATE_IMPLEMENT(type) \
// 	type* val = (type*)(malloc(sizeof(type))); \
// 	if (!val) { throw std::runtime_error("##type ´´½¨Ê§°Ü"); }\
// 	saveTo(*val); return val; \
// 

#define JsonVectorSave(type,name)	\
{ Json::Value arr##name; for (UINT i = 0; i < m_##name##.size() ; i++) {  \
	Json::Value val;	m_##name##.at(i).save(val);	arr##name##.append(val); } \
	out[#name] = arr##name; }

#define JsonVectorLoad(type,name) \
	if (in[#name].isArray()) { for (UINT i = 0; i < in[#name].size() ; i++) {\
	type name##Temp;\
	name##Temp.load(in[#name][i]);\
	m_##name.push_back(##name##Temp);	}}



class HG_Vec2;
class HG_Vec3;
class HG_Vec4;
class HG_Mat;


class HG_BaseModel
{
public:
	HG_BaseModel(void){};
	virtual ~HG_BaseModel(void){};
	HG_BaseModel(const HG_BaseModel& other)	{}
	
	HG_BaseModel& operator=(const HG_BaseModel &other)	{return *this;}

	virtual std::string get_classname() { return "HG_BaseModel"; };

	virtual void save(Json::Value& out){};
	virtual void load(const Json::Value& in){};
};

class HG_Vec2 : HG_BaseModel
{
public:
	HG_Vec2(void)
	{
		set_x(0);
		set_y(0);
	}
	HG_Vec2(float x, float y)
	{
		set_x(x);
		set_y(y);
	}
	HG_Vec2(const HG_Vec2& other)
	{
		set_x(other.get_x());
		set_y(other.get_y());
	}
	~HG_Vec2(void){};

	HG_Vec2& operator=(const HG_Vec2 &other)
	{
		set_x(other.get_x());
		set_y(other.get_y());
		return *this;
	}

	virtual std::string get_classname() override { return "HG_Vec2"; };

	virtual void save(Json::Value& out) override
	{
		out["x"] = get_x();
		out["y"] = get_y();
	}

	virtual void load(const Json::Value& in) override
	{
		set_x(in["x"].asFloat());
		set_y(in["y"].asFloat());
	}



private:
	GETSET(float,x);
	GETSET(float,y);

};

class HG_Vec3 : HG_BaseModel
{
public:
	HG_Vec3(void)
	{
		set_x(0);
		set_y(0);
		set_z(0);
	}
	HG_Vec3(float x, float y,float z)
	{
		set_x(x);
		set_y(y);
		set_z(z);
	}
	HG_Vec3(const HG_Vec3& other)
	{
		set_x(other.get_x());
		set_y(other.get_y());
		set_z(other.get_z());
	}
	~HG_Vec3(void){};

	HG_Vec3& operator=(const HG_Vec3 &other)
	{
		set_x(other.get_x());
		set_y(other.get_y());
		set_z(other.get_z());
		return *this;
	}


	std::string get_classname(){ return "HG_Vec3"; };

	virtual void save(Json::Value& out) override
	{
		out["x"] = get_x();
		out["y"] = get_y();
		out["z"] = get_z();
	}


	virtual void load(const Json::Value& in) override
	{
		set_x(in["x"].asFloat());
		set_y(in["y"].asFloat());
		set_z(in["z"].asFloat());
	}
private:
	GETSET(float,x);
	GETSET(float,y);
	GETSET(float,z);
	
};

class HG_Vec4 : HG_BaseModel
{
public:
	HG_Vec4(void)
	{
		set_x(0);
		set_y(0);
		set_z(0);
		set_w(0);
	}
	HG_Vec4(float x, float y,float z,float w)
	{
		set_x(x);
		set_y(y);
		set_z(z);
		set_w(w);
	}
	HG_Vec4(const HG_Vec4& other)
	{
		set_x(other.get_x());
		set_y(other.get_y());
		set_z(other.get_z());
		set_w(other.get_w());
	}
	~HG_Vec4(void){};

	HG_Vec4& operator=(const HG_Vec4 &other)
	{
		set_x(other.get_x());
		set_y(other.get_y());
		set_z(other.get_z());
		set_w(other.get_w());
		return *this;
	}


	virtual std::string get_classname() { return "HG_Vec4"; };

	virtual void save(Json::Value& out) override
	{
		out["x"] = get_x();
		out["y"] = get_y();
		out["z"] = get_z();
		out["w"] = get_w();
	}


	virtual void load(const Json::Value& in) override
	{
		set_x(in["x"].asFloat());
		set_y(in["y"].asFloat());
		set_z(in["z"].asFloat());
		set_w(in["w"].asFloat());
	}

private:
	GETSET(float,x);
	GETSET(float,y);
	GETSET(float,z);
	GETSET(float,w);

};

class HG_Mat : public HG_BaseModel
{
public:
	HG_Mat(void)
	{
		set_mat(_matrix);
		clear();
	}
	HG_Mat(const HG_Vec4& v1, const HG_Vec4& v2, const HG_Vec4& v3, const HG_Vec4& v4)
	{
		set_mat(_matrix);
		clear();
		m_mat[0] = v1;
		m_mat[1] = v2;
		m_mat[2] = v3;
		m_mat[3] = v4;
	}
	HG_Mat(const HG_Mat& other)
	{
		set_mat(_matrix);
		clear();
		m_mat[0] = other.m_mat[0];
		m_mat[1] = other.m_mat[1];
		m_mat[2] = other.m_mat[2];
		m_mat[3] = other.m_mat[3];
	}
	~HG_Mat(void){};

	HG_Mat& operator=(const HG_Mat &other)
	{
		set_mat(_matrix);
		clear();
		m_mat[0] = other.m_mat[0];
		m_mat[1] = other.m_mat[1];
		m_mat[2] = other.m_mat[2];
		m_mat[3] = other.m_mat[3];
		return *this;
	}

	virtual std::string get_classname() { return "HG_Mat"; };

	void clear()
	{
		for (int row = 0; row < 4 ; row++)
		{
			m_mat[row] = HG_Vec4();
		}
	}

	virtual void save(Json::Value& out) override
	{
		for (int row = 0; row < 4 ; row++)
		{
			Json::Value strMatRow;
			strMatRow.clear();
			m_mat[row].save(strMatRow);

			CString strIndex;
			strIndex.Format("%d",row);
			out[strIndex.GetBuffer()] = strMatRow;
		}
	}


	virtual void load(const Json::Value& in) override
	{
		for (int row = 0; row < 4 ; row++)
		{
			CString strIndex;
			strIndex.Format("%d",row);
			m_mat[row].load(in[strIndex.GetBuffer()]);
		}
	}
private:
	HG_Vec4 _matrix[4];
	GETSET(HG_Vec4*,mat);
};