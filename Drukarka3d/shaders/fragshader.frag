#version 330 core
in vec2 TexCoord;
in vec3 VecColor;
in vec4 PositionWorldspace;
in vec4 Normal;

out vec3 color;

struct DirectionalLight {
    vec3 direction;
	
    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;
};

struct PointLight {
    vec3 position;

    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;

    float constantParameter;
    float linearParameter;
    float quadraticParameter;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;

    float constantParameter;
    float linearParameter;
    float quadraticParameter;
};

#define AMOUNT_OF_POINT_LIGHTS 20
#define AMOUNT_OF_SPOT_LIGHTS 5

uniform vec3 viewPos;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[20];
uniform SpotLight spotLights[5];

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDirection);
vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 position, vec3 viewDirection);

void main()
{   
    // Normalize normal vector and view direction vector
    // It is done because we are interested in directions and angles and not in length
    vec3 normal = normalize(vec3(Normal));
    vec3 viewDirection = normalize(viewPos - vec3(PositionWorldspace));

    vec3 result = calculateDirectionalLight(directionalLight, normal, viewDirection);

    //vec3 result = ( (ambientLight + diffuseLight + specularLight) * attenuation ) * VecColor;

	//TODO : colors & textures

    color = result;
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
    vec3 lightDirection = normalize(-light.direction);

    // Diffuse light
    float diff = max(dot(normal, lightDirection), 0.0);
    
    // Specular light
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);

    vec3 ambientLight = light.ambientStrength * VecColor;
    vec3 diffuseLight = light.diffuseStrength * diff * VecColor;
    vec3 specularLight = light.specularStrength * spec * VecColor;

    return (ambientLight + diffuseLight + specularLight);
}