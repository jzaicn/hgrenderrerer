#pragma once


#include <stack>
#include <sstream> 
#include "osg\Geode"
#include "osg\StateSet"
#include "HG_BaseModel.h"

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
//����
class GeodeMatrial
{
public:
	typedef enum{
		empty,
		image,
		color
	}MType;

	GeodeMatrial(){ Type(empty); Color(1.0,1.0,1.0,1.0);};
	GeodeMatrial(std::string img ,GeodeMatrial::MType _type = image)
	{
		Image(img);	
		Type(_type);
	}
	//û����ͼ��ȫ��Ĭ��Ϊ��ɫ��������������
	GeodeMatrial(float r,float g,float b,float a ,GeodeMatrial::MType _type = color)
	{
		Color(r,g,b,a);
		Type(_type);
	}


	std::string Image() const { return m_image; }
	void Image(std::string val) { m_image = val; }
	osg::Vec4 Color() const { return m_color; }
	void Color(osg::Vec4 val) { m_color = val; }
	void Color(float r,float g,float b,float a) { m_color = osg::Vec4(r,g,b,a); }
	GeodeMatrial::MType Type() const { return m_type; }
	void Type(GeodeMatrial::MType val) { m_type = val; }

	std::string toString() 
	{
		if (m_type == image)
		{
			return std::string() + "image : " + m_image;
		} 
		else
		{
			std::stringstream ss;
			ss << "color : " << m_color.r() << m_color.g() << m_color.b() << m_color.a() ;
			return ss.str();
		} 
	}

	bool operator ==(const GeodeMatrial &other)
	{
		if (Type() == other.Type())
		{
			switch(m_type)
			{
			case image:
				return (Image().compare(other.Image()) == 0);
				break;
			case color:
				return ( Color()==other.Color() );
				break;
			case empty:
				return true;
				break;
			default:
				break;
			}
		}
		return false;
	}

private:
	MType m_type;
	std::string m_image;
	osg::Vec4 m_color;
};

//////////////////////////////////////////////////////////////////////////
// Geodeר�Ŵ�����
class GeodeReader
{
public:
	GeodeReader(osg::Geode* _geode);
	~GeodeReader(void);

	///Tell us if last Node succeed traversing.
	bool succeedLastApply() const { return m_succeedLastApply; }
	void debugGeode();

protected:
	//��������
	void processGeometery(osg::Geode* _geode);

	void createListUVs(const osg::Geometry* g);

	void createListNormals(const osg::Geometry* g);

	void createListVerts(const osg::Geometry* g);

	void saveMesh(const osg::Geometry* g,UINT drawable_n);



	void pushStateSet(const osg::StateSet* ss);
	void popStateSet(const osg::StateSet* ss);
	int getMaterialIndex(const osg::Geometry* geo, const osg::StateSet* ss);
	void createListTriangle(const osg::Geometry* geo,ListTriangle& listTriangles,bool& texcoords,unsigned int& drawable_n);	
	void setControlPointAndNormalsAndUV(const osg::Geode& geo, MapIndices& index_vert, bool texcoords); // FbxMesh* mesh);
	unsigned int addPolygont3(MapIndices & index_vert, unsigned int vertIndex, unsigned int normIndex, unsigned int drawableNum);
	void addPolygon( MapIndices & index_vert, const Triangle & tri, unsigned int drawableNum);
	void buildFaces(const osg::Geode& geo,ListTriangle& listTriangles,bool texcoords);
	void failedApply() { m_succeedLastApply = false; }
	void debugTriangleList();
private:
	osg::Geode* m_geode;
	bool m_succeedLastApply;
	
	StateSetStack m_stateSetStack;
	osg::ref_ptr<osg::StateSet> m_currentStateSet;

	GETSET(ListTriangle,listTriangles);
	GETSET(osg::ref_ptr<osg::Vec3Array>,points);
	GETSET(osg::ref_ptr<osg::Vec3Array>,normals);
	GETSET(osg::ref_ptr<osg::Vec2Array>,uvs);
	GETSET(std::vector<GeodeMatrial>,material);
};



