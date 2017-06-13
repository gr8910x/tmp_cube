#ifndef ILIGHT_H
#define ILIGHT_H

#include "commonincludings.h"

class Renderer;

//! Interface for light implementation.
class ILight
{
public:
    virtual com_defs::LightType getType() const = 0;             //! Returns light type.
    virtual void draw(Renderer *renderer) noexcept(false) = 0;   //! Draws into light buffer.

    virtual ~ILight() {}
};

#endif // ILIGHT_H
