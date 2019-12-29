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
#include "include/shprogram.h"
#include "include/BasicCylinder.h"
#include "include/Camera.h"
#include <CompositeGroup.h>
#include <ObjectGroup.h>


// Window dimensions
GLuint WIDTH = 800, HEIGHT = 600;

// TODO Is there better solution than global object?
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

// Information of key being held
bool keyWHold = false;
bool keyAHold = false;
bool keySHold = false;
bool keyDHold = false;

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

	try
	{
		// Create a GLFWwindow object that we can use for GLFW's functions
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Niewielka Drukarka Trujwymiaru !", glfwGetPrimaryMonitor(), nullptr);
		
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
		ShaderProgram theProgram("shaders/core.vert", "shaders/core.frag");
		ShaderProgram shaderBasic("shaders/vertshader.vert", "shaders/fragshader.frag");

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		// Set camera options
		camera.setPitchConstrains(-89.0f, 89.0f);
		camera.setBoundries(glm::vec3(-10.0f, -10.0f, -10.0f), glm::vec3(10.0f, 10.0f, 10.0f));

		// Make demo cylinders
		BasicCylinder cylinder1 = BasicCylinder(glm::vec3(.0f, .7f, .1f), 1.f, .1f);
		BasicCylinder cylinder2 = BasicCylinder(glm::vec3(.7f, .1f, .5f), 1.f, .3f);
		BasicCylinder cylinder3 = BasicCylinder(glm::vec3(.1f, .5f, .7f), .3f, .05f);
		
		//make composite group demo
		CompositeGroup compGroup;
		{
			cylinder2.translate(glm::vec3(0.f, -.5f, 0.f));
			cylinder3.translate(glm::vec3(0.f, 2.2f, 0.f));

			compGroup.addObject(cylinder1);
			compGroup.addObject(cylinder2);
			compGroup.addObject(cylinder3);

			compGroup.translate(glm::vec3(1.0f, -1.0f, 1.0f));

			cylinder2.translate(glm::vec3(0.f, .5f, 0.f));
			cylinder3.translate(glm::vec3(0.f, -2.2f, 0.f));
		}

		// Scale cylinders
		cylinder1.scale(glm::vec3(.5f, 1.5f, .5f));
		cylinder3.scale(glm::vec3(2.4f, 1.f, 1.f));

		// Move cylinders apart
		cylinder2.translate(glm::vec3(-.5f, -.5f, -.5f));
		cylinder3.translate(glm::vec3(.2f, .2f, .2f));

		//make object group demo
		auto objGroup = std::make_shared<ObjectGroup>();
		{
			// NOTE : that will link the objects to their origin ! 
			// there is no copying with below use !!!

			// To make a shared object best practise would be to incherit from Group Object and make Objects in constructor
			// this also allows to make logic for moving some of the objects by keeping order of the objects in vector
			objGroup.get()->addObject(std::move(std::make_shared<BasicCylinder>(cylinder1)));
			objGroup.get()->addObject(std::move(std::make_shared<BasicCylinder>(cylinder2)));
			objGroup.get()->addObject(std::move(std::make_shared<BasicCylinder>(cylinder3)));

			//objects are pointed but ParentModel will move them apart
			objGroup.get()->translate(glm::vec3(-1.0f, 1.0f, -1.0f));
		}
		ObjectGroup objGroup2;
		objGroup2.addObject(objGroup);

		//objects are pointed but ParentModel will move them apart
		objGroup2.translate(glm::vec3(1.0f, 0.0f, 1.0f));
		objGroup2.scale(glm::vec3(0.3f, 0.3f, 0.3f));
		
		// Calculate aspect ration for projection later to be used
		GLfloat aspectRatio = static_cast<GLfloat>(screenWidth / screenHeight);

		glm::mat4 projection = glm::mat4(1.0f);

		// Frame calculation for smooth animation
		double currentFrame = glfwGetTime();
		double deltaTime = 0;
		double lastFrame = currentFrame;

		while (!glfwWindowShouldClose(window)) {
			currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Handle potential movement based on delta time and key callbacks 
			if (keyAHold || keyWHold || keySHold || keyDHold) {
				handleMovement(static_cast<GLfloat>(deltaTime));
			}

			glClearColor(.35f, .2f, 0.0f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// Set angle [keeping velocity in time]
			static GLfloat rot_angle = static_cast<GLfloat>(deltaTime) * 300.0f;

			// Set camera view matrix
			shaderBasic.setMat4Uniform("view", camera.getView());

			// Set projection matrix
			projection = glm::perspective(glm::radians(camera.getZoom()), aspectRatio, 0.1f, 100.0f);
			shaderBasic.setMat4Uniform("projection", projection);

			// Rotate cylinders
			cylinder1.rotate(glm::vec3(.3f, .6f, .8f), 3*rot_angle);
			cylinder2.rotate(glm::vec3(.3f, .1f, .8f), -rot_angle);
			cylinder3.rotate(glm::vec3(.9f, .1f, .1f), rot_angle);

			// Rotate groups
			compGroup.rotate(glm::vec3(.5f, .5f, .5f), rot_angle);
			objGroup.get()->rotate(glm::vec3(.5f, -.5f, -.5f), -2*rot_angle);

			// Draw our cylinders
			shaderBasic.Use();
			cylinder1.Draw(shaderBasic);
			cylinder2.Draw(shaderBasic);
			cylinder3.Draw(shaderBasic);

			// Draw Groups
			compGroup.Draw(shaderBasic);
			objGroup.get()->Draw(shaderBasic);
			objGroup2.Draw(shaderBasic);
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
