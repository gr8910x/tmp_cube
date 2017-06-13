#ifndef COMMONSHAPES_H
#define COMMONSHAPES_H

#include <functional>
#include <cstdint>

#include "openglapifunctions.h"

#include <QVector>
#include <QVector3D>
#include <QVector4D>
#include <QList>
#include <QtMath>
#include <QMap>
#include <QHash>

#include "auxiliary.h"
#include "mesh.h"
#include "vertex.h"
#include "index.h"

namespace common_shapes               //! Namespace for common shapes vertices used in the program.
{
    std::function<Mesh (QVector4D, QString)> cube = [] (QVector4D color, QString description) -> Mesh {    //! Cube mesh lambda with center in { 0.0f, 0.0f, 0.0f }.
        Mesh cubeMesh( { Vertex({-1.0f, -1.0f, -1.0f}, color, { 0.0f,  0.0f, -1.0f})  // Cube back verge.
                       , Vertex({-1.0f,  1.0f, -1.0f}, color, { 0.0f,  0.0f, -1.0f})
                       , Vertex({ 1.0f,  1.0f, -1.0f}, color, { 0.0f,  0.0f, -1.0f})
                       , Vertex({ 1.0f, -1.0f, -1.0f}, color, { 0.0f,  0.0f, -1.0f})

                       , Vertex({ 1.0f,  1.0f,  1.0f}, color, { 0.0f,  0.0f,  1.0f})  // Cube front verge.
                       , Vertex({-1.0f,  1.0f,  1.0f}, color, { 0.0f,  0.0f,  1.0f})
                       , Vertex({-1.0f, -1.0f,  1.0f}, color, { 0.0f,  0.0f,  1.0f})
                       , Vertex({ 1.0f, -1.0f,  1.0f}, color, { 0.0f,  0.0f,  1.0f})

                       , Vertex({-1.0f,  1.0f,  1.0f}, color, {-1.0f,  0.0f,  0.0f})  // Cube left verge.
                       , Vertex({-1.0f,  1.0f, -1.0f}, color, {-1.0f,  0.0f,  0.0f})
                       , Vertex({-1.0f, -1.0f, -1.0f}, color, {-1.0f,  0.0f,  0.0f})
                       , Vertex({-1.0f, -1.0f,  1.0f}, color, {-1.0f,  0.0f,  0.0f})

                       , Vertex({ 1.0f,  1.0f,  1.0f}, color, { 1.0f,  0.0f,  0.0f})  // Cube right verge.
                       , Vertex({ 1.0f, -1.0f,  1.0f}, color, { 1.0f,  0.0f,  0.0f})
                       , Vertex({ 1.0f, -1.0f, -1.0f}, color, { 1.0f,  0.0f,  0.0f})
                       , Vertex({ 1.0f,  1.0f, -1.0f}, color, { 1.0f,  0.0f,  0.0f})

                       , Vertex({-1.0f,  1.0f,  1.0f}, color, { 0.0f,  1.0f,  0.0f})  // Cube upper verge.
                       , Vertex({ 1.0f,  1.0f,  1.0f}, color, { 0.0f,  1.0f,  0.0f})
                       , Vertex({ 1.0f,  1.0f, -1.0f}, color, { 0.0f,  1.0f,  0.0f})
                       , Vertex({-1.0f,  1.0f, -1.0f}, color, { 0.0f,  1.0f,  0.0f})

                       , Vertex({-1.0f, -1.0f,  1.0f}, color, { 0.0f, -1.0f,  0.0f})  // Cube lower verge.
                       , Vertex({-1.0f, -1.0f, -1.0f}, color, { 0.0f, -1.0f,  0.0f})
                       , Vertex({ 1.0f, -1.0f, -1.0f}, color, { 0.0f, -1.0f,  0.0f})
                       , Vertex({ 1.0f, -1.0f,  1.0f}, color, { 0.0f, -1.0f,  0.0f})
                       }
                     , { Index(0),  Index(1),  Index(2),  Index(0),  Index(2),  Index(3)  // Cube back verge indices.
                       , Index(4),  Index(5),  Index(6),  Index(4),  Index(6),  Index(7)  // Cube front verge indices.
                       , Index(8),  Index(9),  Index(10), Index(8),  Index(10), Index(11) // Cube left verge indices.
                       , Index(12), Index(13), Index(14), Index(12), Index(14), Index(15) // Cube right verge indices.
                       , Index(16), Index(17), Index(18), Index(16), Index(18), Index(19) // Cube upper verge indices.
                       , Index(20), Index(21), Index(22), Index(20), Index(22), Index(23) // Cube lower verge indices.
                       }
                     , GL_TRIANGLES
                     , description
                     );

        return cubeMesh;
    };

