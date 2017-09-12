#version 150 core

uniform sampler2D fireTexture;
uniform vec3 maincolor;
out vec4 fragColor;
in vec2 texCoord;

void main()
{
    //output color from material
    //fragColor = vec4(maincolor,1.0);
    fragColor = texture( fireTexture, texCoord );
}

