#include "OrbitCamera.h"

// Constructor: register callbacks
OrbitCamera::OrbitCamera(GLFWwindow* window, glm::vec3 target, float distance, float yaw, float pitch)
  : _win(window), _target(target), _radius(distance), _yaw(yaw), _pitch(pitch)
{
    int w, h;
    glfwGetFramebufferSize(_win, &w, &h);
    _lastX = w * 0.5f;
    _lastY = h * 0.5f;

    glfwSetMouseButtonCallback(_win, mouseButtonCB);
    glfwSetCursorPosCallback  (_win, cursorPosCB);
    glfwSetScrollCallback     (_win, scrollCB);


    glfwSetWindowUserPointer(_win, this);
}

// Static wrappers retrieve instance pointer then forward
void OrbitCamera::mouseButtonCB(GLFWwindow* w, int b, int a, int m) {
    static_cast<OrbitCamera*>(glfwGetWindowUserPointer(w))->onMouseButton(b,a,m);
}
void OrbitCamera::cursorPosCB(GLFWwindow* w, double x, double y) {
    static_cast<OrbitCamera*>(glfwGetWindowUserPointer(w))->onCursorPos(x,y);
}
void OrbitCamera::scrollCB(GLFWwindow* w, double xoff, double yoff) {
    static_cast<OrbitCamera*>(glfwGetWindowUserPointer(w))->onScroll(xoff,yoff);
}

// Instance handlers
void OrbitCamera::onMouseButton(int button, int action, int /*mods*/) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        _rotating = (action == GLFW_PRESS);
    }
    if (_rotating) {
        glfwGetCursorPos(_win, &_lastX, &_lastY);
    }
}

void OrbitCamera::onCursorPos(double x, double y) {
    if (!_rotating) return;
      float dx = float(x - _lastX);
    float dy = float(y - _lastY);
    _lastX = float(x); _lastY = float(y);

    constexpr float SENS = 0.5f;
    _yaw   += dx * SENS;
    _pitch += dy * SENS;    
    _pitch  = glm::clamp(_pitch, -89.0f, 89.0f);
}

void OrbitCamera::onScroll(double /*xoff*/, double yoff) {
    _radius = glm::clamp(_radius - float(yoff)*0.5f, 1.0f, 50.0f);
}

void OrbitCamera::updateMatrices(int fbWidth, int fbHeight) {
    // never let camera come closer than needed to see the whole sphere
    _radius = std::max(_radius, _minRadius);

    float aspect = float(fbWidth) / float(fbHeight);
    _proj = glm::perspective(_fovY, aspect, 0.1f, _radius + _boundingRadius);

 
    float radYaw   = glm::radians(_yaw);
    float radPitch = glm::radians(_pitch);
    glm::vec3 pos = {
        _target.x + _radius * cos(radPitch) * cos(radYaw),
        _target.y + _radius * sin(radPitch),
        _target.z + _radius * cos(radPitch) * sin(radYaw)
    };

    _view = glm::lookAt(pos, _target, {0,1,0});
}


