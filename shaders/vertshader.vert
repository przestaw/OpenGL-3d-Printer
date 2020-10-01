#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 VecColor;
out vec2 TexCoord;
out vec4 PositionWorldspace;
out vec4 Normal;
//light direction and camera direction -> for light calculations

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    PositionWorldspace = (model * vec4(position, 1.0));

    VecColor = color;
    TexCoord = texCoord;

    gl_Position = projection * view * PositionWorldspace;
    // TODO This is expensive so it should be moved outside of shader
    // However I'll keep this for now
    Normal = transpose(inverse(model)) * vec4(normal, 1.0f);  
}
