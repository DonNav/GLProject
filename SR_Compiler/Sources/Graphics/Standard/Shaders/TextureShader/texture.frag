precision mediump float;

// Material informations
uniform vec4 uAmbient;
uniform vec4 uDiffuse;
uniform vec4 uEmissive;

uniform sampler2D uTexture;

// Camera informations:
uniform vec3 uCameraPosition;

// Light Informations
uniform vec4 light_position_array;
uniform vec4 light_ambient_array;
uniform vec4 light_diffuse_array;
uniform float light_constantAttenuation_array;
uniform float light_linearAttenuation_array;
uniform float light_quadraticAttenuation_array;
uniform vec4 light_spotDirection_array;

// Varying values
varying vec3 position;
varying vec3 normal;
varying vec2 textureCoordinate;

void main() 
{

	vec3 nNormal = normalize(normal);

        //We compute the light position compare to object position
        vec3 nLight = normalize(light_position_array.xyz - position.xyz);

        // we define two color for color computation
        vec4 color = uEmissive;

        // we compute the angle between the normal and the light position
        // we be used to compute specular exponent
        float angle = max(dot(nNormal, nLight), 0.0);

        vec4 textureColor = texture2D(uTexture,textureCoordinate);

        // Compute the light attenuation -------------------------------------------------------------------------------------------------------------------
         float attenuation = 1.0;
         if (light_constantAttenuation_array!= 0.0 || light_linearAttenuation_array !=0.0 || light_quadraticAttenuation_array != 0.0)
        {
                float len = length(light_position_array.xyz - position.xyz);
                attenuation = 1.0 / (light_constantAttenuation_array +  light_linearAttenuation_array * len + light_quadraticAttenuation_array * len * len);
         }
        // ----------------------------------------------------------------------------------------------------------------------------------------------------
        color += uAmbient*light_ambient_array * attenuation  + angle * textureColor  *light_diffuse_array * attenuation;



	gl_FragColor = vec4(clamp(color.rgb, 0.0, 1.0), uAmbient.a);
}
