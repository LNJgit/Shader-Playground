#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


std::string Shader::loadSource(const std::string& p) const {
    std::ifstream f(p, std::ios::in);
    if (!f.is_open()) {
        std::cerr << "[Shader] Failed to open " << p << '\n';
        return "";                      
    }
    std::stringstream ss; ss << f.rdbuf();
    return ss.str();
}

GLuint Shader::compile(const std::string& src, GLenum type) const
{
    GLuint id = glCreateShader(type);
    const char* code = src.c_str();
    glShaderSource(id, 1, &code, nullptr);
    glCompileShader(id);

    GLint ok;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(id, 1024, nullptr, log);
        std::cerr << "Shader compile error:\n" << log << std::endl;
    }
    return id;

}

Shader::Shader(const std::string& vertPath, const std::string& fragPath) {
    GLuint vs = compile(loadSource(vertPath), GL_VERTEX_SHADER);
    GLuint fs = compile(loadSource(fragPath), GL_FRAGMENT_SHADER);

    program_ = glCreateProgram();
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glLinkProgram(program_);

    GLint ok;
    glGetProgramiv(program_, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetProgramInfoLog(program_, 1024, nullptr, log);
        std::cerr << "Program link error:\n" << log << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::use() const { glUseProgram(program_); }

void Shader::setUniform2f(const std::string& name, float v0, float v1) const {
    GLint loc = glGetUniformLocation(program_, name.c_str());
    glUniform2f(loc, v0, v1);
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& matrix) const {
    GLint loc = glGetUniformLocation(program_, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::~Shader() { glDeleteProgram(program_); }