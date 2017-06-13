#version 430 core

#define ATTRIBUTE_COORDINATE    0       //! Coordinate attribute location.

layout( location = ATTRIBUTE_COORDINATE ) in highp vec3 inTexCoordinate; //! Input texture coordinate attribute.

out highp vec2  texCoordinate;          // Output texture coordinate attribute.

void main()
{
    texCoordinate  =  vec2(inTexCoordinate.x, inTexCoordinate.y);

    gl_Position    =  vec4( 2.0f * texCoordinate - 1.0f, 0.0f, 1.0f ); // Transforming texture coordinates to world coordinates : [ 0, 1] -> [-1, 1].
}
