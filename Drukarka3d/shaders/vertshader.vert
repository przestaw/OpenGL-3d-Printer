#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 VecColor;
out vec2 TexCoord;
out vec3 Position_Worldspace;

uniform mat4 model;

void main()
{
	Position_Worldspace = vec3(model * vec4(position, 1.0));

    VecColor = color;
    TexCoord = texCoord;

    gl_Position = vec4(Position_Worldspace, 1.0);
} 