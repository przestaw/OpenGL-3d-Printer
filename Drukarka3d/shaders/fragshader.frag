#version 330 core
in vec2 TexCoord;
in vec3 VecColor;
in vec4 PositionWorldspace;

out vec3 color;

void main()
{   
    vec3 result = VecColor;

	//TODO : colors & textures

    color = result;
}
