#version 430 core

#define ATTRIBUTE_COORDINATE    0       //! Coordinate attribute location.

layout( location = ATTRIBUTE_COORDINATE ) in highp vec3 inCoordinate; //! Input coordinate attribute.

uniform highp mat4 uniProjectionView;   //! Projection view matrix uniform.
uniform highp mat4 uniModel;            //! Model matrix uniform.

uniform highp vec3  uniLightPosition;   //! Light source position uniform.
uniform highp float uniLightRadius;     //! Light radius uniform.

out highp vec4 coordinate;              //! Output coordinate attribute.
out highp vec3 lightPosition;           //! Output light source position uniform.


void main()
{
    highp mat4 projectionViewModel = uniProjectionView * uniModel; // Calculating projection view model matrix.
    coordinate    = projectionViewModel * vec4(inCoordinate * uniLightRadius, 1.0f);// Light mesh coordinate.
    lightPosition = vec4(uniModel * vec4(uniLightPosition, 1.0f) ).xyz;             // Light source position.


    gl_Position = coordinate;
}
