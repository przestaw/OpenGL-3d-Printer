/** == == PROJECT : 3d rep-rap model == ==
 *  == main entry point for application ==
 *	created by przestaw on 13.12.2019
 */

#include <iostream>

// GLEW
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
#include <Camera.h>
#include <CompositeGroup.h>
#include <ObjectGroup.h>
#include <shprogram.h>
#include <Printer.h>
#include "LightManager.h"
#include "Skybox.h"
#include <Forest.h>
#include <Lamp.h>
#include <Terrain.h>

// Window dimensions
GLuint WIDTH = 800, HEIGHT = 600;

// TODO Is there better solution than global object?
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

// Information of key being held
bool keyWHold = false;
bool keyAHold = false;
bool keySHold = false;
bool keyDHold = false;

bool moveExtruderUp    = false;
bool moveExtruderDown  = false;
bool moveExtruderLeft  = false;
bool moveExtruderRight = false;
bool moveExtruderAhead = false;
bool moveExtruderBack  = false;

bool flashlightOn = true;

bool spawnBallPressed     = false;
bool spawnCubePressed     = false;
bool spawnConePressed     = false;
bool spawnCylinderPressed = false;
bool spawnIceCreamPressed = false;
bool deleteSpawned        = false;

// Using directives
using std::cerr;
using std::cout;
using std::endl;
using std::exception;

// Callback for key interpretation
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode);

// Handling movement in four directions based on delta time and key callbacks
void handleMovement(GLfloat deltaTime);

// Handling extruder movement
void handleExtruderMovement(Printer& printer, const GLfloat deltaTime);

// Handling "3d printing"
void handleSpawningObjects(Printer& printer);

void mouseCallback(GLFWwindow* window, double xPos, double yPos);

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

double lastMouseX{0};
double lastMouseY{0};
bool mouseVariablesInitialized{false};

