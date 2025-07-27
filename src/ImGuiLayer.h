#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "Application.h"

class Application;

class ImGuiLayer {
public:
    ImGuiLayer(Application* parentApp);
    void init(GLFWwindow* window);
    void begin();
    void end();
    void shutdown();

private:
    bool initialized = false;
    Application* parent = nullptr;
};


