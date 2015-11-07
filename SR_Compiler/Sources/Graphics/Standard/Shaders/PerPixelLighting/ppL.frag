precision mediump float;

// Material informations
uniform vec4 uAmbient;
uniform vec4 uDiffuse;
uniform vec4 uSpecular;
uniform vec4 uEmissive;

uniform float uGloss;

// Camera informations:
uniform vec3 uCameraPosition;


// Varying values
varying vec3 position;
varying  vec3 normal;


void main(void)
{
	vec4 light_position_array = vec4(0.0,10.0,5.0,1.0);
	vec4 light_ambient_array= vec4(1.0,1.0,1.0,1.0);
	vec4 light_diffuse_array= vec4(1.0,1.0,1.0,1.0);
	vec4 light_specular_array= vec4(1.0,1.0,1.0,1.0);

    vec4 colorFinal = vec4(0.0,0.0,0.0,1.0);

    vec3 nNormal = normalize(normal.xyz);
    vec3 nCamera = normalize(uCameraPosition.xyz - position.xyz);

    //We compute the light position compare to object position;
    vec3 nLight = normalize(light_position_array.xyz - position.xyz);

    // we define two color for color computation
    vec4 color = vec4(uEmissive);
    vec4 scolor = vec4(0.0,0.0,0.0,1.0);

    // we compute the angle between the normal and the light position
    // we be used to compute specular exponent
    float angle = max(dot(nNormal, nLight), 0.0);

    color += uAmbient*light_ambient_array  + angle *  uDiffuse * light_diffuse_array  ;

    // Calculate the specular light components. ---------------------------------------------------------------------------------------------------------
     if (angle != 0.0 && uGloss > 0.0 ) {
            scolor = pow( max(dot(nNormal, normalize(nLight + nCamera)), 0.0), uGloss) * uSpecular*light_specular_array;
    }

    // Generate the final output colors to pass to the fragment shader. -----------------------------------------------------------------------------------

     vec4 litColor = vec4(clamp(color.rgb, 0.0, 1.0), uAmbient.a);
    vec4 litSecondaryColor = vec4(clamp(scolor.rgb, 0.0, 1.0), 0.0);
    colorFinal += clamp(litColor + litSecondaryColor , 0.0, 1.0);

    gl_FragColor = vec4(colorFinal.rgb, uAmbient.a);
}
