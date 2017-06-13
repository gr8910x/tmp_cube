#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QVector4d>

#include "openglapifunctions.h"

namespace auxiliary_functions                                   //! Namespace for OpenGL utility functions.
{
    // Vectors operations section.
    QVector2D & normalize(QVector2D &vector);                   //! Normalizes given 2D vector and returns it.
    QVector3D & normalize(QVector3D &vector);                   //! Normalizes given 3D vector and returns it.
    QVector4D & normalize(QVector4D &vector);                   //! Normalizes given 4D vector and returns it.

    QVector<QVector2D> & normalize(QVector<QVector2D> &vectors);//! Normalizes given 2D vectors and returns them.
    QVector<QVector3D> & normalize(QVector<QVector3D> &vectors);//! Normalizes given 3D vectors and returns them.
    QVector<QVector4D> & normalize(QVector<QVector4D> &vectors);//! Normalizes given 4D vectors and returns them.


    // GLEW section.
    GLenum initGLEW();                                          //! Initializes GLEW library.
}
namespace aux_funcs = auxiliary_functions;                      //! Shorter alias for opengl_utility_functions namespace.


#endif // AUXILIARY_H
