#include "StdAfx.h"
#include "GeodeReader.h"




GeodeReader::GeodeReader(osg::Geode* _geode)
{
	_succeedLastApply = true;
	_currentStateSet = new osg::StateSet();
}


GeodeReader::~GeodeReader(void)
{
}

void GeodeReader::processGeometery()
{
	unsigned int count = geode->getNumDrawables();
	ListTriangle listTriangles;
	bool texcoords = false;

	if(geode->getStateSet()){
		pushStateSet(geode->getStateSet());
	}
	for (unsigned int i = 0; i < count; ++i)
	{
		const osg::Geometry* g = geode->getDrawable(i)->asGeometry();
		if (g != NULL)
		{
			pushStateSet(g->getStateSet());
			//TODO: 保存多边形三角化顺序
			createListTriangle(g, listTriangles, texcoords, i);
			popStateSet(g->getStateSet());
		}
	}

	for (int i = 0; i < listTriangles.size() ; i++)
	{
		HGLOG_DEBUG("vertsIndex{%d,%d,%d},normalIndex{%d,%d,%d},face:%d"
			,listTriangles.at(i).first.t1,listTriangles.at(i).first.t2,listTriangles.at(i).first.t3
			,listTriangles.at(i).first.normalIndex1,listTriangles.at(i).first.normalIndex2,listTriangles.at(i).first.normalIndex3
			,listTriangles.at(i).second);
	}


	if(geode->getStateSet()){
		popStateSet(geode->getStateSet());
	}
	if (count > 0)
	{
		buildFaces(*geode, listTriangles, texcoords);
	}
}
