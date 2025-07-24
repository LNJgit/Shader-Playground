#pragma once
#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>

class Shader
{
    public:

    //It will construct the shader from the paths to the vert and frag files.
    Shader(const std::string& vertPath, const std::string& fragPath);

    //Bind the shader when drawing
    void use() const;

    //Uniform helper
    void setUniform2f(const std::string& name, float v0, float v1) const;
    void setUniformMat4(const std::string& name, const glm::mat4& matrix) const;

    //Clean up GPU program
    ~Shader();

    private:

    GLuint program_{0};

    std::string loadSource(const std::string& path) const;
    GLuint compile(const std::string& src, GLenum type) const;

};