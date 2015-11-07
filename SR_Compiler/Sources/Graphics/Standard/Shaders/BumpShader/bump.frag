precision mediump float;

// Material informations
uniform vec4 uAmbient;
uniform vec4 uDiffuse;
uniform vec4 uSpecular;
uniform vec4 uEmissive;

uniform float uGloss;
uniform float uReflectivity;
uniform float uRefraction;

uniform sampler2D uTexture;
uniform sampler2D uBumpTexture;

// Camera informations:
uniform vec3 uCameraPosition;

// Light Informations
uniform vec4 light_position_array;
uniform vec4 light_ambient_array;
uniform vec4 light_diffuse_array;
uniform vec4 light_specular_array;
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
	vec4 colorFinal = vec4(0.0,0.0,0.0,1.0);

	vec3 nNormal = normalize(normal);
	vec3 nCamera = normalize(uCameraPosition.xyz - position.xyz);
	
        //We compute the light position compare to object position
        vec3 nLight = normalize(light_position_array.xyz - position.xyz);

        // we define two color for color computation
        vec4 color = uEmissive;
        vec4 scolor = vec4(0.0,0.0,0.0,1.0);


        vec4 diffuse = texture2D(uTexture,textureCoordinate) +uDiffuse;

        vec3 nModifNormal = normalize(texture2D(uBumpTexture, textureCoordinate).xyz * 2.0 - 1.0);
        vec3 nBumpNormal = nNormal ;
        if (nModifNormal.r > 0.01 && nModifNormal.g > 0.01 && nModifNormal.b > 0.01){
                nBumpNormal = nNormal *  nModifNormal;
        }

        // we compute the angle between the normal and the light position
        // we be used to compute specular exponent
        float angle = max(dot(nBumpNormal, nLight), 0.0);

        // Compute the light attenuation -------------------------------------------------------------------------------------------------------------------
         float attenuation = 1.0;
         if (light_constantAttenuation_array!= 0.0 || light_linearAttenuation_array !=0.0 || light_quadraticAttenuation_array != 0.0)
        {
                float len = length(light_position_array.xyz - position.xyz);
                attenuation = 1.0 / (light_constantAttenuation_array +  light_linearAttenuation_array * len + light_quadraticAttenuation_array * len * len);
         }
        // ----------------------------------------------------------------------------------------------------------------------------------------------------
        color += uAmbient*light_ambient_array * attenuation  + angle * diffuse*light_diffuse_array * attenuation;

        // Calculate the specular light components. ---------------------------------------------------------------------------------------------------------
         if (angle != 0.0 && uGloss > 0.0 ) {
                scolor = pow( max(dot(nBumpNormal, normalize(nLight + nCamera)), 0.0), uGloss) * uSpecular*light_specular_array;
         }
         scolor *= attenuation;

        // Generate the final output colors to pass to the fragment shader. -----------------------------------------------------------------------------------

        vec4 litColor = vec4(clamp(color.rgb, 0.0, 1.0), uAmbient.a);
        vec4 litSecondaryColor = vec4(clamp(scolor.rgb, 0.0, 1.0), 0.0);
        colorFinal += clamp(litColor + litSecondaryColor , 0.0, 1.0);



	gl_FragColor = vec4(colorFinal.rgb, uAmbient.a);
}
