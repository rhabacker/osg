/*
    vertexData.h
    Copyright (c) 2007, Tobias Wolf <twolf@access.unizh.ch>
    All rights reserved.

    Header file of the VertexData class.
*/

/** note, derived from Equalizer LGPL source.*/


#ifndef MESH_VERTEXDATA_H
#define MESH_VERTEXDATA_H


#include <osg/Node>
#include <osg/PrimitiveSet>
#include <osgDB/ReadFile>

#include <vector>

///////////////////////////////////////////////////////////////////////////////
//!
//! \class VertexData
//! \brief helps to read ply file and converts in to osg::Node format
//!
///////////////////////////////////////////////////////////////////////////////

// defined elsewhere
struct PlyFile;

namespace ply
{
    /*  Holds the flat data and offers routines to read, scale and sort it.  */
    class VertexData
    {
    public:
        // Default constructor
        VertexData();

        // Reads ply file and convert in to osg::Node and returns the same
        osg::Node* readPlyFile( const char* file, const bool ignoreColors = false );

        // to set the flag for using inverted face
        void useInvertedFaces() { _invertFaces = true; };

		// set transformation values
		void setTransformation(const osgDB::ReaderWriter::Options* options);

    private:

        enum VertexFields
        {
          NONE = 0,
          XYZ = 1,
          NORMALS = 2,
          RGB = 4,
          AMBIENT = 8,
          DIFFUSE = 16,
          SPECULAR = 32,
          RGBA = 64,
          TEXCOORD = 128
        };

        // Function which reads all the vertices and colors if color info is
        // given and also if the user wants that information
        void readVertices( PlyFile* file, const int nVertices,
                           const int vertexFields );

        // Reads the triangle indices from the ply file
        void readTriangles( PlyFile* file, const int nFaces );

		// Flag if vertex data should be transformed
		void applyTransformation(bool apply) { _transform = apply; };
		// Set X-Offset
		void setOffsetX(double offsetX) { _offsetX = offsetX; };
		// Set Y-Offset
		void setOffsetY(double offsetY) { _offsetY = offsetY; };
		// Set rotation
		void setAlpha(double alpha) 
		{ 
			_alpha = alpha; 
			_cosAlpha = cos(-_alpha);
			_sinAlpha = sin(-_alpha);
		};

		// Transform a vector with transformation params
		void transform(osg::Vec3d& vec);

        bool        _invertFaces;

		/// transformation parameters
		double		_offsetX;
		double		_offsetY;
		double		_alpha;
		bool		_transform;
		// precomputed values based on alpha
		double		_cosAlpha;
		double		_sinAlpha;

        // Vertex array in osg format
        osg::ref_ptr<osg::Vec3Array>   _vertices;
        // Color array in osg format
        osg::ref_ptr<osg::Vec4Array>   _colors;
        osg::ref_ptr<osg::Vec4Array>   _ambient;
        osg::ref_ptr<osg::Vec4Array>   _diffuse;
        osg::ref_ptr<osg::Vec4Array>   _specular;
        osg::ref_ptr<osg::Vec2Array>   _texcoord;

        // Normals in osg format
        osg::ref_ptr<osg::Vec3Array> _normals;
        // The indices of the faces in premitive set
        osg::ref_ptr<osg::DrawElementsUInt> _triangles;
        osg::ref_ptr<osg::DrawElementsUInt> _quads;
    };
}


#endif // MESH_VERTEXDATA_H
