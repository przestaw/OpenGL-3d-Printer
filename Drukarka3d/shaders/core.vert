#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 ourColor;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0f);
    ourColor = vec4(color, 1.0f);
}