    std::function<Mesh (uint, QVector4D, QString)> sphere = [] (uint recursionLevel, QVector4D color, QString description) -> Mesh {  //! Sphere (icosahedron -> icosphere) mesh lambda with center in { 0.0f, 0.0f, 0.0f } and radius 1.

        QVector<Vertex>   vertices;           // Vertices.
        QVector<Index>    indices;            // Indices.
        uint              index      = 0;     // Current index.
        Mesh              mesh;               // Sphere mesh.

        QHash<std::uint64_t, uint> middlePointIndexCache; // Cache of middle points indices.

        std::function<uint(QVector3D)> addVertex = [&index, &vertices, color] (QVector3D point3D) -> uint {  //! Adds vertex, returns its index.
            const QVector3D &coordinate =   aux_funcs::normalize(point3D); //  Coordinate.
            const QVector3D &normal     =   coordinate;                    //  Normal.

            vertices << Vertex( coordinate, color, normal );               //  Pushing new vertex to vertices.

            return index ++;
        };

        std::function<uint (uint, uint)> getMiddlePoint = [&middlePointIndexCache, &vertices, &addVertex](uint pointIndexOne, uint pointIndexTwo) -> uint {  //! Gets middle point, returns its index.
            bool pointIndexOneSmaller = pointIndexOne < pointIndexTwo;

            std::uint64_t smallerIndex = pointIndexOneSmaller ? pointIndexOne : pointIndexTwo;
            std::uint64_t biggerIngex  = pointIndexOneSmaller ? pointIndexTwo : pointIndexOne;
            std::uint64_t key = (static_cast<std::uint64_t>(smallerIndex) << 32) + static_cast<std::uint64_t>(biggerIngex);

            QHash<std::uint64_t, uint>::iterator it = middlePointIndexCache.find(key);  // Checking if value already exists.
            if( it != middlePointIndexCache.end() )
            {
                return it.value();   // Returning it if exists.
            }
            else
            {
                const QVector3D &pointOne = vertices[pointIndexOne].getCoordinates();
                const QVector3D &pointTwo = vertices[pointIndexTwo].getCoordinates();
                QVector3D middlePoint = (pointOne + pointTwo) / 2.0f;       // Calculating middle point.

                uint index = addVertex(middlePoint);                        // Adding middle point.

                middlePointIndexCache.insert(key, index);                   // Inserting index to cache.

                return index;
            }
        };

        std::function<void (uint)> create = [&indices, &getMiddlePoint, &addVertex] (uint recursionLevel) -> void {   //! Creates sphere mesh.
            float t = (1.0f + sqrtf(5.0f)) / 2.0f;

            addVertex( QVector3D(-1, t, 0) );    // Creating 12 vertices of icosahedron.
            addVertex( QVector3D( 1, t, 0) );
            addVertex( QVector3D(-1,-t, 0) );
            addVertex( QVector3D( 1,-t, 0) );

            addVertex( QVector3D( 0,-1, t) );
            addVertex( QVector3D( 0, 1, t) );
            addVertex( QVector3D( 0,-1,-t) );
            addVertex( QVector3D( 0, 1,-t) );

            addVertex( QVector3D( t, 0,-1) );
            addVertex( QVector3D( t, 0, 1) );
            addVertex( QVector3D(-t, 0,-1) );
            addVertex( QVector3D(-t, 0, 1) );

            QVector<Index> faces;
            faces << Index(0)  << Index(11) << Index(5)     // Indices.
                  << Index(0)  << Index(5)  << Index(1)
                  << Index(0)  << Index(1)  << Index(7)
                  << Index(0)  << Index(7)  << Index(10)
                  << Index(0)  << Index(10) << Index(11)

                  << Index(1)  << Index(5)  << Index(9)
                  << Index(5)  << Index(11) << Index(4)
                  << Index(11) << Index(10) << Index(2)
                  << Index(10) << Index(7)  << Index(6)
                  << Index(7)  << Index(1)  << Index(8)

                  << Index(3)  << Index(9)  << Index(4)
                  << Index(3)  << Index(4)  << Index(2)
                  << Index(3)  << Index(2)  << Index(6)
                  << Index(3)  << Index(6)  << Index(8)
                  << Index(3)  << Index(8)  << Index(9)

                  << Index(4)  << Index(9)  << Index(5)
                  << Index(2)  << Index(4)  << Index(11)
                  << Index(6)  << Index(2)  << Index(10)
                  << Index(8)  << Index(6)  << Index(7)
                  << Index(9)  << Index(8)  << Index(1);

            for( uint i = 0; i < recursionLevel; ++i )
            {
                QVector<Index> facesTwo;
                for( int j = 0; j < faces.length(); j+=3 )
                {
                    uint a = getMiddlePoint(faces[j + 0].getIndex(), faces[j + 1].getIndex() );
                    uint b = getMiddlePoint(faces[j + 1].getIndex(), faces[j + 2].getIndex() );
                    uint c = getMiddlePoint(faces[j + 2].getIndex(), faces[j + 0].getIndex() );

                    facesTwo << faces[j + 0] << Index(a) << Index(c)
                             << faces[j + 1] << Index(b) << Index(a)
                             << faces[j + 2] << Index(c) << Index(b)
                             << Index(a)     << Index(b) << Index(c);
                }

                faces.clear();
                for( int j = 0; j < facesTwo.size(); j+=3 )
                {
                    faces << facesTwo[j + 0]
                          << facesTwo[j + 1]
                          << facesTwo[j + 2];
                }
            }

            indices = faces;

        };

        create(recursionLevel);      // Creating icosahedron (icosphere) mesh.

        mesh.setVertices(vertices);
        mesh.setIndices(indices);
        mesh.setMode(GL_TRIANGLES);
        mesh.setDescription(description);

        return mesh;
    };

    std::function<Mesh (QVector4D, QString)> square = [] (QVector4D color, QString description) -> Mesh { //! Square mesh lambda with center in { 0.0f, 0.0f, 0.0f } in x & y plane.
        Mesh squareMesh( { Vertex({ 1.0f,  1.0f, 0.0f}, color, { 0.0f, 0.0f, 1.0f})
                         , Vertex({-1.0f,  1.0f, 0.0f}, color, { 0.0f, 0.0f, 1.0f})
                         , Vertex({-1.0f, -1.0f, 0.0f}, color, { 0.0f, 0.0f, 1.0f})
                         , Vertex({ 1.0f, -1.0f, 0.0f}, color, { 0.0f, 0.0f, 1.0f})
                         }
                       , { Index(0),  Index(1),  Index(2),  Index(0),  Index(2),  Index(3)
                         }
                       , GL_TRIANGLES
                       , description
                       );

        return squareMesh;
    };
}

namespace com_shapes = common_shapes; //! Shorter alias for common shapes namespace.

#endif // COMMONSHAPES_H
