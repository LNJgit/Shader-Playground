#include <glad/gl.h>    
#include <GLFW/glfw3.h> 
#include <iostream>  
#include "Shader.h"  
#include "Mesh.h"
#include "ShapeLibrary.h"

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version to 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For macOS
#endif

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Shader Playground", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    // Load GL functions
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    Mesh mesh;
    mesh.loadFromVertices(ShapeLibrary::getVertices(ShapeType::Triangle));



    Shader shader("../../shaders/default.vert", "../../shaders/default.frag");



    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int w, h; glfwGetFramebufferSize(window, &w, &h);
        glViewport(0,0,w,h);
        glClearColor(0.1f,0.1f,0.1f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setUniform2f("iResolution", w,h);
        mesh.draw();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}