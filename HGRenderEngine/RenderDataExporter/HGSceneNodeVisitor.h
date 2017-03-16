#pragma once
#include "osg\NodeVisitor"


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

	//���
	bool isGroupPanel(osg::Node& node);

#endif
	//////////////////////////////////////////////////////////////////////////
	// ����ڵ�
#if 1
	//�ݹ���������ӽڵ�
	virtual void apply(osg::Node& node);

	//·���ӽڵ�
	void groupRoute(osg::Node &node);

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

