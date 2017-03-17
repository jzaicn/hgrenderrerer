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
		

	//////////////////////////////////////////////////////////////////////////
	// ���ͼ��
#if 1

	//�ж�����ת���ɹ���ִ��
#define CHECK_IF_DO(class_type,point,function) \
	{ class_type* conv = dynamic_cast<class_type*>(point); 	if (conv) { function } }


	//�жϽڵ��Ƿ�Group�ڵ�
	bool isGroup(osg::Node &node);

	//�жϽڵ��Ƿ����ڻ�ͼ
	bool isGeode(osg::Node &node);

	//�ж�����
	bool isGroupLiner(osg::Node& node);

	//�ж�ģ��
	bool isGroupModel(osg::Node& node);

	//�ж��Ƿ���������ڵ�
	bool isGroupIgnore(osg::Node& node);

	//�ж��Ƿ���
	bool isGroupPanel(osg::Node& node);



#endif
	//////////////////////////////////////////////////////////////////////////
	// ����ڵ�
#if 1
	//�ݹ���������ӽڵ�
	virtual void apply(osg::Node& node);

	void ProcessGeode(osg::Geode* geode);

	//·���ӽڵ�
	void groupRoute(osg::Node &node);

	//ʶ��ڵ�����ͷ���
	std::string getGroupFilterName(osg::Node &node);
#endif
	//////////////////////////////////////////////////////////////////////////
	// �������
#if 1
	//�����ǰ�ӽڵ�
	void debugNode(osg::Node &node);

	//�����ǰ��ڵ�
	void debugGroup(osg::Group &node);

#endif

};

