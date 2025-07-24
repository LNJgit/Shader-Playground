#pragma once

#include "Mesh.h"
#include "OrbitCamera.h"
#include "RemoteAPI.h"
#include <GLFW/glfw3.h>
#include <string>

class Application {
public:
    // Constructor: pass in the GLFW window
    explicit Application(GLFWwindow* window);

    // Called once per frame: draws and handles updates
    void update();

    // Switch to a different model by name
    void switchModel(const std::string& name);

    // Check external request (e.g., file) to change model
    void pollModelChange();

    // Access camera for setting matrices
    const OrbitCamera& getCamera() const { return camera; }

private:
    GLFWwindow* window;
    Mesh mesh;
    OrbitCamera camera;
    RemoteAPI api;

    std::string lastModel;
};
