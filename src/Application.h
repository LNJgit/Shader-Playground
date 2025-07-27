#pragma once

#include <string>
#include <memory>
#include <glad/gl.h>
#include "OrbitCamera.h"
#include "Mesh.h"
#include "Shader.h"


class Application {
public: 
    Application(GLFWwindow* window);                
    void pollModelLoad();                           
    void loadModel(const std::string& modelName);  
    void init();               
    void run();                              

private:
    GLFWwindow* window;      
    OrbitCamera camera;        
    Mesh currentMesh;          
    std::unique_ptr<Shader> currentShader;
    std::string title;        
    int width, height;        

    const std::string modelPath = "../../assets/models";   
    const std::string shaderPath = "../../shaders";      

    std::string currentModelPath;      
    std::string lastLoadedModelPath;
};