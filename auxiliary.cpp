#include <iostream>
#include "auxiliary.h"

namespace auxiliary_functions
{
    GLenum initGLEW()
    {
        GLenum initStatus = glewInit();         // Initializing GLEW.        

        return initStatus;
    }

    QVector3D & normalize(QVector3D &vector)
    {
        const float normalX = vector.x();
        const float normalY = vector.y();
        const float normalZ = vector.z();

        const float normalLength = sqrtf( normalX * normalX
                                        + normalY * normalY
                                        + normalZ * normalZ );
        float normalizedX = 0.0f;
        float normalizedY = 0.0f;
        float normalizedZ = 0.0f;

        if( normalLength > 0 )
        {
            normalizedX = normalX / normalLength;
            normalizedY = normalY / normalLength;
            normalizedZ = normalZ / normalLength;
        }

        vector.setX(normalizedX);
        vector.setY(normalizedY);
        vector.setZ(normalizedZ);

        return vector;
    }

    QVector2D & normalize(QVector2D &vector)
    {
        const float normalX = vector.x();
        const float normalY = vector.y();

        const float normalLength = sqrtf( normalX * normalX
                                        + normalY * normalY );
        float normalizedX = 0.0f;
        float normalizedY = 0.0f;

        if( normalLength > 0 )
        {
            normalizedX = normalX / normalLength;
            normalizedY = normalY / normalLength;
        }

        vector.setX(normalizedX);
        vector.setY(normalizedY);

        return vector;
    }

    QVector4D & normalize(QVector4D &vector)
    {
        const float normalX = vector.x();
        const float normalY = vector.y();
        const float normalZ = vector.z();
        const float normalW = vector.w();

        const float normalLength = sqrtf( normalX * normalX
                                        + normalY * normalY
                                        + normalZ * normalZ
                                        + normalW * normalW );
        float normalizedX = 0.0f;
        float normalizedY = 0.0f;
        float normalizedZ = 0.0f;
        float normalizedW = 0.0f;

        if( normalLength > 0 )
        {
            normalizedX = normalX / normalLength;
            normalizedY = normalY / normalLength;
            normalizedZ = normalZ / normalLength;
            normalizedW = normalW / normalLength;
        }

        vector.setX(normalizedX);
        vector.setY(normalizedY);
        vector.setZ(normalizedZ);
        vector.setW(normalizedW);

        return vector;
    }

    QVector<QVector2D> & normalize(QVector<QVector2D> &vectors)
    {
        for( QVector<QVector2D>::iterator it = vectors.begin(); it != vectors.end(); ++it )
        {
            normalize(*it);
        }

        return vectors;
    }

    QVector<QVector3D> & normalize(QVector<QVector3D> &vectors)
    {
        for( QVector<QVector3D>::iterator it = vectors.begin(); it != vectors.end(); ++it )
        {
            normalize(*it);
        }

        return vectors;
    }

    QVector<QVector4D> & normalize(QVector<QVector4D> &vectors)
    {
        for( QVector<QVector4D>::iterator it = vectors.begin(); it != vectors.end(); ++it )
        {
            normalize(*it);
        }

        return vectors;
    }

}
