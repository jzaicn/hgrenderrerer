#include "StdAfx.h"
#include "MeshProcer.h"


MeshProcer::MeshProcer(void)
{
}


MeshProcer::~MeshProcer(void)
{
}



void PrimitiveIndexWriter::writeTriangle(unsigned int i1, unsigned int i2, unsigned int i3)
{
	Triangle triangle;
	triangle.t1 = i1;
	triangle.t2 = i2;
	triangle.t3 = i3;
	if (_normalBinding == osg::Geometry::BIND_PER_VERTEX){
		triangle.normalIndex1 = i1;
		triangle.normalIndex2 = i2;
		triangle.normalIndex3 = i3;
	}
	else{
		triangle.normalIndex1 = _curNormalIndex;
		triangle.normalIndex2 = _curNormalIndex;
		triangle.normalIndex3 = _curNormalIndex;
	}
	_listTriangles.push_back(std::make_pair(triangle, _sectionIndex));
}

void PrimitiveIndexWriter::drawArrays(GLenum mode,GLint first,GLsizei count)
{
	unsigned int pos=first;
	switch (mode)
	{
	case GL_TRIANGLES:
		for (GLsizei i = 2; i < count; i += 3, pos += 3)
		{
			writeTriangle(pos, pos + 1, pos + 2);
			if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		}
		break;
	case GL_TRIANGLE_STRIP:
		for (GLsizei i = 2; i < count; ++i, ++pos)
		{
			if (i & 1) writeTriangle(pos, pos + 2, pos + 1);
			else       writeTriangle(pos, pos + 1, pos + 2);
		}
		if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		break;
	case GL_QUADS:
		for (GLsizei i = 3; i < count; i += 4, pos += 4)
		{
			writeTriangle(pos, pos + 1, pos + 2);
			writeTriangle(pos, pos + 2, pos + 3);
			if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		}
		break;
	case GL_QUAD_STRIP:
		for (GLsizei i = 3; i < count; i += 2, pos += 2)
		{
			writeTriangle(pos, pos + 1, pos + 2);
			writeTriangle(pos + 1, pos + 3, pos + 2);
		}
		if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		break;
	case GL_POLYGON: // treat polygons as GL_TRIANGLE_FAN
	case GL_TRIANGLE_FAN:
		pos = first + 1;
		for (GLsizei i = 2; i < count; ++i, ++pos)
		{
			writeTriangle(first, pos, pos+1);
		}
		if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
		break;
	case GL_POINTS:
	case GL_LINES:
	case GL_LINE_STRIP:
	case GL_LINE_LOOP:
	default:
		OSG_WARN << "WriterNodeVisitor :: can't handle mode " << mode << std::endl;
		break;
	}
	if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE_SET) ++_curNormalIndex;
}
