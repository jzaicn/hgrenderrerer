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

/** writes all primitives of a primitive-set out to a stream, decomposes quads to triangles, line-strips to lines etc */
class PrimitiveIndexWriter : public osg::PrimitiveIndexFunctor
{
public:
	PrimitiveIndexWriter(const osg::Geometry* inputGeometory,
		ListTriangle&        outTriangleVec,
		unsigned int         sectionIndex,
		unsigned int         material) :
	_sectionIndex(sectionIndex),
		_listTriangles(outTriangleVec),
		_GLDrawModeCache(0),
		_hasNormalCoords(inputGeometory->getNormalArray() != NULL),
		_hasTexCoords(inputGeometory->getTexCoordArray(0) != NULL),
		_geometory(inputGeometory),
		_lastFaceIndex(0),
		_curNormalIndex(0),
		_material(material),
		_normalBinding(inputGeometory->getNormalBinding())
	{
		if (!inputGeometory->getNormalArray() || inputGeometory->getNormalArray()->getNumElements()==0)
		{
			_normalBinding = osg::Geometry::BIND_OFF;        // Turn off binding if there is no normal data
		}
		reset();
	}

	void reset() { _curNormalIndex = 0; }

	unsigned int getNextFaceIndex() { return _lastFaceIndex; }

	virtual void setVertexArray(unsigned int, const osg::Vec2*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec3*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec4*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec2d*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec3d*) {}

	virtual void setVertexArray(unsigned int, const osg::Vec4d*) {}

	// operator for triangles
	void writeTriangle(unsigned int i1, unsigned int i2, unsigned int i3);

	virtual void begin(GLenum mode)
	{
		_GLDrawModeCache = mode;
		_indexCache.clear();
	}

	virtual void vertex(unsigned int vert)
	{
		_indexCache.push_back(vert);
	}

	virtual void end()
	{
		if (!_indexCache.empty())
		{
			drawElements(_GLDrawModeCache, _indexCache.size(), &_indexCache.front());
		}
	}

	virtual void drawArrays(GLenum mode, GLint first, GLsizei count);

	virtual void drawElements(GLenum mode, GLsizei count, const GLubyte* indices)
	{
		drawElementsImplementation<GLubyte>(mode, count, indices);
	}

	virtual void drawElements(GLenum mode, GLsizei count, const GLushort* indices)
	{
		drawElementsImplementation<GLushort>(mode, count, indices);
	}

	virtual void drawElements(GLenum mode, GLsizei count, const GLuint* indices)
	{
		drawElementsImplementation<GLuint>(mode, count, indices);
	}

protected:

	template <typename T> void drawElementsImplementation(GLenum mode, GLsizei count, const T* indices)
	{
		if (indices==0 || count==0) return;

		typedef const T* IndexPointer;

		switch (mode)
		{
		case GL_TRIANGLES:
			{
				IndexPointer ilast = indices + count;
				for (IndexPointer iptr = indices; iptr < ilast; iptr+=3)
				{
					writeTriangle(iptr[0], iptr[1], iptr[2]);
					if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				}
				break;
			}
		case GL_TRIANGLE_STRIP:
			{
				IndexPointer iptr = indices;
				for (GLsizei i = 2; i < count; ++i, ++iptr)
				{
					if (i & 1) writeTriangle(iptr[0], iptr[2], iptr[1]);
					else       writeTriangle(iptr[0], iptr[1], iptr[2]);
				}
				if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				break;
			}
		case GL_QUADS:
			{
				IndexPointer iptr = indices;
				for (GLsizei i = 3; i < count; i += 4, iptr += 4)
				{
					writeTriangle(iptr[0], iptr[1], iptr[2]);
					writeTriangle(iptr[0], iptr[2], iptr[3]);
					if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				}
				break;
			}
		case GL_QUAD_STRIP:
			{
				IndexPointer iptr = indices;
				for (GLsizei i = 3; i < count; i += 2, iptr += 2)
				{
					writeTriangle(iptr[0], iptr[1], iptr[2]);
					writeTriangle(iptr[1], iptr[3], iptr[2]);
				}
				if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				break;
			}
		case GL_POLYGON: // treat polygons as GL_TRIANGLE_FAN
		case GL_TRIANGLE_FAN:
			{
				IndexPointer iptr = indices;
				unsigned int first = *iptr;
				++iptr;
				for (GLsizei i = 2; i < count; ++i, ++iptr)
				{
					writeTriangle(first, iptr[0], iptr[1]);
				}
				if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE) ++_curNormalIndex;
				break;
			}
		case GL_POINTS:
		case GL_LINES:
		case GL_LINE_STRIP:
		case GL_LINE_LOOP:
			// Not handled
			break;
		default:
			// uhm should never come to this point :)
			break;
		}
		if (_normalBinding == osg::Geometry::BIND_PER_PRIMITIVE_SET) ++_curNormalIndex;
	}

private:
	PrimitiveIndexWriter& operator = (const PrimitiveIndexWriter&); // { return *this; }

	unsigned int         _sectionIndex;
	ListTriangle&        _listTriangles;
	GLenum               _GLDrawModeCache;
	std::vector<GLuint>  _indexCache;
	bool                 _hasNormalCoords, _hasTexCoords;
	const osg::Geometry* _geometory;
	unsigned int         _lastFaceIndex;
	unsigned int         _curNormalIndex;
	unsigned int		 _material;
	osg::Geometry::AttributeBinding _normalBinding;
};
