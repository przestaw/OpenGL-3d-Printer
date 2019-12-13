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

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

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

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	try
	{
		// Create a GLFWwindow object that we can use for GLFW's functions
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Przepotenzna drukarka trujwymiaru !", nullptr, nullptr);
		
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

		// Set up vertex data [8 vertices 3 coord and 3 color coord per vert]
		//GLfloat vertices[ 8 * 6 ] = { 0 };
		/*int iter = 0;
		for (GLfloat z = .5f; z >= -1.; z = z - 1.f) {
			for (GLfloat y = .5f; y >= -1.; y = y - 1.f) {
				for (GLfloat x = .5f; x >= -1.; x = x - 1.f) {
					vertices[iter++] = x; vertices[iter++] = y; vertices[iter++] = z;
					vertices[iter++] = 0.2;
					vertices[iter++] = 0.7;
					vertices[iter++] = 0.9;

				}
			}
		}*/ 
			
		GLfloat vertices[] = {
			// front
			-0.5, -0.5,  0.5,   1.0, 0.0, 0.0,
			 0.5, -0.5,  0.5,   0.0, 1.0, 0.0,
			 0.5,  0.5,  0.5,   0.0, 0.0, 1.0,
			-0.5,  0.5,  0.5,   1.0, 1.0, 1.0,
			// back
			-0.5, -0.5, -0.5,   1.0, 0.0, 0.0,
			 0.5, -0.5, -0.5,   0.0, 1.0, 0.0,
			 0.5,  0.5, -0.5,   0.0, 0.0, 1.0,
			-0.5,  0.5, -0.5,   1.0, 1.0, 1.0
		};
		

		// Set up triangles [6 walls 2 triangles each]
		unsigned int indices[] = { // front
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
		};
		

		GLuint VBO, EBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
		glBindVertexArray(0); 

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		while (!glfwWindowShouldClose(window)) {
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 trans;
			static GLfloat rot_angle = 0.0f;
			trans = glm::rotate(trans, -glm::radians(rot_angle), glm::vec3(0.2, 0.5, 0.8));
			rot_angle += 0.05f;
			if (rot_angle >= 360.0f)
				rot_angle -= 360.0f;
			GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

			// Draw our first triangle
			theProgram.Use();

			glBindVertexArray(VAO);
			// TODO : repair cube
			glDrawElements(GL_TRIANGLES, _countof(indices), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
	
		// Properly de-allocate all resources once they've outlived their purpose
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

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