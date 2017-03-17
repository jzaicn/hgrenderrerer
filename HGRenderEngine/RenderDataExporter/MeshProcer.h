#pragma once

#include "osg\Vec2"
#include "osg\Vec2d"
#include "osg\Vec3"
#include "osg\Vec3d"
#include "osg\Vec4"
#include "osg\Vec4d"
#include "osg\Geometry"

class MeshProcer
{
public:
	MeshProcer(void);
	~MeshProcer(void);
};


struct Triangle
{
	unsigned int t1;
	unsigned int t2;
	unsigned int t3;
	unsigned int normalIndex1;        ///< Normal index for all bindings except BIND_PER_VERTEX and BIND_OFF.
	unsigned int normalIndex2;
	unsigned int normalIndex3;
	int material;
};
typedef std::vector<std::pair<Triangle, int> > ListTriangle; //三角形和section之间关系
