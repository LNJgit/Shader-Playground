#include "ImGuiLayer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>



ImGuiLayer::ImGuiLayer(Application* parentApp)
    : parent(parentApp), initialized(false) {}

void ImGuiLayer::init(GLFWwindow* window) {
    if (initialized) return;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext(); 

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui_ImplOpenGL3_Init("#version 330");     

    initialized = true;
}

void ImGuiLayer::begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Draw model selector using parent data
    ImGui::Begin("Model Selector");

    for (const auto& model : parent->availableModels) {
        if (ImGui::Button(model.name.c_str())) {
            std::string fullPath = parent->modelPath + "/" + model.file;
            parent->loadModel(fullPath);
        }
    }

    ImGui::End();
}

void ImGuiLayer::end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::shutdown() {
    if (!initialized) return;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    initialized = false;
}