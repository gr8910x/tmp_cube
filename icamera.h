#ifndef ICAMERA_H
#define ICAMERA_H

#include "commonincludings.h"

//! Interface for OpenGL Scene 3D space camera implementation.
class ICamera
{
public:
    virtual ~ICamera() {}

protected:
    virtual const QMatrix4x4 & calculateView() = 0;           //! Calculates camera view matrix and returns it.
    virtual const QMatrix4x4 & calculateProjection() = 0;     //! Calculates camera projection matrix and returns it.
    virtual const QMatrix4x4 & calculateProjectionView() = 0; //! Calculates camera projection view matrix and returns it.
};

#endif // ICAMERA_H
