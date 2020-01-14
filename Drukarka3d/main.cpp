/** == == PROJECT : 3d rep-rap model == ==
 *  == main entry point for application ==
 *	created by przestaw on 13.12.2019
 */

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <glew.h>

// GLFW
#include <glfw3.h>

// SOIL
#include <SOIL.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Project includes
#include <shprogram.h>
#include <BasicCylinder.h>
#include <Camera.h>
#include <CompositeGroup.h>
#include <ObjectGroup.h>

#include <Printer.h>

#include "include/BasicSphere.h"

#include "include/BasicCylinder.h"
#include "include/Camera.h"
#include "LightManager.h"
#include "Skybox.h"
#include <IceCream.h>



// Window dimensions
GLuint WIDTH = 800, HEIGHT = 600;

// TODO Is there better solution than global object?
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

// Information of key being held
bool keyWHold = false;
bool keyAHold = false;
bool keySHold = false;
bool keyDHold = false;

bool flashlightOn = true;

// Using directives
using std::cout;
using std::cerr;
using std::endl;
using std::exception;

// Callback for key interpretation 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Handling movement in four directions based on delta time and key callbacks
void handleMovement(GLfloat deltaTime);

void mouseCallback(GLFWwindow* window, double xPos, double yPos);

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

double lastMouseX{ 0 };
double lastMouseY{ 0 };
bool mouseVariablesInitialized{ false };

