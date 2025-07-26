#include <glad/gl.h>    
#include <GLFW/glfw3.h> 
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>  

#include "Shader.h"  
#include "Application.h"

int main() {
    // ── Remote API Connectivity ─────────────────────────
    RemoteAPI api;

    // ── GLFW Init ───────────────────────────────────────
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For macOS
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "Shader Playground", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);

    // ── Shader and App Setup ────────────────────────────
    Shader shader("../../../assets/shaders/default.vert", "../../../assets/shaders/default.frag");
    Application app(window);

    // ── Main Loop ───────────────────────────────────────
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        shader.use();
        shader.setUniformMat4("uModel", glm::mat4(1.0f));
        shader.setUniformMat4("uView",  app.getCamera().view());
        shader.setUniformMat4("uProj",  app.getCamera().proj());

        app.update(); 
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
