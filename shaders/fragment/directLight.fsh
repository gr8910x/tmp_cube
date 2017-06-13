#version 430 core

#define FRAGMENT_LIGHT  0               //! Fragment light location.

in highp vec2 texCoordinate;            //! Input coordinate attribute.

uniform highp mat4 uniInvProjectionView;   //! Inverse projection view uniform.
uniform highp mat4 uniShadowProjectionView;//! Shadow projection view matrix.

uniform highp vec3 uniLightDirection;   //! Light direction uniform.
uniform lowp  vec4 uniLightColor;       //! Light color uniform.

uniform highp sampler2D uniNormalsTexture2D;  //! Normals 2D texture uniform.
uniform highp sampler2D uniDepthTexture2D;    //! Depth 2D texture uniform.
uniform highp sampler2D uniShadowTexture2D;   //! Shadow 2D texture uniform.

layout( location = FRAGMENT_LIGHT ) out highp vec4 outLightFragment; //! Output fragment light.


highp float getShadow(in highp vec3 worldCoordinates, in highp mat4 shadowProjectionView, in highp sampler2D shadowTexture2D); //! Calculates and returns shadow factor.
highp vec3 getWorldCoordinates(in highp mat4 inverseProjectionView,  in highp vec3 ndcCoordinates);//! Calculates and returns world coordinates.


void main()
{
    highp vec3 ndcCoordinates   = vec3( texCoordinate * 2.0f - 1.0f     // Receiving NDC x, y & z coordinates : [-1, 1 ].
                                      , texture(uniDepthTexture2D, texCoordinate).s * 2.0f - 1.0f );
    highp vec3 worldCoordinates = getWorldCoordinates(uniInvProjectionView, ndcCoordinates);    // Restoring world space x, y & z coordinates.
    highp vec3 normal           = texture(uniNormalsTexture2D, texCoordinate).stp * 2.0f - 1.0f;// Receiving x, y & z normal coordinates : [-1, 1 ].


    highp vec3 lightDir         = normalize(vec3(0.0f) - uniLightDirection);// Identity vector towards light source.
    highp vec3 cameraDir        = normalize(vec3(0.0f) + worldCoordinates);// Identity vector towards camera position { 0.0f, 0.0f, 0.0f }.

    highp float diffuseLight    = max(0.0f, dot(lightDir, normal));        // Calculating diffuse light.


    highp float attenuation     = (ndcCoordinates.z < 1.0f) ? 1.0f : 0.0f; // Light attenuation coefficient.


    highp float shadow = getShadow(worldCoordinates, uniShadowProjectionView, uniShadowTexture2D); // Getting shadow factor.

    highp vec4 lightFragment = vec4( 1.0f, 1.0f, 1.0f, 1.0f);  // Output light color.
    lightFragment = ( ndcCoordinates.z < 1.0f ) ?  vec4( vec3(diffuseLight + 0.0f)
                                                       * uniLightColor.rgb
                                                       * shadow
                                                       * attenuation
                                                       , 1.0f )
                                                       //* attenuation
                                                :  vec4( 1.0f );
    //if( ndcCoordinates.z < 1.0f && ndcCoordinates.z > -1.0f )
    //{
    //    lightFragment  = vec4(vec3(shadow), 1.0f);
    //}

    outLightFragment = lightFragment;
}

highp float getShadow( in highp vec3 worldCoordinates       //! Calculates and returns shadow factor.
                     , in highp mat4 shadowProjectionView
                     , in highp sampler2D shadowTexture2D )
{
    highp float shadow = 0.0f;

    highp vec4  cameraShadowNDCCoordinates = vec4( shadowProjectionView * vec4(worldCoordinates, 1.0f));  // Calculating camera to light coordinates from light point of view : [-1. 1].
    cameraShadowNDCCoordinates /= cameraShadowNDCCoordinates.w;

    highp float cameraShadowDepth = cameraShadowNDCCoordinates.z;  // Camera shadow depth : [-1, 1].
    highp vec2  shadowTexture2DCoordinates = cameraShadowNDCCoordinates.xy * 0.5f + 0.5f; // Shadow map texture 2D coordinates : [ 0, 1].

    highp float lightShadowDepth = texture(shadowTexture2D, shadowTexture2DCoordinates).p * 2.0f - 1.0f; // Light shadow depth : [-1, 1].

    shadow = ( cameraShadowDepth - 0.05f > lightShadowDepth ) ? 0.5f
                                                              : 1.0f;
    //shadow = lightShadowDepth;

    return shadow;
}

highp vec3 getWorldCoordinates(in highp mat4 inverseProjectionView,  in highp vec3 ndcCoordinates) //! Calculates and returns world coordinates.
{
    highp vec4 worldCoordinates = inverseProjectionView * vec4(ndcCoordinates, 1.0f);

    return worldCoordinates.xyz / worldCoordinates.w;
}
