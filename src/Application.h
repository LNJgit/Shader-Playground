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

struct ShaderInfo {
    std::string name;
    std::string vertexPath;
    std::string fragmentPath;
};

class Application {

    friend class ImGuiLayer;

public: 
    Application(GLFWwindow* window);  
    ~Application();                                
    void loadModel(const std::string& modelName);  
    void loadShader(const std::string& vertPath, const std::string& fragPath);
    void init();               
    void run();      
    void loadAvailableModels(); 
    void loadAvailableShaders();

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
    const std::string shaderPath = "../../assets/shaders";    
    
    std::vector<ModelInfo> availableModels;
    std::vector<ShaderInfo> availableShaders;

    std::string currentModelPath;      
    std::string lastLoadedModelPath;
};