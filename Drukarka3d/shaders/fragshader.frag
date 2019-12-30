#version 330 core
in vec2 TexCoord;
in vec3 VecColor;
in vec4 PositionWorldspace;

out vec3 color;

uniform sampler2D ShTexture;
uniform float textureImpact;

void main()
{   
    vec4 result = mix(vec4(VecColor, 1.0), texture(ShTexture,TexCoord), textureImpact);

	//TODO : colors & textures

    color = vec3(result);
}
