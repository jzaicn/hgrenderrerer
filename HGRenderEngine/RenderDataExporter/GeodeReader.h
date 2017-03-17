#pragma once


#include <stack>
#include "osg\Geode"
#include "osg\StateSet"

//////////////////////////////////////////////////////////////////////////
// ������

//��������Ͳ���
class Triangle
{
public:
	unsigned int t1;		// ����index
	unsigned int t2;
	unsigned int t3;
	unsigned int normalIndex1;        ///< Normal index for all bindings except BIND_PER_VERTEX and BIND_OFF.
	unsigned int normalIndex2;
	unsigned int normalIndex3;
	int material;			//����index
};
//�������б�
typedef std::vector<std::pair<Triangle, int> > ListTriangle;
//״̬����
typedef std::stack<osg::ref_ptr<osg::StateSet> > StateSetStack;
//���㼯��
class VertexIndex
{
public:
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
//�������
typedef std::map<VertexIndex, unsigned int> MapIndices;


//////////////////////////////////////////////////////////////////////////
// Geodeר�Ŵ�����
class GeodeReader
{
public:
	GeodeReader(osg::Geode* _geode);	~GeodeReader(void);

	///Tell us if last Node succeed traversing.
	bool succeedLastApply() const { return _succeedLastApply; }

protected:
	//��������
	void processGeometery(osg::Geode* _geode);


	void pushStateSet(const osg::StateSet* ss);
	void popStateSet(const osg::StateSet* ss);
	int getMaterialIndex(const osg::StateSet* ss);
	void createListTriangle(const osg::Geometry* geo,ListTriangle& listTriangles,bool& texcoords,unsigned int& drawable_n);	
	void setControlPointAndNormalsAndUV(const osg::Geode& geo, MapIndices& index_vert, bool texcoords); // FbxMesh* mesh);
	unsigned int addPolygont3(MapIndices & index_vert, unsigned int vertIndex, unsigned int normIndex, unsigned int drawableNum);
	void addPolygon( MapIndices & index_vert, const Triangle & tri, unsigned int drawableNum);
	void buildFaces(const osg::Geode& geo,ListTriangle&     listTriangles,bool              texcoords);
	void failedApply() { _succeedLastApply = false; }
private:
	osg::Geode* geode;
	bool _succeedLastApply;
	
	StateSetStack _stateSetStack;
	osg::ref_ptr<osg::StateSet> _currentStateSet;
};



