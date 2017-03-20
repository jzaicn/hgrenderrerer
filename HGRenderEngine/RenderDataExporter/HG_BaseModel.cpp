#include "StdAfx.h"
#include "HG_BaseModel.h"
#include <stdexcept>
#include <sstream>

std::string HG_BaseModel::toString()
{
	return "HG_BaseModel";
}

std::string HG_Vec2::toString()
{
	HG_Vec2& v = *this;
	std::stringstream ss;
	ss<<"{"<<v.get_x()<<","<<v.get_y()<<"}";
	ss.flush();
	return ss.str();
}

std::string HG_Vec3::toString()
{
	const HG_Vec3& v = *this;
	std::stringstream ss;
	ss<<"{"<<v.get_x()<<","<<v.get_y()<<","<<v.get_z()<<"}";
	ss.flush();
	return ss.str();
}

std::string HG_Vec4::toString()
{
	const HG_Vec4& v = *this;
	std::stringstream ss;
	ss<<"{"<<v.get_x()<<","<<v.get_y()<<","<<v.get_z()<<","<<v.get_w()<<"}";
	ss.flush();
	return ss.str();
}

std::string HG_Mat::toString()
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