int main() {

  // Init GLFW and make sure it suceed
  if (glfwInit() != GL_TRUE) {
    cerr << "GLFW initialization failed" << endl;
    return -1;
  }

  // Probe Dimensions
  WIDTH  = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
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
  // Worth noting is that setCutOff and setOuterCutOff are already doing
  // glm::cos(glm::radians()) therefore we don't need to
  flashlight->setCutOff(12.5f);
  flashlight->setOuterCutOff(15.0f);

  // Lamps
  auto lamp1 = lightManager.addPointLight();
  lamp1->setAmbientStrength(glm::vec3(0.1f));
  lamp1->setDiffuseStrength(glm::vec3(0.8f));
  lamp1->setSpecularStrength(glm::vec3(1.0f));
  lamp1->setLightRange(PointLight::LightRange::RANGE_50);
  lamp1->setPosition(glm::vec3(3.0f, 1.0f, 5.0f));

  auto lamp2 = lightManager.addPointLight();
  lamp2->setAmbientStrength(glm::vec3(0.2f));
  lamp2->setDiffuseStrength(glm::vec3(0.8f));
  lamp2->setSpecularStrength(glm::vec3(1.0f));
  lamp2->setLightRange(PointLight::LightRange::RANGE_32);
  lamp2->setPosition(glm::vec3(5.0f, 1.0f, -5.0f));

  auto lamp3 = lightManager.addPointLight();
  lamp3->setAmbientStrength(glm::vec3(0.1f));
  lamp3->setDiffuseStrength(glm::vec3(1.0f));
  lamp3->setSpecularStrength(glm::vec3(0.2f));
  lamp3->setLightRange(PointLight::LightRange::RANGE_32);
  lamp3->setPosition(glm::vec3(-2.2f, 1.0f, -2.0f));

  try {
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window =
        glfwCreateWindow(WIDTH, HEIGHT, "Niewielka Drukarka Trojwymiaru !",
                         nullptr /* glfwGetPrimaryMonitor()*/, nullptr);

    // Check if window is created
    if (window == nullptr) {
      throw std::runtime_error("GLFW window not created");
    }

    // Get exact screen width and height
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // Capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set this to true so GLEW knows to use a modern approach to retrieving
    // function pointers and extensions
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
      throw std::runtime_error("GLEW Initialization failed");
    }

    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Build, compile and link shader program
    ShaderProgram shaderBasic("shaders/vertshader.vert",
                              "shaders/fragshader.frag");
    ShaderProgram shaderLamp("shaders/lampshader.vert",
                             "shaders/lampshader.frag");
    ShaderProgram shaderSkybox("shaders/skyboxshader.vert",
                               "shaders/skyboxshader.frag");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Set light maps, 0 and 1 are just IDs
    shaderBasic.Use();
    shaderBasic.setIntUniform("material.diffuseMap", 0);
    shaderBasic.setIntUniform("material.specularMap", 1);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    // Set camera options
    camera.setPitchConstrains(-89.0f, 89.0f);
    camera.setBoundries(glm::vec3(-10.0f, -10.0f, -10.0f),
                        glm::vec3(10.0f, 10.0f, 10.0f));

    std::vector<std::string> skyboxFaces = {
        "res/skybox/ely_lakes/lakes_ft.jpg",
        "res/skybox/ely_lakes/lakes_bk.jpg",
        "res/skybox/ely_lakes/lakes_up.jpg",
        "res/skybox/ely_lakes/lakes_dn.jpg",
        "res/skybox/ely_lakes/lakes_rt.jpg",
        "res/skybox/ely_lakes/lakes_lf.jpg",
    };
    /* Initialize skybox */
    Skybox skybox(skyboxFaces);
    // Set uniform in skybox shader
    shaderSkybox.Use();
    shaderSkybox.setIntUniform("skybox", 0);

    // Calculate aspect ration for projection later to be used
    // NOTE I do not know but sometimes line below cause program to crash. I
    // cannot find proper solution nor reason for this to cause any damage. If
    // white screen appears in front of you I'd suggest setting aspect ratio
    // hard coded as I have no clue what is going on.
    GLfloat aspectRatio =
        static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight);
    std::cout << "width: " << screenWidth << std::endl;
    std::cout << "height: " << screenHeight << std::endl;
    std::cout << "aspect ratio: " << aspectRatio << std::endl;

    glm::mat4 projection = glm::mat4(1.0f);

    // Printer
    Printer printer(0.7);
    ObjectGroup exterior;

    Material wood(10, Texture("res/table.jpg"), 0.8, Texture("res/black.jpg"),
                  1.0);

    // Lights
    std::vector<Lamp> lamps;
    lamps.push_back(Lamp(lamp1->getPosition(), wood));
    lamps.push_back(Lamp(lamp2->getPosition(), wood));
    lamps.push_back(Lamp(lamp3->getPosition(), wood));

    // Globe XD
    BasicCuboid table(glm::vec3(0.3, 0.18, 0.1), 1.0, 0.2, 1.0);
    table.translate(glm::vec3(0.0, -0.15, 0.0));
    table.setMaterial(wood);
    exterior.addObject(table);

    // Terrain
    Terrain terrain(18.0f, 18.0f, 90, 0.14f, false);
    terrain.translate(glm::vec3(0.0f, -0.23f, 0.0f));
    Material grassy(12, Texture("res/grass.jpg"), 0.8f,
                    Texture("res/black.jpg"), 0.8f);
    terrain.setMaterial(grassy);

    // Pretty random forrest
    Material leaves  = Material(16.0, Texture("res/leaves.jpg"), 0.8,
                               Texture("res/leaves_ref.jpg"), 1.0);
    Material neadles = Material(64.0, Texture("res/neadles.jpg"), 0.8,
                                Texture("res/neadles_ref.jpg"), 1.0);
    Material bark    = Material(4.0, Texture("res/bark.jpg"), 0.8,
                             Texture("res/bark_ref2.jpg"), 0.45);
    Forrest forrest(0.6, 8.5, 0.35, 70, 70, bark, leaves, neadles, 18);

    forrest.translate(glm::vec3(0.0, -0.1, 0.0));

    // Frame calculation for smooth animation
    double currentFrame = glfwGetTime();
    double deltaTime    = 0;
    double lastFrame    = currentFrame;

    bool flashlightLastFrame = true;
    double counter           = 0;

    while (!glfwWindowShouldClose(window)) {
      currentFrame = glfwGetTime();
      deltaTime    = currentFrame - lastFrame;
      lastFrame    = currentFrame;

      flashlightLastFrame = flashlightOn;

      // Check if any events have been activiated (key pressed, mouse moved
      // etc.) and call corresponding response functions
      glfwPollEvents();

      // Turn flashlight on/off when F is clicked
      if (flashlightLastFrame != flashlightOn) {
        if (flashlightOn) {
          flashlight->setDiffuseStrength(glm::vec3(1.0f));
          flashlight->setSpecularStrength(glm::vec3(1.0f));
        } else {
          flashlight->setDiffuseStrength(glm::vec3(0.0f));
          flashlight->setSpecularStrength(glm::vec3(0.0f));
        }
      }

      // Handle potential movement based on delta time and key callbacks
      if (keyAHold || keyWHold || keySHold || keyDHold) {
        handleMovement(static_cast<GLfloat>(deltaTime / 2.0));
      }

      handleExtruderMovement(printer, static_cast<GLfloat>(deltaTime / 2.0));
      handleSpawningObjects(printer);

      glClearColor(.08f, .08f, 0.08f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Start working with basic shader
      shaderBasic.Use();

      // Set projection matrix
      projection = glm::perspective(glm::radians(camera.getZoom()), aspectRatio,
                                    0.1f, 100.0f);
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

      // Terrain
      terrain.Draw(shaderBasic);

      // Printer and table
      printer.Draw(shaderBasic);
      exterior.Draw(shaderBasic);
      forrest.Draw(shaderBasic);

      // Start working with lamp's shader
      shaderLamp.Use();

      // Set camera matrices for lamp shaders
      shaderLamp.setMat4Uniform("projection", projection);
      shaderLamp.setMat4Uniform("view", camera.getView());
      shaderLamp.setVec3Uniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

      for (auto lamp : lamps) { lamp.Draw(shaderBasic, shaderLamp); }

      // Draw skybox, as last object so
      skybox.Draw(shaderSkybox, glm::mat3(camera.getView()), projection);

      // Swap the screen buffers
      glfwSwapBuffers(window);
    }
  } catch (std::runtime_error& ex) {
    // Information about the failure
    cerr << ex.what() << endl;
  } catch (exception& ex) {
    // Information about the failure
    cerr << ex.what() << endl;
  }

  glfwTerminate();

  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
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
    if (key == GLFW_KEY_UP) {
      moveExtruderUp = true;
    }
    if (key == GLFW_KEY_DOWN) {
      moveExtruderDown = true;
    }
    if (key == GLFW_KEY_LEFT) {
      moveExtruderLeft = true;
    }
    if (key == GLFW_KEY_RIGHT) {
      moveExtruderRight = true;
    }
    if (key == GLFW_KEY_O) {
      moveExtruderAhead = true;
    }
    if (key == GLFW_KEY_L) {
      moveExtruderBack = true;
    }
    if (key == GLFW_KEY_0) {
      deleteSpawned = true;
    }
    if (key == GLFW_KEY_1) {
      spawnBallPressed = true;
    }
    if (key == GLFW_KEY_2) {
      spawnConePressed = true;
    }
    if (key == GLFW_KEY_3) {
      spawnCubePressed = true;
    }
    if (key == GLFW_KEY_4) {
      spawnCylinderPressed = true;
    }
    if (key == GLFW_KEY_5) {
      spawnIceCreamPressed = true;
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

void handleExtruderMovement(Printer& printer, const GLfloat deltaTime) {
  printer.setMoveDelta(deltaTime);
  if (moveExtruderAhead) {
    printer.moveExtruderX(true);
    moveExtruderAhead = false;
  }
  if (moveExtruderBack) {
    printer.moveExtruderX(false);
    moveExtruderBack = false;
  }
  if (moveExtruderUp) {
    printer.moveExtruderZ(true);
    moveExtruderUp = false;
  }
  if (moveExtruderDown) {
    printer.moveExtruderZ(false);
    moveExtruderDown = false;
  }
  if (moveExtruderRight) {
    printer.moveExtruderY(true);
    moveExtruderRight = false;
  }
  if (moveExtruderLeft) {
    printer.moveExtruderY(false);
    moveExtruderLeft = false;
  }
}

void handleSpawningObjects(Printer& printer) {
  if (deleteSpawned) {
    printer.deleteSpawned();
    deleteSpawned = false;
  }
  if (spawnBallPressed) {
    printer.spawnBall();
    spawnBallPressed = false;
  }
  if (spawnCubePressed) {
    printer.spawnCube();
    spawnCubePressed = false;
  }
  if (spawnConePressed) {
    printer.spawnCone();
    spawnConePressed = false;
  }
  if (spawnCylinderPressed) {
    printer.spawnCylinder();
    spawnCylinderPressed = false;
  }
  if (spawnIceCreamPressed) {
    printer.spawnIceCream();
    spawnIceCreamPressed = false;
  }
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
  if (!mouseVariablesInitialized) {
    lastMouseX                = xPos;
    lastMouseY                = yPos;
    mouseVariablesInitialized = true;
  }

  auto xOffset = static_cast<GLfloat>(xPos - lastMouseX);
  // Calculation is reversed in yOffset to achieve looking up while moving mouse
  // forward
  // TODO Option for choosing between reversed and normal movement?
  auto yOffset = static_cast<GLfloat>(lastMouseY - yPos);
  lastMouseX   = xPos;
  lastMouseY   = yPos;

  camera.handleMouseMovement(xOffset, yOffset);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
  camera.handleMouseScroll(static_cast<GLfloat>(yOffset));
}