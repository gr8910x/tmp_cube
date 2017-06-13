#version 430 core

#define FRAGMENT_SHADOW  1     //! Fragment shadow location.

layout( location = FRAGMENT_SHADOW  ) out highp vec4 outShadowFragment; //! Output shadow fragment.


void main()
{
    highp float depth = gl_FragCoord.z;
    outShadowFragment = vec4( vec3(depth), 1.0f);
}