int main() {

	//Init GLFW and make sure it suceed
	if (glfwInit() != GL_TRUE)
	{
		cerr << "GLFW initialization failed" << endl;
		return -1;
	}

	// Probe Dimensions
	WIDTH = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
	HEIGHT = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Set up lights
	LightManager lightManager(20, 5);

	// Set sun-like directional light
	auto directionalLight = lightManager.getDirectionalLight();
	directionalLight->setAmbientStrength(glm::vec3(0.1f));
	directionalLight->setDiffuseStrength(glm::vec3(0.5f));
	directionalLight->setSpecularStrength(glm::vec3(1.0f));
	directionalLight->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));

	// Create flashlight
	auto flashlight = lightManager.addSpotLight();
	flashlight->setAmbientStrength(glm::vec3(0.0f));
	flashlight->setDiffuseStrength(glm::vec3(1.0f));
	flashlight->setSpecularStrength(glm::vec3(1.0f));
	flashlight->setLightRange(PointLight::LightRange::RANGE_50);
	// Worth noting is that setCutOff and setOuterCutOff are already doing glm::cos(glm::radians())
	// therefore we don't need to
	flashlight->setCutOff(12.5f);
	flashlight->setOuterCutOff(15.0f);

	// Create two example lamps
	auto lamp1 = lightManager.addPointLight();
	lamp1->setAmbientStrength(glm::vec3(0.2f));
	lamp1->setDiffuseStrength(glm::vec3(0.8f));
	lamp1->setSpecularStrength(glm::vec3(1.0f));
	lamp1->setLightRange(PointLight::LightRange::RANGE_100);
	lamp1->setPosition(glm::vec3(3.0f, 3.0f, 5.0f));

	auto lamp2 = lightManager.addPointLight();
	lamp2->setAmbientStrength(glm::vec3(0.2f));
	lamp2->setDiffuseStrength(glm::vec3(0.8f));
	lamp2->setSpecularStrength(glm::vec3(1.0f));
	lamp2->setLightRange(PointLight::LightRange::RANGE_32);
	lamp2->setPosition(glm::vec3(-5.0f, 0.0f, -2.0f));

	try
	{
		// Create a GLFWwindow object that we can use for GLFW's functions
		//GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Niewielka Drukarka Trujwymiaru !", glfwGetPrimaryMonitor(), nullptr);
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Niewielka Drukarka Trujwymiaru !", nullptr, nullptr);

		// Check if window is created
		if (window == nullptr)
			throw exception("GLFW window not created");

		// Get exact screen width and height
		int screenWidth, screenHeight;
		glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, mouseCallback);
		glfwSetScrollCallback(window, scrollCallback);

		// Capture mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		// Define the viewport dimensions
		glViewport(0, 0, screenWidth, screenHeight);

		// Build, compile and link shader program
		ShaderProgram shaderBasic("shaders/vertshader.vert", "shaders/fragshader.frag");
		ShaderProgram shaderLamp("shaders/lampshader.vert", "shaders/lampshader.frag");
		ShaderProgram shaderSkybox("shaders/skyboxshader.vert", "shaders/skyboxshader.frag");

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		// Set camera options
		camera.setPitchConstrains(-89.0f, 89.0f);
		camera.setBoundries(glm::vec3(-10.0f, -10.0f, -10.0f), glm::vec3(10.0f, 10.0f, 10.0f));

		/* Initialize skybox */
		Skybox skybox;
		
		std::vector<std::string> skyboxFaces =
		{
			"res/skybox/ely_lakes/lakes_ft.jpg",
			"res/skybox/ely_lakes/lakes_bk.jpg",
			"res/skybox/ely_lakes/lakes_up.jpg",
			"res/skybox/ely_lakes/lakes_dn.jpg",
			"res/skybox/ely_lakes/lakes_rt.jpg",
			"res/skybox/ely_lakes/lakes_lf.jpg",
		};
		skybox.setCubemapFaces(skyboxFaces);
		// Set uniform in skybox shader
		shaderSkybox.Use();
		shaderSkybox.setIntUniform("skybox", 0);

		// Calculate aspect ration for projection later to be used
		// NOTE I do not know but sometimes line below cause program to crash. I cannot find proper solution nor
		// reason for this to cause any damage. If white screen appears in front of you I'd suggest setting
		// aspect ratio hard coded as I have no clue what is going on.
		GLfloat aspectRatio = static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight);
		std::cout << "width: " << screenWidth << std::endl;
		std::cout << "height: " << screenHeight << std::endl;
		std::cout << "aspect ratio: " << aspectRatio << std::endl;

		glm::mat4 projection = glm::mat4(1.0f);

		// Lights
		BasicCylinder lampCylinder1 = BasicCylinder(glm::vec3(1.0f, 1.0f, 1.0f), .5f, .1f);
		BasicCylinder lampCylinder2 = BasicCylinder(glm::vec3(1.0f, 1.0f, 1.0f), .5f, .1f);
		lampCylinder1.translate(lamp1->getPosition());
		lampCylinder2.translate(lamp2->getPosition());

		// Printer
		Printer printer(3.0);

		ObjectGroup exterior;
		// Globe XD
		BasicCuboid table(glm::vec3(0.3, 0.18, 0.1), 5.0, 1.0, 5.0);
		table.translate(glm::vec3(0.0, -0.7, 0.0));
		table.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCone::M_PI);
		table.setTexture(Texture("res/table.jpg"), 0.8);
		
		exterior.addObject(table);

		BasicCuboid grass(glm::vec3(0.1, 0.4, 0.2), 25.0, 0.2, 25.0);
		grass.translate(glm::vec3(0.0, -0.7, 0.0));
		grass.rotate(glm::vec3(1.0, 0.0, 0.0), BasicCone::M_PI);
		table.setTexture(Texture("res/grass.jpg"), 0.9);

		exterior.addObject(grass);

		IceCream ice1(1.0, glm::vec3(0.9, 0.18, 0.1));
		IceCream ice2(1.0, glm::vec3(0.3, 0.18, 0.9));
		IceCream ice3(1.0, glm::vec3(0.2, 0.8, 0.1));
		IceCream ice4(1.0, glm::vec3(0.9, 0.0, 0.9));

		ice1.translate(glm::f32vec1(5.0) * glm::vec3(0.9, -0.018, 1.0));
		ice2.translate(glm::f32vec1(5.0) * glm::vec3(0.3, 0.018, 0.9));
		ice3.translate(glm::f32vec1(5.0) * glm::vec3(-0.9, -0.018, 1.0));
		ice4.translate(glm::f32vec1(5.0) * glm::vec3(0.9, 0.018, -1.0));

		exterior.copyObjects(ice1);
		exterior.copyObjects(ice2);
		exterior.copyObjects(ice3);
		exterior.copyObjects(ice4);
		
		// Frame calculation for smooth animation
		double currentFrame = glfwGetTime();
		double deltaTime = 0;
		double lastFrame = currentFrame;

		bool flashlightLastFrame = true;
		double counter = 0;

		printer.spawnIceCream();

		while (!glfwWindowShouldClose(window)) {
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			flashlightLastFrame = flashlightOn;

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Turn flashlight on/off when F is clicked
			if (flashlightLastFrame != flashlightOn) {
				if (flashlightOn) {
					flashlight->setDiffuseStrength(glm::vec3(1.0f));
					flashlight->setSpecularStrength(glm::vec3(1.0f));
				}
				else {
					flashlight->setDiffuseStrength(glm::vec3(0.0f));
					flashlight->setSpecularStrength(glm::vec3(0.0f));
				}
			}

			// Handle potential movement based on delta time and key callbacks 
			if (keyAHold || keyWHold || keySHold || keyDHold) {
				handleMovement(static_cast<GLfloat>(deltaTime/2.0));
			}

			glClearColor(.08f, .08f, 0.08f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// Start working with basic shader
			shaderBasic.Use();

			// Set projection matrix
			projection = glm::perspective(glm::radians(camera.getZoom()), aspectRatio, 0.1f, 100.0f);
			shaderBasic.setMat4Uniform("projection", projection);
			// Set camera view matrix
			shaderBasic.setMat4Uniform("view", camera.getView());

			// Set view position
			shaderBasic.setVec3Uniform("viewPos", camera.getPosition());

			// Set flashlight parameters
			flashlight->setPosition(camera.getPosition());
			flashlight->setDirection(camera.getFrontVector());

			// Set up light on scene
			lightManager.setUpLight(shaderBasic);

			// Printer and table
			printer.Draw(shaderBasic);
			exterior.Draw(shaderBasic);
			// TODO : logick for moving extruder and shiting on objects

			// Start working with lamp's shader
			shaderLamp.Use();

			// Set camera matrices for lamp shaders
			shaderLamp.setMat4Uniform("projection", projection);
			shaderLamp.setMat4Uniform("view", camera.getView());
			shaderLamp.setVec3Uniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

			// Draw lamp
			lampCylinder1.Draw(shaderLamp);
			lampCylinder2.Draw(shaderLamp);

			// Start working with skybox shader (skybox should be drawn as the last object!)
			shaderSkybox.Use();

			// We want to remove translation from the view matrix so that camera movement
			// doesn't affect the skybox's position vectors.
			shaderSkybox.setMat4Uniform("view", glm::mat4(glm::mat3(camera.getView())));
			shaderSkybox.setMat4Uniform("projection", projection);

			// Draw skybox
			skybox.Draw();

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
	} catch (exception ex) {
		// Information about the failure
		cerr << ex.what() << endl;
	}

	glfwTerminate();
	
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	cerr << key << endl;
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_W) {
			keyWHold = true;
		}
		if (key == GLFW_KEY_A) {
			keyAHold = true;
		}
		if (key == GLFW_KEY_S) {
			keySHold = true;
		}
		if (key == GLFW_KEY_D) {
			keyDHold = true;
		}
		if (key == GLFW_KEY_F) {
			flashlightOn = !flashlightOn;
		}
	}

	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W) {
			keyWHold = false;
		}
		if (key == GLFW_KEY_A) {
			keyAHold = false;
		}
		if (key == GLFW_KEY_S) {
			keySHold = false;
		}
		if (key == GLFW_KEY_D) {
			keyDHold = false;
		}
	}

}

void handleMovement(GLfloat deltaTime) {
	if (keyWHold) {
		camera.handleKeyboard(Camera::FORWARD, deltaTime);
	}
	if (keyAHold) {
		camera.handleKeyboard(Camera::LEFT, deltaTime);
	}
	if (keySHold) {
		camera.handleKeyboard(Camera::BACKWARD, deltaTime);
	}
	if (keyDHold) {
		camera.handleKeyboard(Camera::RIGHT, deltaTime);
	}
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (!mouseVariablesInitialized) {
		lastMouseX = xPos;
		lastMouseY = yPos;
		mouseVariablesInitialized = true;
	}

	auto xOffset = static_cast<GLfloat>(xPos - lastMouseX);
	// Calculation is reversed in yOffset to achieve looking up while moving mouse forward
	// TODO Option for choosing between reversed and normal movement?
	auto yOffset = static_cast<GLfloat>(lastMouseY - yPos);
	lastMouseX = xPos;
	lastMouseY = yPos;

	camera.handleMouseMovement(xOffset, yOffset);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.handleMouseScroll(static_cast<GLfloat>(yOffset));
}