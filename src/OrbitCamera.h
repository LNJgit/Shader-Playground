#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class OrbitCamera {
public:
    OrbitCamera(GLFWwindow* window,
                glm::vec3 target = {0,0,0},
                float  distance = 5.0f,
                float  yaw      = -90.0f,
                float  pitch    =   0.0f);

    // Call once per frame before drawing
    void updateMatrices(int fbWidth, int fbHeight);

    void setTarget(const glm::vec3& target) { _target = target; }

    void setBoundingRadius(float radius) {
        _boundingRadius = radius;
        _minRadius = _boundingRadius / std::sin(_fovY * 0.5f);
        _radius = std::max(_radius, _minRadius);
    }

    // Getters for shaders
    const glm::mat4& view() const noexcept { return _view; }
    const glm::mat4& proj() const noexcept { return _proj; }
    const glm::mat4& model() const noexcept { return _model; }

private:
    // GLFW callbacks
    static void mouseButtonCB(GLFWwindow*, int, int, int);
    static void cursorPosCB  (GLFWwindow*, double, double);
    static void scrollCB     (GLFWwindow*, double, double);

    // Instance methods
    void  onMouseButton(int button, int action, int mods);
    void  onCursorPos  (double x, double y);
    void  onScroll     (double /*xoff*/, double yoff);

    // Internal state
    GLFWwindow* _win;
    glm::vec3   _target;
    glm::mat4   _view, _proj, _model = glm::mat4(1.0f);
    float       _yaw, _pitch, _radius;
    double       _lastX, _lastY;
    bool        _rotating = false;
    float       _fovY     = glm::radians(45.0f);
    float     _boundingRadius = 1.0f;  
    float     _minRadius      = 1.0f;   
};
