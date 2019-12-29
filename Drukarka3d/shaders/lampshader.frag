#version 330 core
in vec2 TexCoord;
in vec3 VecColor;
in vec4 PositionWorldspace;

out vec3 color;

uniform vec3 lightColor;

void main()
{   
    color = lightColor;
}
