#ifndef ISHAPE_H
#define ISHAPE_H

#include "commonincludings.h"

class Camera;

//! Interface for OpenGL shape implementation.
class IShape
{
public:
    virtual void draw(const Camera *camera) noexcept(false) = 0;      //! Draws shape.
    virtual void drawShadow(const Camera *camera) noexcept(false) = 0;//! Draws shape shadow to texture.

    virtual ~IShape() {}
};

#endif // ISHAPE_H
