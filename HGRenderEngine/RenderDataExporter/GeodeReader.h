#pragma once


#include "osg\Geode"
//////////////////////////////////////////////////////////////////////////
// 工具类

//三角形面和材质
class Triangle
{
public:
	unsigned int t1;		// 顶点index
	unsigned int t2;
	unsigned int t3;
	unsigned int normalIndex1;        ///< Normal index for all bindings except BIND_PER_VERTEX and BIND_OFF.
	unsigned int normalIndex2;
	unsigned int normalIndex3;
	int material;			//材质index
};
//三角形列表
typedef std::vector<std::pair<Triangle, int> > ListTriangle;

//顶点集合
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
//顶点队列
typedef std::map<VertexIndex, unsigned int> MapIndices;

class GeodeReader
{
public:
	GeodeReader(osg::Geode* _geode);	~GeodeReader(void);

protected:
	void processGeometery();

private:
	osg::Geode* geode;
};

