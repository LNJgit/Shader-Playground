#include "Application.h"
#include <fstream>
#include <iostream>

Application::Application(GLFWwindow* win)
    : window(win), camera(win), api("http://127.0.0.1:8000") {

    auto models = api.fetchModelList();
    if (!models.empty()) {
        switchModel(models[0]);
    }
}

void Application::switchModel(const std::string& name) {
    std::string path = "../../../assets/models/" + name;
    if (!mesh.loadFromOBJ(path)) {
        std::cerr << "[App] Failed to load model: " << name << "\n";
        return;
    }

    glm::vec3 center = mesh.getBoundingSphereCentre();
    float radius     = mesh.getBoundingSphereRadius();
    camera.setTarget(center);
    camera.setBoundingRadius(radius);
    camera.resetCamera();
    lastModel = name;

    std::cout << "[App] Switched model to: " << name << "\n";
}

void Application::pollModelChange() {
    std::ifstream file("../../../assets/current_model.txt");
    if (!file.is_open()) return;

    std::string name;
    std::getline(file, name);
    if (!name.empty() && name != lastModel) {
        switchModel(name);
    }
}

void Application::update() {
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pollModelChange();
    camera.updateMatrices(w, h);

    mesh.draw();
}
