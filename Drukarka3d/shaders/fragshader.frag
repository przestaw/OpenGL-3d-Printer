#version 330 core
in vec2 TexCoord;
in vec3 VecColor;
in vec4 PositionWorldspace;
in vec4 Normal;

out vec3 color;

// For now it is only one light source
// TODO implement option for having multiple lights
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{   
    // Set ambient light
    float ambientStrength = 0.1;
    vec3 ambientLight = ambientStrength * lightColor;

    // Normalize normal vector and light directon's vector
    // It is done because we are interested in directions and angles and not in length
    vec3 normal = normalize(vec3(Normal));
    vec3 lightDirection = normalize(lightPos - vec3(PositionWorldspace));

    // Calculate diffuse impact
    // We are use max(x, 0) because result of dot may be negative (and then diffuse strength is just 0)
    float diffuseStrength = max(dot(normal, lightDirection), 0.0);
    vec3 diffuseLight = diffuseStrength * lightColor;

    // Calculate specular light
    float specularStrength = 0.5;

    vec3 viewDirection = normalize(viewPos - vec3(PositionWorldspace));
    vec3 reflectDirection = reflect(-lightDirection, normal);
    
    // We calculate power of specular effect based on direction of reflection and view direction
    // Shininess should be preferably a power of 2 and the greater the number the more reflects light
    int shininess = 32;
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
    
    vec3 specularLight = specularStrength * spec * lightColor;

    vec3 result = (ambientLight + diffuseLight + specularLight) * VecColor;

	//TODO : colors & textures

    color = result;
}
