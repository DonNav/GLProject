attribute mediump vec4 aPosition;
attribute mediump vec4 aNormal;
attribute mediump vec2 aTexture;


varying mediump vec2 texCoord;


void main()
{
        gl_Position = aPosition;


        texCoord = aTexture;
}


