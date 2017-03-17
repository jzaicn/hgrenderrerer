#pragma once
#include "osg\NodeVisitor"

#include <stack>
#include "osg\Geometry"

struct Triangle;
typedef std::vector<std::pair<Triangle, int> > ListTriangle;
struct VertexIndex
{
	VertexIndex(unsigned int vertexIndex, unsigned int drawableIndex, unsigned int normalIndex)
		: vertexIndex(vertexIndex), drawableIndex(drawableIndex), normalIndex(normalIndex)
	{}
	VertexIndex(const VertexIndex & v) : vertexIndex(v.vertexIndex), drawableIndex(v.drawableIndex), normalIndex(v.normalIndex) {}

	unsigned int vertexIndex;        ///< Index of the vertice position in the vec3 array
	unsigned int drawableIndex;
	unsigned int normalIndex;        ///< Normal index for all bindings except BIND_PER_VERTEX and BIND_OFF.

	bool operator<(const VertexIndex & v) const {
		if (drawableIndex!=v.drawableIndex) 
			return drawableIndex<v.drawableIndex;
		else
			return vertexIndex<v.vertexIndex;
	}
};
typedef std::map<VertexIndex, unsigned int> MapIndices;



class HGSceneNodeVisitor :public osg::NodeVisitor
{
public:
	HGSceneNodeVisitor(void);
	~HGSceneNodeVisitor(void);

private:
	int m_level;
		
	typedef std::stack<osg::ref_ptr<osg::StateSet> > StateSetStack;
	///The Stack of different stateSet.
	StateSetStack _stateSetStack;
	///The current stateSet.
	osg::ref_ptr<osg::StateSet> _currentStateSet;

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



	bool _succeedLastApply;

	void pushStateSet(const osg::StateSet* ss);
	void popStateSet(const osg::StateSet* ss);
	int getMaterialIndex(const osg::StateSet* ss);
	void createListTriangle(const osg::Geometry* geo,ListTriangle& listTriangles,bool& texcoords,unsigned int& drawable_n);	

	void buildFaces(const osg::Geode& geo,ListTriangle&     listTriangles,bool              texcoords);
	///Tell us if last Node succeed traversing.
	bool succeedLastApply() const { return _succeedLastApply; }
	///Set the flag _succeedLastApply to false.
	void failedApply() { _succeedLastApply = false; }
#endif
	//////////////////////////////////////////////////////////////////////////
	// 处理节点
#if 1
	//递归遍历所有子节点
	virtual void apply(osg::Node& node);

	void setControlPointAndNormalsAndUV(const osg::Geode& geo, MapIndices& index_vert, bool texcoords); // FbxMesh* mesh);
	unsigned int addPolygont3(MapIndices & index_vert, unsigned int vertIndex, unsigned int normIndex, unsigned int drawableNum);
	void addPolygon( MapIndices & index_vert, const Triangle & tri, unsigned int drawableNum);
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

