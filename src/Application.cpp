#include "Application.h"
#include <iostream>
#include <fstream>


/**
 * @brief Constructs an Application instance with the given GLFW window.
 *
 * Initializes the application, sets up the camera using the provided window,
 * and retrieves the window's dimensions. If the window pointer is null,
 * an error message is printed and initialization is aborted.
 *
 * @param window Pointer to the GLFWwindow to be used by the application.
 */
Application::Application(GLFWwindow* window)
    : window(window),
      camera(window)
{
    if (!window) {
        std::cerr << "Error: GLFW window is null\n";
        return;
    }

    glfwGetWindowSize(window, &width, &height);

}

/**
 * @brief Initializes the application by setting up the shader, loading models, and configuring OpenGL states.
 *
 * This function performs the following actions:
 * - Creates and assigns the default shader program using vertex and fragment shader files.
 * - Initiates the model loading process.
 * - Enables depth testing and sets the depth function to GL_LESS for proper 3D rendering.
 * - Enables face culling and sets it to cull back faces to optimize rendering.
 */
void Application::init() {
    currentShader = std::make_unique<Shader>(shaderPath + "/default.vert", shaderPath + "/default.frag");

    pollModelLoad(); 

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Application::pollModelLoad() {
    std::ifstream modelFile(modelPath + "/current_model.txt");
    if (!modelFile) {
        std::cerr << "Error: Could not open current_model.txt\n";
        return;
    }

    std::string modelName;
    std::getline(modelFile, modelName);
    currentModelPath = modelPath + "/" + modelName;

    if (currentModelPath != lastLoadedModelPath) {
        std::cout << "Model change detected. Loading: " << modelName << "\n";
        loadModel(currentModelPath);
    }
}

void Application::loadModel(const std::string& path) {
    if (!currentMesh.loadFromOBJ(path)) {
        std::cerr << "Error: Failed to load model: " << path << "\n";
        return;
    }

    lastLoadedModelPath = path;

    glm::vec3 center = currentMesh.getBoundingSphereCentre();
    float radius     = currentMesh.getBoundingSphereRadius();

    camera.setTarget(center);
    camera.setBoundingRadius(radius);

    std::cout << "Model loaded: " << path << "\n";
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        pollModelLoad(); 

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.updateMatrices(width, height);

        currentShader->use();
        currentShader->setUniformMat4("uModel", camera.model());
        currentShader->setUniformMat4("uView",  camera.view());
        currentShader->setUniformMat4("uProj",  camera.proj());

        currentMesh.draw();

        glfwSwapBuffers(window);
    }
}
