#pragma once
#include "osg\NodeVisitor"

#include <stack>
#include "osg\Geometry"
#include "HG_SceneCenter.h"
#include "JsonCpp/json.h"

class HGSceneNodeVisitor :public osg::NodeVisitor
{
public:
	HGSceneNodeVisitor(void);
	~HGSceneNodeVisitor(void);

private:
	int m_level;

	//////////////////////////////////////////////////////////////////////////
	// 类型检测
#if 1

	//判断类型转换成功则执行
#define CHECK_IF_DO(class_type,point,function) \
	{ class_type* conv = dynamic_cast<class_type*>(point); 	if (conv) { function } }


	//判断节点是否Group节点
	bool isGroup(osg::Node &node);

	//判断节点是否用于绘图
	bool isGeode(osg::Node &node);

	//判断线型
	bool isGroupLiner(osg::Node& node);

	//判断模型
	bool isGroupModel(osg::Node& node);

	//判断是否跳过这个节点
	bool isGroupIgnore(osg::Node& node);

	//判断是否板件
	bool isGroupPanel(osg::Node& node);



#endif
	//////////////////////////////////////////////////////////////////////////
	// 处理节点
#if 1
	//递归遍历所有子节点
	virtual void apply(osg::Node& node);

	bool ProcessGroup(osg::Group* node);

	bool SaveModel(std::string& modeFile, osg::Matrix& mat);

	HG_Mat convertToHG_Mat(osg::Matrix mat);

	void ProcessGeode(osg::Geode* geode);

	//路由子节点
	void groupRoute(osg::Node &node);

	//识别节点的类型分类
	std::string getGroupFilterName(osg::Node &node);
#endif
	//////////////////////////////////////////////////////////////////////////
	// 调试输出
#if 1
	//输出当前子节点
	void debugNode(osg::Node &node);

	//输出当前组节点
	void debugGroup(osg::Group &node);

#endif

};

