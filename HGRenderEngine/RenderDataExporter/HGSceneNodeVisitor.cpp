#include "StdAfx.h"
#include "HGSceneNodeVisitor.h"


#include "HgLog\HgLog.h"
#include "osg\Geode"
#include "osg\Geometry"
#include "osg\Billboard"
#include "osg\Group"
#include "osg\ProxyNode"
#include "osg\Projection"
#include "osg\CoordinateSystemNode"
#include "osg\ClipNode"
#include "osg\TexGenNode"
#include "osg\LightSource"
#include "osg\Transform"
#include "osg\Camera"
#include "osg\CameraView"
#include "osg\MatrixTransform"
#include "osg\PositionAttitudeTransform"
#include "osg\Switch"
#include "osg\Sequence"
#include "osg\LOD"
#include "osg\PagedLOD"
#include "osg\ClearNode"
#include "osg\OccluderNode"
#include "osg\OcclusionQueryNode"
#include "osg\StateSet"
#include "osg\Material"
#include "osg\CullFace"

#include "hgcw\hgCst\DoorSeries.h"
#include "hgcw\hgCst\AlumStrip.h"
#include "hgcw\hgCst\Borer.h"
#include "hgcw\hgCst\BorerShow.h"
#include "hgcw\hgCst\Door.h"
#include "hgcw\hgCst\Glass.h"
#include "hgcw\hgCst\Model.h"
#include "hgcw\hgCst\Shape.h"
#include "hgcw\hgCst\SliderDoor.h"
#include "hg3d\Entity.h"
#include "hg3d\NDoorCore.h"
#include "hg3d\NDoorFrame.h"
#include "hg3d\NDoorPocket.h"
#include "hg3d\DoorWindow.h"
#include "hg3d\Girder.h"
#include "hg3d\ExtrudeMaterial.h"
#include "hg3d\LineMaterial.h"
#include "hg3d\Utils.h"
#include "HG_Mesh.h"
#include "HG_Config.h"
#include "GeodeReader.h"
#include "osgDB/FileUtils"

HGSceneNodeVisitor::HGSceneNodeVisitor(void)
{
	m_level = 0;
	//设置默认递归全部子节点
	setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
	setTraversalMask(0xffffffff);
	setNodeMaskOverride(0);
	setVisitorType(osg::NodeVisitor::NODE_VISITOR);

}


HGSceneNodeVisitor::~HGSceneNodeVisitor(void)
{
}
//////////////////////////////////////////////////////////////////////////
// 类型检测
#if 1
//判断节点是否Group节点
bool HGSceneNodeVisitor::isGroup(osg::Node &node)
{
	osg::Group* group = node.asGroup();
	return (group != nullptr);
}

//判断节点是否用于绘图
bool HGSceneNodeVisitor::isGeode(osg::Node &node)
{
	osg::Geode* geode = node.asGeode();
	return (geode != nullptr);
}

//判断线型
bool HGSceneNodeVisitor::isGroupLiner(osg::Node& node)
{
	CHECK_IF_DO(hg3d::HBar,&node,{ return true; });
	CHECK_IF_DO(hg3d::VBar,&node,{ return true; });
	CHECK_IF_DO(hg3d::ExtrudeMaterial,&node,{ return true; });
	CHECK_IF_DO(hg3d::LineMaterial,&node,{ return true; });
	return false;
}

//判断模型
bool HGSceneNodeVisitor::isGroupModel(osg::Node& node)
{
	CHECK_IF_DO(hg3d::Borer,&node,{ return true; });
	CHECK_IF_DO(hg3d::BorerShow,&node,{ return true; });
	CHECK_IF_DO(hg3d::Entity,&node,{ return true; });
	CHECK_IF_DO(hg3d::Girder,&node,{ return true; });
	CHECK_IF_DO(hg3d::Door,&node,{ return true; });
	CHECK_IF_DO(hg3d::AlumStrip,&node,{ return true; });
	CHECK_IF_DO(hg3d::Glass,&node,{ return true; });
	CHECK_IF_DO(hg3d::Model,&node,{ return true; });
	CHECK_IF_DO(hg3d::Shape,&node,{ return true; });
	CHECK_IF_DO(hg3d::NDoorCore,&node,{ return true; });
	CHECK_IF_DO(hg3d::NDoorFrame,&node,{ return true; });
	CHECK_IF_DO(hg3d::NDoorPocket,&node,{ return true; });
	CHECK_IF_DO(hg3d::DoorWindow,&node,{ return true; });
	CHECK_IF_DO(hg3d::SliderDoor,&node,{ return true; });
	
	return false;
}

