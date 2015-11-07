uniform mediump mat4 projection ;
uniform mediump mat4 model;
uniform mediump mat4 view;
attribute mediump vec4 aPosition;
attribute mediump vec4 aNormal;
attribute mediump vec2 aTexture;

varying mediump vec3 position;
varying mediump vec3 normal;
varying mediump vec2 textureCoordinate;

void main() 
{
        gl_Position = projection * view * model * aPosition;

	position = aPosition.xyz;
	normal = aNormal.xyz;
        textureCoordinate=  aTexture.xy;
}
