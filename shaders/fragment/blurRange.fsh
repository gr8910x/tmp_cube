#version 430 core

#define FRAGMENT_COLOR  0   //! Fragment color location.

in highp vec2           texCoordinate;             //! Input texture coordinate attribute.

uniform highp sampler2D uniDepthTexture2D;         //! Depth 2D texture uniform.
uniform lowp  sampler2D uniDiffuseLightCombined2D; //! Diffuse light combined 2D texture uniform.

uniform highp mat4      uniInvProjection;          //! Inverse projection matrix uniform.

uniform highp float     uniFocalDistance;          //! Focal distance uniform.
uniform highp float     uniFocalRange;             //! Focal range uniform.

layout( location = FRAGMENT_COLOR ) out lowp vec4 outColorFragment;   //! Output fragment color.


void main()
{
    texture(uniDepthTexture2D, texCoordinate);
    texture(uniDiffuseLightCombined2D, texCoordinate);
    uniInvProjection + 0.0f;
    uniFocalDistance + 0.0f;
    uniFocalRange    + 0.0f;

    outColorFragment = vec4(texCoordinate, 1.0f, 1.0f);
}
