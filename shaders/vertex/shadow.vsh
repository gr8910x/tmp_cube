#version 430 core

#define ATTRIBUTE_COORDINATE    0       //! Coordinate attribute location.

layout( location = ATTRIBUTE_COORDINATE ) in highp vec3 inCoordinate; //! Input coordinate attribute.

uniform highp mat4 uniProjectionViewModel;//! Projection view model matrix uniform.


void main()
{
    gl_Position =   uniProjectionViewModel * vec4(inCoordinate, 1.0f);
}
