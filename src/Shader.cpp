#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>


std::string Shader::loadSource(const std::string& path) const
{
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();

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

void Shader::setUniform(const std::string& name, float v0, float v1) const {
    GLint loc = glGetUniformLocation(program_, name.c_str());
    glUniform2f(loc, v0, v1);
}

Shader::~Shader() { glDeleteProgram(program_); }