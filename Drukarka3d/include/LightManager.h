#pragma 
#include "DirectionalLight.h"
#include "SpotLight.h"

#include <memory>
#include <iostream>
#include <vector>

// Light Manager's task is to manage scene lighting. It keeps all the lights, has one method for setting them all up
// at once, allows to dynamically add and/or remove them.
class LightManager
{
public:
	// Currently lights in shaders are kept as an arrays of specified size therefore LightManager has to keep track
	// of amount of lights and if it is close to the limit
	LightManager(int maxPointLightAmount, int maxSpotLightAmount);

	void setUpLight(const ShaderProgram& shaderProgram);

	// Directional light is only one therefore we do not need methods for adding multiple directional lights
	std::shared_ptr<DirectionalLight> getDirectionalLight();
	
	void addPointLight(std::shared_ptr<PointLight> light);
	std::shared_ptr<PointLight> addPointLight();
	std::shared_ptr<PointLight> getPointLight(const int index);
	void removePointLight(std::shared_ptr<PointLight> lightToRemove);


	void addSpotLight(std::shared_ptr<SpotLight> light);
	std::shared_ptr<SpotLight> addSpotLight();
	std::shared_ptr<SpotLight> getSpotLight(const int index);
	void removeSpotLight(std::shared_ptr<SpotLight> lightToRemove);

private:
	enum class LightType { DIRECTIONAL, POINT, SPOT };

	// Lights are kept here in vectors but shaders knows them by their index therefore everytime these vectors
	// are changed we need to update names of light's uniforms as they contain indexes
	void fixNames(LightType lightType);

	// These three methods are just for organizing things a little
	void setUpDirectionalLight(const ShaderProgram& shaderProgram);
	void setUpPointLights(const ShaderProgram& shaderProgram);
	void setUpSpotLights(const ShaderProgram& shaderProgram);

	std::vector<std::shared_ptr<PointLight>> pointLightsVector;
	std::vector<std::shared_ptr<SpotLight>> spotLightsVector;
	std::shared_ptr<DirectionalLight> directionalLight;

	const int maxPointLightAmount;
	const int maxSpotLightAmount;
};

