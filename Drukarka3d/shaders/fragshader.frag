#version 330 core
in vec2 TexCoord;
in vec3 VecColor;

out vec3 color;

void main()
{   
    vec3 result = VecColor;

    color = result;
}
