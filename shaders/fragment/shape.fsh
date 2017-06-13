#version 430 core

#define FRAGMENT_DIFFUSE  0     //! Fragment diffuse location.
#define FRAGMENT_NORMAL   1     //! Fragment normal location.
#define FRAGMENT_DEPTH    2     //! Fragment depth location.

in lowp  vec4 color;            //! Input color attribute.
in highp vec3 normal;           //! Input normal attribute.

layout( location = FRAGMENT_DIFFUSE  ) out highp vec4 outDiffuseFragment; //! Output fragment diffuse.
layout( location = FRAGMENT_NORMAL   ) out highp vec4 outNormalFragment;  //! Output fragment normal.
layout( location = FRAGMENT_DEPTH    ) out highp vec4 outDepthFragment;   //! Output fragment depth.

void main()
{
    outDiffuseFragment = color;
    outNormalFragment  = vec4(normal, 1.0f);
    outDepthFragment   = vec4( vec3(gl_FragCoord.z), 1.0f);
}
