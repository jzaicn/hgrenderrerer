#pragma once

#include <vector>


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

class HG_Vec2;
class HG_Vec3;
class HG_Vec4;
class HG_Mat;

class HG_BaseModel
{
public:
	HG_BaseModel(void){};
	virtual ~HG_BaseModel(void){};

	virtual std::string toString();
	virtual void fromString();

	virtual std::string toString()
	{
		return "HG_BaseModel";
	}

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
	~HG_Vec2(void){};

	std::string toString()
	{
		HG_Vec2& v = *this;
		std::stringstream ss;
		ss<<"{"<<v.get_x()<<","<<v.get_y()<<"}";
		ss.flush();
		return ss.str();
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
	~HG_Vec3(void){};

	std::string toString()
	{
		const HG_Vec3& v = *this;
		std::stringstream ss;
		ss<<"{"<<v.get_x()<<","<<v.get_y()<<","<<v.get_z()<<"}";
		ss.flush();
		return ss.str();
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
	~HG_Vec4(void){};

	std::string toString()
	{
		const HG_Vec4& v = *this;
		std::stringstream ss;
		ss<<"{"<<v.get_x()<<","<<v.get_y()<<","<<v.get_z()<<","<<v.get_w()<<"}";
		ss.flush();
		return ss.str();
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
	}
	~HG_Mat(void){};

	std::string toString()
	{
		const HG_Mat& v = *this;
		std::stringstream ss;
		ss<<"["<<v.get_mat()[0].get_x()<<","<<v.get_mat()[0].get_y()<<","<<v.get_mat()[0].get_z()<<","<<v.get_mat()[0].get_w()<<","<<"]"<<std::endl;
		ss<<"["<<v.get_mat()[1].get_x()<<","<<v.get_mat()[1].get_y()<<","<<v.get_mat()[1].get_z()<<","<<v.get_mat()[1].get_w()<<","<<"]"<<std::endl;
		ss<<"["<<v.get_mat()[2].get_x()<<","<<v.get_mat()[2].get_y()<<","<<v.get_mat()[2].get_z()<<","<<v.get_mat()[2].get_w()<<","<<"]"<<std::endl;
		ss<<"["<<v.get_mat()[3].get_x()<<","<<v.get_mat()[3].get_y()<<","<<v.get_mat()[3].get_z()<<","<<v.get_mat()[3].get_w()<<","<<"]"<<std::endl;
		ss.flush();
		return ss.str();
	}
private:
	HG_Vec4 _matrix[4];
	GETSET(HG_Vec4*,mat);
};