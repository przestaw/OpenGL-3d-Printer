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

#include "BasicSphere.h"
#include "BasicCuboid.h"

// Window dimensions
GLuint WIDTH = 800, HEIGHT = 600;

//using directives
using std::cout;
using std::cerr;
using std::endl;
using std::exception;

//callback for key interpretation 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

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

		// Make demo cylinders
		BasicCylinder cylinder1 = BasicCylinder(glm::vec3(.0f, .7f, .1f), 1.f, .1f);
		BasicCylinder cylinder2 = BasicCylinder(glm::vec3(.7f, .1f, .5f), 1.f, .3f);
		BasicCylinder cylinder3 = BasicCylinder(glm::vec3(.1f, .5f, .7f), .3f, .05f);
		
		// Make demo sphere
		BasicSphere sphere1 = BasicSphere(glm::vec3(0.5f, 0.5f, 0.6f), 0.5f, 64, 64);

		// Scale cylinders
		cylinder1.scale(glm::vec3(.5f, 1.5f, .5f));
		cylinder3.scale(glm::vec3(2.4f, 1.f, 1.f));

		// Move cylinders apart
		cylinder2.translate(glm::vec3(-.5f, -.5f, -.5f));
		cylinder3.translate(glm::vec3(.2f, .2f, .2f));

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

			glClearColor(.35f, .2f, 0.0f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// Set angle [keeping velocity in time]
			static GLfloat rot_angle = static_cast<GLfloat>(deltaTime) * 300.f;

			// Rotate cylinders
			cylinder1.rotate(glm::vec3(.3f, .6f, .8f), 3*rot_angle);
			cylinder2.rotate(glm::vec3(.3f, .1f, .8f), -rot_angle);
			cylinder3.rotate(glm::vec3(.9f, .1f, .1f), rot_angle);
			
			// Rotate sphere 
			sphere1.rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(1.0f));

			// Draw our cylinders
			shaderBasic.Use();
			cylinder1.Draw(shaderBasic);
			cylinder2.Draw(shaderBasic);
			cylinder3.Draw(shaderBasic);

			// Draw sphere
			sphere1.Draw(shaderBasic);

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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}