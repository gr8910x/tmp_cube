#version 430 core

#define FRAGMENT_COLOR  0   //! Fragment color location.

in highp vec2           texCoordinate;      //! Input texture coordinate attribute.

uniform highp sampler2D uniSomeTexture2D;   //! Some 2D texture uniform.

layout( location = FRAGMENT_COLOR ) out lowp  vec4 outColorFragment;   //! Output fragment color.

void main()
{
    outColorFragment =  texture(uniSomeTexture2D, texCoordinate);
}
