#include <glad/gl.h>    
#include <GLFW/glfw3.h> 
#include <glm/gtc/matrix_transform.hpp>
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

    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // optionally, cull back faces so you only ever see front faces
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Mesh mesh;
    mesh.loadFromOBJ("../../assets/models/armadillo.obj");


    Shader shader("../../shaders/default.vert", "../../shaders/default.frag");



    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int w, h; glfwGetFramebufferSize(window, &w, &h);
        glViewport(0,0,w,h);
        glClearColor(0.1f,0.1f,0.1f,1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(2,2,2), glm::vec3(0), glm::vec3(0,1,0));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)w / h, 0.1f, 100.0f);


        shader.use();
        shader.setUniformMat4("uModel", model);
        shader.setUniformMat4("uView",  view);
        shader.setUniformMat4("uProj",  projection);
        mesh.draw();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}