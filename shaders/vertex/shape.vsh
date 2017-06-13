#version 430 core

#define ATTRIBUTE_COORDINATE    0       //! Coordinate attribute location.
#define ATTRIBUTE_COLOR         1       //! Color attribute location.
#define ATTRIBUTE_NORMAL        2       //! Normal attribute location.

layout( location = ATTRIBUTE_COORDINATE ) in highp vec3 inCoordinate; //! Input coordinate attribute.
layout( location = ATTRIBUTE_COLOR      ) in lowp  vec4 inColor;      //! Input color attribute.
layout( location = ATTRIBUTE_NORMAL     ) in highp vec3 inNormal;     //! Input normal attribute.

uniform highp mat4 uniProjectionViewModel;//! Projection view model matrix uniform.
uniform highp mat4 uniModel;              //! Model matrix uniform.

out lowp  vec4 color;                   //! Output color attribute.
out highp vec3 normal;                  //! Output normal attribute.


highp vec3 getNormal(in highp vec3 inputNormal, in highp mat4 model); //! Calculates normals.


void main()
{    
    color       =   inColor;
    normal      =   getNormal(inNormal, uniModel);

    gl_Position =   uniProjectionViewModel * vec4(inCoordinate, 1.0f);
}


highp vec3 getNormal(in highp vec3 inputNormal, in highp mat4 model) //! Calculates normals.
{
    highp vec4 tmp = model * vec4(inputNormal, 0.0f);
    return ( normalize(tmp.xyz) + 1.0f ) / 2.0f;      // Transforming normals : [-1, 1] -> [ 0, 1].
}
