#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 VecColor;
out vec2 TexCoord;
out vec4 PositionWorldspace;
//light direction and camera direction -> for light calculations

uniform mat4 model;
uniform mat4 parentModel;

void main()
{
	PositionWorldspace = (parentModel * model * vec4(position, 1.0));

    VecColor = color;
    TexCoord = texCoord;

    gl_Position = PositionWorldspace; //view, projection etc
} 