//判断是否跳过这个节点
bool HGSceneNodeVisitor::isGroupIgnore(osg::Node& node)
{
	CHECK_IF_DO(hg3d::Borer,&node,{ return true; });
	CHECK_IF_DO(hg3d::BorerShow,&node,{ return true; });
	return false;
}

//判断是否板件
bool HGSceneNodeVisitor::isGroupPanel(osg::Node& node)
{
	CHECK_IF_DO(hg3d::Panel,&node,{ return true; });
	return false;
}
#endif
//////////////////////////////////////////////////////////////////////////
// 处理节点
#if 1

//递归遍历所有子节点
void HGSceneNodeVisitor::apply(osg::Node& node)
{
	//如果是组
	if (isGroup(node))
	{
		debugGroup(*node.asGroup());
	
		if (!ProcessGroup(node.asGroup()))
		{
			groupRoute(node);
		}		
		
		return;
	}
	else
	{
		debugNode(node);

		//如果是可以画的实体
		if (isGeode(node))
		{
			osg::Geode* geode = node.asGeode();
			ProcessGeode(geode);
			
		}
	}
}
bool HGSceneNodeVisitor::ProcessGroup(osg::Group* node)
{
	if (isGroupIgnore(*node)) return true;
	//if (isGroupLiner(node)) ;
	if (isGroupModel(*node)) 
	{
		std::string modeFile;
		osg::Matrix mat;

		
// 		{ 
// 			hg3d::Entity* conv = dynamic_cast<hg3d::Entity*>(node);
// 			osg::Quat quat = conv->getAttitude();
// 			conv->getMatrix();
// 			conv->computeLocalToWorldMatrix();
// 			conv->getWorldMatrices(0);
// 			hg3d::getFullFileName(conv->get_modelFile());
// 		 	if (conv) { function } 
// 		}

		CHECK_IF_DO(hg3d::Entity,node,{  modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Girder,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Door,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::AlumStrip,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Glass,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Model,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Shape,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::NDoorCore,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::NDoorFrame,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::NDoorPocket,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::DoorWindow,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::SliderDoor,node,{ modeFile = hg3d::getFullFileName(conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });

		return SaveModel(modeFile, mat);
	}
	//if (isGroupPanel(node)) ;
	//else 



	return false;
}

bool HGSceneNodeVisitor::SaveModel(std::string& modeFile, osg::Matrix& mat)
{
	//TODO: 查找高模，成功则不再分发
	HGLOG_DEBUG("mode file: %s",modeFile.c_str());
	HGLOG_DEBUG("[ %f %f %f %f ]",mat(0,0),mat(0,1),mat(0,2),mat(0,3));
	HGLOG_DEBUG("[ %f %f %f %f ]",mat(1,0),mat(1,1),mat(1,2),mat(1,3));
	HGLOG_DEBUG("[ %f %f %f %f ]",mat(2,0),mat(2,1),mat(2,2),mat(2,3));
	HGLOG_DEBUG("[ %f %f %f %f ]",mat(3,0),mat(3,1),mat(3,2),mat(3,3));
	//mat.invert(mat);

	CString strMatrix;
	CString oneMatrix;
	oneMatrix.Format("[%0.2f%0.2f%0.2f%0.2f]",mat(0,0),mat(0,1),mat(0,2),mat(0,3));
	strMatrix+=oneMatrix;
	oneMatrix.Format("[%0.2f%0.2f%0.2f%0.2f]",mat(1,0),mat(1,1),mat(1,2),mat(1,3));
	strMatrix+=oneMatrix;
	oneMatrix.Format("[%0.2f%0.2f%0.2f%0.2f]",mat(2,0),mat(2,1),mat(2,2),mat(2,3));
	strMatrix+=oneMatrix;
	oneMatrix.Format("[%0.2f%0.2f%0.2f%0.2f]",mat(3,0),mat(3,1),mat(3,2),mat(3,3));
	strMatrix+=oneMatrix;
	strMatrix = HGCode::UrlUTF8(strMatrix.GetBuffer()).c_str();

	if (!modeFile.empty())
	{
		//查找高模
		CString highModelPath = modeFile.c_str();
		highModelPath.Replace(".IVE",".ess");
		if (PathFileExists(highModelPath))
		{
			//找到高模
			modeFile = highModelPath.GetBuffer();
			
			//更改文件名为ascii
			std::string file_new_name = modeFile;
			CString replacestring = file_new_name.c_str();
			replacestring.Replace(" ","");
			replacestring.Replace("-","");
			replacestring.Replace(":","");
			replacestring.Replace("\\","");
			replacestring.Replace(".ess","");
			file_new_name = replacestring.GetBuffer();
			file_new_name = HGCode::UrlUTF8(const_cast<char*>(file_new_name.c_str()));
			file_new_name += ".ess";

			//文件应该放置到的新位置
			std::string export_name = HG_Config::inst().get_model_export_path(file_new_name);

			//把文件拷贝到新目录
			if (!osgDB::makeDirectoryForFile(export_name))
			{
				HGLOG_DEBUG("不能创建目录 %s",export_name.c_str());
			}
			if (osgDB::FileOpResult::OK != osgDB::copyFile(modeFile,export_name))
			{
				HGLOG_DEBUG("不能拷贝到指定目录 %s",export_name.c_str());
			}

			//保存
			HGLOG_DEBUG("high mode file: %s",export_name.c_str());
			HG_ModelInstance modelinst = HG_ModelInstance(export_name,convertToHG_Mat(mat));
			modelinst.set_unique_code(strMatrix.GetBuffer());
			HG_SceneCenter::inst().addModelInstance(modelinst);
			return true;
		}
	}
	return false;
}

HG_Mat HGSceneNodeVisitor::convertToHG_Mat(osg::Matrix mat)
{
	HG_Mat hgmat;
	hgmat.ref_mat()[0] = HG_Vec4(mat(0,0),mat(0,1),mat(0,2),mat(0,3));
	hgmat.ref_mat()[1] = HG_Vec4(mat(1,0),mat(1,1),mat(1,2),mat(1,3));
	hgmat.ref_mat()[2] = HG_Vec4(mat(2,0),mat(2,1),mat(2,2),mat(2,3));
	hgmat.ref_mat()[3] = HG_Vec4(mat(3,0),mat(3,1),mat(3,2),mat(3,3));
	return hgmat;
}


void HGSceneNodeVisitor::ProcessGeode(osg::Geode* geode)
{
	GeodeReader reader(geode);
}

//路由子节点
void HGSceneNodeVisitor::groupRoute(osg::Node &node)
{
	osg::Group* group = node.asGroup();
	for (UINT i = 0; i < group->getNumChildren(); i++)
	{
		m_level++;
		osg::Node* pnode = (group->getChild(i));
		//traverse(*(node));
		apply(*pnode);
		m_level--;
	}
}

//识别节点的类型分类
std::string HGSceneNodeVisitor::getGroupFilterName(osg::Node &node)
{
	if (isGroupLiner(node))
	{
		return ("liner");
	}
	else if (isGroupModel(node))
	{
		return("model");
	} 
	else if (isGroupPanel(node))
	{
		return("panel");
	}
	else
	{
		return "other";
	}
}
#endif
//////////////////////////////////////////////////////////////////////////
// 调试输出
#if 1
//输出当前子节点
void HGSceneNodeVisitor::debugNode(osg::Node &node)
{
	std::string libName = node.libraryName();
	std::string className = node.className();
	std::string nodeName = node.getName();
	HGLOG_DEBUG("libname: %s, m_level:%02d , classname: %s , nodename: %s ",libName.c_str(),m_level,className.c_str(),nodeName.c_str());
}

//输出当前组节点
void HGSceneNodeVisitor::debugGroup(osg::Group &node)
{
	std::string libName = node.libraryName();
	std::string className = node.className();
	std::string nodeName = node.getName();
	int size = node.getNumChildren();
	HGLOG_DEBUG("libname: %s, m_level:%02d , classname: %s , nodename: %s child: %d type: %s "
		,libName.c_str(),m_level,className.c_str(),nodeName.c_str(),size,getGroupFilterName(node).c_str());
}
#endif