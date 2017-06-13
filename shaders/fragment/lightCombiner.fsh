#version 430 core

#define FRAGMENT_COLOR  0                   //! Fragment color location.

in highp vec2 texCoordinate;                //! Input texture coordinate attribute.

uniform highp sampler2D uniDiffuseTexture2D;//! Diffuse 2D texture uniform.
uniform highp sampler2D uniLightTexture2D;  //! Light 2D texture uniform.

layout( location = FRAGMENT_COLOR ) out lowp vec4 outColorFragment; //! Output fragment color.

void main()
{
    outColorFragment =  texture(uniDiffuseTexture2D, texCoordinate) //! Combining light & diffuse.
                      * texture(uniLightTexture2D, texCoordinate);
}
