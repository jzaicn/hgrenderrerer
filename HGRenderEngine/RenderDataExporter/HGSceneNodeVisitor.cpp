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
#include "hgcw\hgCst\Ironware.h"
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
bool HGSceneNodeVisitor::isIgnore(osg::Node& node)
{
	//TODO: 开了这两个书桌的桌角没了 Borer BorerShow 处理柜体配置或者筛选列表修复这个问题
	CHECK_IF_DO(hg3d::Borer,&node,{ return true; });
	CHECK_IF_DO(hg3d::BorerShow,&node,{ return true; });

	// 过滤
 	CHECK_IF_DO(osg::Node,&node,{ return conv->getName().compare("hide_box") == 0; });
// 	CHECK_IF_DO(osg::Node,&node,{ return conv->getName().compare("木肖") == 0; });
// 	CHECK_IF_DO(osg::Node,&node,{ return conv->getName().compare("偏心件") == 0; });
// 	CHECK_IF_DO(osg::Node,&node,{ return conv->getName().compare("偏心轮孔位") == 0; });
// 
// 
// 	CHECK_IF_DO(osg::Geometry,&node,{ return (conv->getName().compare("hide_box")==0); });
// 	CHECK_IF_DO(hg3d::Ironware,&node,{ return true; });
// 	CHECK_IF_DO(osg::Node,&node,{ return conv->getName().compare("Ironware") == 0; });
// 	CHECK_IF_DO(osg::Node,&node,{ return conv->getName().compare("Eccentric") == 0; });


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
	if (isIgnore(node))
	{
	}
	else if (isGroup(node))
	{
		//debugGroup(*node.asGroup());
	
		if (!ProcessModel(node.asGroup()))
		{
			groupRoute(node);
		}
	}
	else
	{
		//debugNode(node);

		//如果是可以画的实体
		if (isGeode(node))
		{
			ProcessGeode(node.asGeode());	
		}
	}
}
bool HGSceneNodeVisitor::ProcessModel(osg::Group* node)
{
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

		CHECK_IF_DO(hg3d::Entity,node,{  modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Girder,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Door,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::AlumStrip,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Glass,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Model,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::Shape,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::NDoorCore,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::NDoorFrame,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::NDoorPocket,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::DoorWindow,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });
		CHECK_IF_DO(hg3d::SliderDoor,node,{ modeFile = (conv->get_modelFile());mat = conv->getWorldMatrices().at(0); });

		if (isIgnoreModel(modeFile))
		{	
			//要过滤的模型，直接返回，不需要再次操作
			return true;
		}
		else
		{
			modeFile = hg3d::getFullFileName(modeFile);
			return SaveModel(modeFile, mat);
		}
		
	}



	return false;
}
bool HGSceneNodeVisitor::isIgnoreModel(const std::string& modeFile)
{
	std::string ignore_path = hg3d::getFullFileName(HG_Config::inst().get_model_ignore_path());
	std::string full_file_name = hg3d::getFullFileName(modeFile);
	if ( std::string::npos != full_file_name.find(ignore_path))
	{
		return true;
	}

	if (modeFile.empty())
	{
		return true;
	}

	return false;
}
bool HGSceneNodeVisitor::SaveModel(std::string modeFile, osg::Matrix mat)
{
	//TODO: 图片应该也要按model的方式处理一次
	if (!modeFile.empty())
	{
		HGLOG_DEBUG("mode file: %s",modeFile.c_str());	
		HGLOG_DEBUG("[ %6.2f %6.2f %6.2f %6.2f ]",mat(0,0),mat(0,1),mat(0,2),mat(0,3));
		HGLOG_DEBUG("[ %6.2f %6.2f %6.2f %6.2f ]",mat(1,0),mat(1,1),mat(1,2),mat(1,3));
		HGLOG_DEBUG("[ %6.2f %6.2f %6.2f %6.2f ]",mat(2,0),mat(2,1),mat(2,2),mat(2,3));
		HGLOG_DEBUG("[ %6.2f %6.2f %6.2f %6.2f ]",mat(3,0),mat(3,1),mat(3,2),mat(3,3));
		//mat.invert(mat);

		CString strMatrix = "MatrixModelName";
		CString oneMatrix;
		oneMatrix.Format("[%0.0f%0.0f%0.0f%0.0f]",mat(0,0),mat(0,1),mat(0,2),mat(0,3));
		strMatrix+=oneMatrix;
		oneMatrix.Format("[%0.0f%0.0f%0.0f%0.0f]",mat(1,0),mat(1,1),mat(1,2),mat(1,3));
		strMatrix+=oneMatrix;
		oneMatrix.Format("[%0.0f%0.0f%0.0f%0.0f]",mat(2,0),mat(2,1),mat(2,2),mat(2,3));
		strMatrix+=oneMatrix;
		oneMatrix.Format("[%0.0f%0.0f%0.0f%0.0f]",mat(3,0),mat(3,1),mat(3,2),mat(3,3));
		strMatrix+=oneMatrix;
		strMatrix = HGCode::UrlUTF8(strMatrix.GetBuffer()).c_str();
		strMatrix.Replace("%","");

		//查找高模
		CString highModelPath = modeFile.c_str();
		highModelPath.Replace(".hgi",".ess");
		highModelPath.Replace(".IVE",".ess");
		if (osgDB::fileExists(highModelPath.GetBuffer()))
		{
			std::string file_name = hg3d::getFileNameWithoutExt(modeFile);

			//找到高模
			std::string hight_mode_file = highModelPath.GetBuffer();
			
			//更改文件名为ascii
			std::string file_new_name = hight_mode_file;
			CString replacestring = file_new_name.c_str();
			replacestring.Replace(" ","");
			replacestring.Replace("-","");
			replacestring.Replace(":","");
			replacestring.Replace("\\","");
			replacestring.Replace(".ess","");
			replacestring = HGCode::UrlUTF8(const_cast<char*>(std::string(replacestring.GetBuffer()).c_str())).c_str();
			replacestring.Replace("%","");
			file_new_name = replacestring.GetBuffer();
			file_new_name += ".ess";

			//文件应该放置到的新位置
			std::string export_name = HG_Config::inst().get_model_export_path(file_new_name);

			//把文件拷贝到新目录
			if (!osgDB::makeDirectoryForFile(export_name))
			{
				HGLOG_DEBUG("不能创建目录 %s",export_name.c_str());
			}
			else if (osgDB::FileOpResult::OK != osgDB::copyFile(hight_mode_file,export_name))
			{
				//TODO: 复制过的模型也应该不用再复制，提高效率
				HGLOG_DEBUG("不能拷贝到指定目录 %s",export_name.c_str());
			}
			else
			{
				//保存
				HGLOG_DEBUG("high mode file: %s",export_name.c_str());
				HG_ModelInstance modelinst = HG_ModelInstance(export_name,convertToHG_Mat(mat));
				modelinst.set_unique_code(strMatrix.GetBuffer());
				HG_SceneCenter::inst().addModelInstance(modelinst);
				return true;
			}
		}
		else
		{
			HGLOG_DEBUG("找不到对应模型");
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