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

// Position of camera
uniform vec3 viewPos;

// Lights
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[20];
uniform SpotLight spotLights[5];

// Current amounts of lights
uniform int amountOfPointLights;
uniform int amountOfSpotLights;

// NOTE For whatever reason these functions have to start with capital letter
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDirection);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 position, vec3 viewDirection);

void main()
{   
    // Normalize normal vector and view direction vector
    // It is done because we are interested in directions and angles and not in length
    vec3 normal = normalize(vec3(Normal));
    vec3 viewDirection = normalize(viewPos - vec3(PositionWorldspace));

    vec3 result = CalculateDirectionalLight(directionalLight, normal, viewDirection);
    
    // NOTE turns out having i as a uint causes some trouble compiling so just stick with int

    for (int i = 0; i < amountOfPointLights; i++) {
        result += CalculatePointLight(pointLights[i], normal, vec3(PositionWorldspace), viewDirection);
    }

    for (int i = 0; i < amountOfSpotLights; i++) {
        result += CalculateSpotLight(spotLights[i], normal, vec3(PositionWorldspace), viewDirection);
    }


	//TODO : colors & textures

    color = result;
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
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

vec3 CalculatePointLight (PointLight light, vec3 normal, vec3 position, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.position - position);

    // Diffuse light
    float diff = max(dot(normal, lightDirection), 0.0);

    // Specular light
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);

    // Attenuation
    float distance = length(light.position - position);
    float attenuation = 1.0 / (light.constantParameter + light.linearParameter * distance +
                               light.quadraticParameter * (distance * distance));

    vec3 ambientLight = light.ambientStrength * VecColor;
    vec3 diffuseLight = light.diffuseStrength * diff * VecColor;
    vec3 specularLight = light.specularStrength * spec * VecColor;

    ambientLight *= attenuation;
    diffuseLight *= attenuation;
    specularLight *= attenuation;

    return (ambientLight + diffuseLight + specularLight);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 position, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.position - position);

    // Diffuse light
    float diff = max(dot(normal, lightDirection), 0.0);

    // Specular light
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);

    // Attenuation
    float distance = length(light.position - position);
    float attenuation = 1.0 / (light.constantParameter + light.linearParameter * distance +
                               light.quadraticParameter * (distance * distance));

    // Spot light intensity
    // Spot light is defined as two cones, inner and outer. The end of inner cone is where light begins to darken
    // and end of outer cone is where light is no more. Between them our light should smoothly change it's intensity

    // theta is the angle between light direction (direction from fragment to light) and spot direction (direction
    // where light is aiming)
    float theta = dot(lightDirection, normalize(-light.direction));

    // epsilon is the difference between inner and outer cone
    float epsilon = light.cutOff - light.outerCutOff;

    // We calculate intensity which can be 0 (when fragment is outside of outer cone), 1 (wher fragment is inside
    // inner cone) and (0.0 ; 1.0) (when fragment is between inside and outer cone)
    float intensity  = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambientLight = light.ambientStrength * VecColor;
    vec3 diffuseLight = light.diffuseStrength * diff * VecColor;
    vec3 specularLight = light.specularStrength * spec * VecColor;

    ambientLight *= attenuation * intensity;
    diffuseLight *= attenuation * intensity;
    specularLight *= attenuation * intensity;
    
    return (ambientLight + diffuseLight + specularLight);
}
