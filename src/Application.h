#pragma once

#include <string>
#include <memory>
#include <glad/gl.h>
#include "OrbitCamera.h"
#include "Mesh.h"
#include "Shader.h"
#include "ImGuiLayer.h"
#include <nlohmann/json.hpp>

class ImGuiLayer;

struct ModelInfo {
    std::string name;
    std::string file;
};

class Application {

    friend class ImGuiLayer;

public: 
    Application(GLFWwindow* window);  
    ~Application();                                
    void loadModel(const std::string& modelName);  
    void init();               
    void run();      
    void loadAvailableModels(); 

    std::vector<ModelInfo> getAvailableModels() const {
        return availableModels;
    }                       

private:
    GLFWwindow* window;      
    OrbitCamera camera; 
    std::unique_ptr<ImGuiLayer> gui;    
    Mesh currentMesh;          
    std::unique_ptr<Shader> currentShader;
    std::string title;        
    int width, height;        

    const std::string modelPath = "../../assets/models";   
    const std::string shaderPath = "../../shaders";    
    
    std::vector<ModelInfo> availableModels;

    std::string currentModelPath;      
    std::string lastLoadedModelPath;
};