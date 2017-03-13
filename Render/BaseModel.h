#pragma once

#include "ElaraHomeAPI.h"
#include <vector>

typedef float EH_RGB[3];
typedef float EH_RGBA[4];
typedef float EH_Vec[3];
typedef float EH_Vec2[2];
typedef float EH_Mat[16];


#define GETSET(type,name)\
private: type m_##name;\
public: type get_##name() const {return this->m_##name;}\
public: void set_##name(type _arg){this->m_##name=_arg;}\
private:

#define GETSET_VECTYPE(type,name)\
private: type m_##name; \
public: void get_##name(type& val) { for (int i = 0; i < sizeof(type) ; i++) { val[i] = m_##name[i] ; } } \
public: void set_##name(const type& val) { for (int i = 0; i < sizeof(type) ; i++) { m_##name[i] = val[i]; } } \
public: float get_##name##_at(int _i) { return m_##name[_i] ; } \
public: float set_##name##_at(int _i,float val) { m_##name[_i] = val; } \
void clear_##name() { for (int i = 0;i<sizeof(type);i++) { m_##name[i] = 0; } }\
private:

#define CREATE_IMPLEMENT(type) \
type* val = (type*)(malloc(sizeof(type))); \
if (!val) { throw std::runtime_error("##type 创建失败"); }\
saveTo(*val); return val; \



class BaseModel
{
public:
	BaseModel(void);
	~BaseModel(void);

private:
	virtual void create() = 0;
public:
	virtual void saveTo() = 0;
	virtual void loadFrom() = 0;

};

class HG_Vec3
{
public:
	HG_Vec3(void);
	~HG_Vec3(void);

public:
	EH_Vec* create();
	void saveTo(_Out_ EH_Vec& vec);
	void loadFrom(const EH_Vec& vec);
	
private:
	GETSET(float,x);
	GETSET(float,y);
	GETSET(float,z);
	
};


class HG_Vec2
{
public:
	HG_Vec2(void);
	~HG_Vec2(void);

public:
	EH_Vec2* create();
	void saveTo(_Out_ EH_Vec2& vec);
	void loadFrom(const EH_Vec2& vec);

private:
	GETSET(float,x);
	GETSET(float,y);

};



class HG_Vec3List : public std::vector<HG_Vec3>
{
public:
	HG_Vec3List():m_arrPointer(NULL){};
	~HG_Vec3List()
	{
		freeArray();
	};

	void fromArray(EH_Vec* arr,UINT size)
	{
		if (arr != NULL)
		{
			freeArray();
			this->clear();
			for (UINT i = 0; i < size ; i++)
			{
				HG_Vec3 newItem;
				newItem.loadFrom(arr[i]);
				this->push_back(newItem);
			}
		}
	}

	EH_Vec* toArray()
	{

		if (!isNeedToFree())
		{ 
			EH_Vec* arr = (EH_Vec*)( malloc(sizeof(EH_Vec) * this->size()) );
			if (!arr)
			{	
				throw std::runtime_error("EH_Vec array 创建失败");
			}
			for (UINT i = 0; i < this->size() ; i++)
			{
				(*this)[i].saveTo( arr[i] );
			}
			set_arrPointer(arr);
			return arr;
		}
		else
		{
			return get_arrPointer();
		}
	}
	bool isNeedToFree()
	{
		return (get_arrPointer() != nullptr);
	}
	void freeArray()
	{
		if (isNeedToFree())
		{
			free(get_arrPointer());
			set_arrPointer(NULL);
		}
	}
private:
	GETSET(EH_Vec*,arrPointer);
};

class HG_Vec2List : public std::vector<HG_Vec2>
{
public:
	HG_Vec2List():m_arrPointer(NULL){};
	~HG_Vec2List()
	{
		freeArray();
	};

	void fromArray(EH_Vec2* arr,UINT size)
	{
		if (arr != NULL)
		{
			freeArray();
			this->clear();
			for (UINT i = 0; i < size ; i++)
			{
				HG_Vec2 newItem;
				newItem.loadFrom(arr[i]);
				this->push_back(newItem);
			}
		}
	}

	EH_Vec2* toArray()
	{
		
		if (!isNeedToFree())
		{ 
			EH_Vec2* arr = (EH_Vec2*)( malloc(sizeof(EH_Vec2) * this->size()) );
			if (!arr)
			{	
				throw std::runtime_error("EH_Vec2 array 创建失败");
			}
			for (UINT i = 0; i < this->size() ; i++)
			{
				(*this)[i].saveTo( arr[i] );
			}
			set_arrPointer(arr);
			return arr;
		}
		else
		{
			return get_arrPointer();
		}
	}
	bool isNeedToFree()
	{
		return (get_arrPointer() != nullptr);
	}
	void freeArray()
	{
		if (isNeedToFree())
		{
			free(get_arrPointer());
			set_arrPointer(NULL);
		}
	}
private:
	GETSET(EH_Vec2*,arrPointer);
};

class HG_UintList : public std::vector<UINT>
{
public:
	HG_UintList():m_arrPointer(NULL){};
	~HG_UintList()
	{
		freeArray();
	};

	void fromArray(UINT* arr,UINT size)
	{
		if (arr != NULL)
		{
			freeArray();
			this->clear();
			for (UINT i = 0; i < size ; i++)
			{
				UINT newItem;
				newItem = arr[i];
				this->push_back(newItem);
			}
		}
	}

	UINT* toArray()
	{

		if (!isNeedToFree())
		{ 
			UINT* arr = (UINT*)( malloc(sizeof(UINT) * this->size()) );
			if (!arr)
			{	
				throw std::runtime_error("UINT array 创建失败");
			}
			for (UINT i = 0; i < this->size() ; i++)
			{
				arr[i] = (*this)[i];
			}
			set_arrPointer(arr);
			return arr;
		}
		else
		{
			return get_arrPointer();
		}
	}
	bool isNeedToFree()
	{
		return (get_arrPointer() != nullptr);
	}
	void freeArray()
	{
		if (isNeedToFree())
		{
			free(get_arrPointer());
			set_arrPointer(NULL);
		}
	}
private:
	GETSET(UINT*,arrPointer);
};