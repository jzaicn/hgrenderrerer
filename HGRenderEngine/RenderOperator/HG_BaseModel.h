#pragma once

#include <vector>
#include "JsonCpp/json.h"
#include "HGCode.h"
#include <math.h>

#define GETSET(type,name)\
private: type m_##name;\
public: type get_##name() const {return this->m_##name;}\
public: void set_##name(type _arg){this->m_##name=_arg;}\
public:	type& ref_##name() { return this->m_##name; }\
private:



#define JsonVectorSave(type,name)	\
{ Json::Value arr##name; for (UINT i = 0; i < m_##name##.size() ; i++) {  \
	Json::Value val;	m_##name##.at(i).save(val);	arr##name##.append(val); } \
	out[#name] = arr##name; }

#define JsonVectorLoad(type,name) \
	if (in[#name].isArray()) { m_##name.clear(); for (UINT i = 0; i < in[#name].size() ; i++) {\
	type name##Temp;\
	name##Temp.load(in[#name][i]);\
	m_##name.push_back(##name##Temp);	}}


#define HGLOBYTE(w)           ((((UINT)(w)) & 0xff))
#define HGGetRValue(rgb)      (HGLOBYTE(rgb))
#define HGGetGValue(rgb)      (HGLOBYTE((rgb) >> 8))
#define HGGetBValue(rgb)      (HGLOBYTE((rgb)>>16))
#define HGGetAValue(rgb)      (HGLOBYTE((rgb)>>24))

#define HGRGB(r,g,b)          (((HGLOBYTE(r)|((HGLOBYTE(g))<<8))|((HGLOBYTE(b))<<16)))
#define HGCONV2RGB(vec4)      HGRGB((UINT)(vec4.get_x()*255.0),(UINT)(vec4.get_y()*255.0),(UINT)(vec4.get_z()*255.0))



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


	virtual void save(Json::Value& out) {}
	virtual void load(const Json::Value& in) {}

};
//TODO: 统一化所有save load接口.

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

	/*---- operator ----*/
	HG_Vec2& operator=(const HG_Vec2 &other)
	{
		set_x(other.get_x());
		set_y(other.get_y());
		return *this;
	}

	bool operator==(const HG_Vec2 &other)
	{
		if(get_x() != other.get_x() || get_y() != other.get_y())
			return true;
		return false;
	}

	bool operator!=(const HG_Vec2 &other)
	{
		if(get_x() != other.get_x() || get_y() != other.get_y())
			return true;
		return false;
	}

	float& operator[](const int index)
	{
		if (index > 1 || index < 0)
			throw std::out_of_range("Index out of range");
		if(index == 0)
			return m_x;
		return m_y;
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

	/*---- operator ----*/
	HG_Vec3& operator=(const HG_Vec3 &other)
	{
		set_x(other.get_x());
		set_y(other.get_y());
		set_z(other.get_z());
		return *this;
	}

	bool operator==(const HG_Vec3 &other)
	{
		if(get_x() != other.get_x() || get_y() != other.get_y() || get_z() != other.get_z())
			return true;
		return false;
	}

	bool operator!=(const HG_Vec3 &other)
	{
		if(get_x() != other.get_x() || get_y() != other.get_y() || get_z() != other.get_z())
			return true;
		return false;
	}

	float& operator[](const int index)
	{
		if (index > 2 || index < 0)
			throw std::out_of_range("Index out of range");
		if(index == 0)
			return m_x;
		if(index == 1)
			return m_y;
		return m_z;
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
	HG_Vec4(UINT material_color)
	{
		float r = (float)(HGGetRValue(material_color)) / 255.0f;
		float g = (float)(HGGetGValue(material_color)) / 255.0f;
		float b = (float)(HGGetBValue(material_color)) / 255.0f;
		//float a = (float)(HGGetAValue(material_color)) / 255.0f; 
		float a = 1.0f; 
		set_x(r);
		set_y(g);
		set_z(b);
		//TODO: 理论上应该默认是1.0的
		set_w(a);
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

	/*---- operator ----*/
	HG_Vec4& operator=(const HG_Vec4 &other)
	{
		set_x(other.get_x());
		set_y(other.get_y());
		set_z(other.get_z());
		set_w(other.get_w());
		return *this;
	}

	bool operator==(const HG_Vec4 &other)
	{
		if(get_x() != other.get_x() || get_y() != other.get_y() || get_z() != other.get_z() || get_w() != other.get_w())
			return true;
		return false;
	}

	bool operator!=(const HG_Vec4 &other)
	{
		if(get_x() != other.get_x() || get_y() != other.get_y() || get_z() != other.get_z() || get_w() != other.get_w())
			return true;
		return false;
	}

	float& operator[](const int index)
	{
		if (index > 3 || index < 0)
			throw std::out_of_range("Index out of range");
		if(index == 0)
			return m_x;
		if(index == 1)
			return m_y;
		if(index == 2)
			return m_z;
		return m_w;
	}

	UINT get_color_uint()
	{
		HG_Vec4 vec4 = *this;
		return HGCONV2RGB(vec4);
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

	/*---- operator ----*/
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

	bool operator==(const HG_Mat &other)
	{
		if(m_mat != other.m_mat)
			return false;
		return true;
	}

	bool operator!=(const HG_Mat &other)
	{
		if(m_mat != other.m_mat)
			return true;
		return false;
	}

	HG_Vec4& operator[](int row)
	{
		return m_mat[row];
	}

	HG_Mat operator*(const HG_Mat &other)
	{
		HG_Mat newMat;
		for(int col = 0; col < 4; col++)
		{
			for(int row = 0; row < 4; row++)
				newMat[row][col] = multiply(0, other, col);
		}

		return newMat;
	}

	void operator*=(const HG_Mat &other)
	{
		for(int col = 0; col < 4; col++)
		{
			for(int row = 0; row < 4; row++)
				m_mat[row][col] = multiply(0, other, col);
		}
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
			strIndex.Format(HGCode::convert("%d"),row);
			out[(char*)strIndex.GetBuffer()] = strMatRow;
		}
	}


	virtual void load(const Json::Value& in) override
	{
		for (int row = 0; row < 4 ; row++)
		{
			CString strIndex;
			strIndex.Format(HGCode::convert("%d"),row);
			m_mat[row].load(in[(char*)strIndex.GetBuffer()]);
		}
	}

	static HG_Mat identityMatrix()
	{
		return HG_Mat(HG_Vec4(1, 0, 0, 0), 
			HG_Vec4(0, 1, 0, 0), 
			HG_Vec4(0, 0, 1, 0), 
			HG_Vec4(0, 0, 0, 1));
	}

private:
	HG_Vec4 _matrix[4];
	GETSET(HG_Vec4*,mat);

	float multiply(int row, const HG_Mat& other, int col)
	{
		HG_Vec4 vRow = m_mat[row];
		float total = 0;
		for(int i = 0; i < 4; i++)
		{
			total += vRow[i] * other.get_mat()[i][col];
		}
		return total;
	}
};