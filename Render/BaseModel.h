#pragma once

#include "ElaraHomeAPI.h"
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
if (!val) { throw std::runtime_error("##type ´´½¨Ê§°Ü"); }\
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

