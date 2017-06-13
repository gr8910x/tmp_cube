#version 430 core

#define FRAGMENT_LIGHT  0           //! Fragment light location.

in highp vec4 coordinate;           //! Input coordinate attribute.
in highp vec3 lightPosition;        //! Input light source position uniform.

uniform highp mat4  uniInvProjectionView;//! Inverse projection view uniform.

uniform lowp  vec4  uniLightColor;       //! Light color uniform.
uniform highp float uniLightRadius;      //! Light radius uniform.

uniform highp sampler2D uniNormalsTexture2D;  //! Normals 2D texture uniform.
uniform highp sampler2D uniDepthTexture2D;    //! Depth 2D texture uniform.

layout( location = FRAGMENT_LIGHT ) out lowp  vec4 outLightFragment;   //! Output fragment light.


highp vec3 getWorldCoordinates(in highp mat4 inverseProjectionView, in highp vec3 ndcCoordinates);//! Calculates and returns world coordinates.
highp vec2 getTexture2DCoordinates(in highp vec4 meshCoordinates);                                //! Calculates and returns 2D texture x & y coordinates : [ 0, 1 ].
highp vec3 getNDCCoordinates(in highp sampler2D depthTexture, in highp vec2 texture2DCoordinates);//! Calculates and returns NDC x, y & z coordinates : [-1, 1 ].
highp vec3 getNormal(in highp sampler2D normalsTexture, in highp vec2 texture2DCoordinates);      //! Returns x, y & z normals coordinates : [-1, 1 ].


void main()
{
    highp vec2 texCoordinates   = getTexture2DCoordinates(coordinate);                 // Receiving texture x & y coordinates : [ 0, 1 ].
    highp vec3 ndcCoordinates   = getNDCCoordinates(uniDepthTexture2D, texCoordinates);// Receiving NDC x, y & z coordinates : [-1, 1 ].
    highp vec3 worldCoordinates = getWorldCoordinates(uniInvProjectionView, ndcCoordinates);// Restoring world space x, y & z coordinates.
    highp vec3 normal           = getNormal(uniNormalsTexture2D, texCoordinates);      // Receiving x, y & z normal coordinates : [-1, 1 ].


    highp vec3 lightDir         = normalize(lightPosition - worldCoordinates);         // Identity vector towards light source.
    highp vec3 cameraDir        = normalize(vec3(0.0f)    + worldCoordinates);         // Identity vector towards camera position { 0.0f, 0.0f, 0.0f }.
    highp vec3 halfDir          = normalize(lightDir + cameraDir);                     // Identity half vector.

    highp float diffuseLight     = max(0.0f, dot(lightDir, normal));                   // Calculating diffuse light.
    highp float specPower        = 10.0f;                                              // Specular light power.
    highp float specularLight    = pow(max(0.0f, dot(halfDir, normal)), specPower);    // Calculating specular light.
    /*
    float   diff = max         ( 0.2, dot ( l, n ) );
    float   spec = pow         ( max ( 0.0, dot ( h, n ) ), 40.0 );
    gl_FragColor = vec4 ( vec3 ( diff + spec ), 1.0 );
    */
    /*
    vec4 diff = diffColor * max ( dot ( n2, l2 ), 0.0 );
    vec4 spec = specColor * pow ( max ( dot ( n2, h2 ), 0.0 ), specPower );
    gl_FragColor = diff + spec;
    */
    /*
    outLightFragment = vec4( (ndcCoordinates.stp + 1) / 2  //vec4(lightRadius / 2, 1.0f);
                           //, 0.0f
                           , 1.0f );
    */
    highp float attenuation = (ndcCoordinates.z < 1.0f) ? 1.0f : 0.0f;                 // Light attenuation coefficient.

    outLightFragment = ( ndcCoordinates.z < 1.0f ) ?  vec4( vec3(diffuseLight + 0.0f)
                                                          * uniLightColor.rgb
                                                          * attenuation
                                                          , 1.0f )
                                                    //* attenuation
                                                   :  vec4( 1.0f );

}


highp vec3 getWorldCoordinates(in highp mat4 inverseProjectionView, in highp vec3 ndcCoordinates)//! Calculates and returns world coordinates.
{
    highp vec4 worldCoordinates = inverseProjectionView * vec4(ndcCoordinates, 1.0f);

    return worldCoordinates.xyz / worldCoordinates.w;
}

highp vec2 getTexture2DCoordinates(in highp vec4 meshCoordinates) //! Calculates and returns 2D texture coordinates : [ 0, 1 ].
{
    return ( meshCoordinates.xy / meshCoordinates.w + 1.0f ) / 2.0f;
}

highp vec3 getNDCCoordinates(in highp sampler2D depthTexture, in highp vec2 texture2DCoordinates)//! Calculates and returns NDC x, y & z coordinates : [-1, 1 ].
{
    return vec3( texture2DCoordinates * 2.0f - 1.0f
               , texture(depthTexture, texture2DCoordinates).s * 2.0f - 1.0f );
}

highp vec3 getNormal(in highp sampler2D normalsTexture, in highp vec2 texture2DCoordinates)      //! Returns x, y & z normals coordinates : [-1, 1 ].
{
    return texture(normalsTexture, texture2DCoordinates).stp * 2.0f - 1.0f;
}


