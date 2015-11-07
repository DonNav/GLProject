precision mediump float; 	

//Material parameters
uniform sampler2D sample_Texture;

varying vec2 texCoord;



void main(void)
{


	vec4 pixel = vec4(texture2D(sample_Texture, texCoord));


        gl_FragColor = pixel;

}
