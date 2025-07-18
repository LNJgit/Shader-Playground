#ifndef MESH_H
#define MESH_H

#include <glad/gl.h>
#include <vector>
#include <string>

class Mesh {

    public:
    Mesh();
    ~Mesh();

    void loadFromVertices(const std::vector<float> &vertices, int components = 3);
    bool loadFromOBJ(const std::string &filePath);
    void draw() const;

    private:

    GLuint VAO,VBO;
    int vertexCount;

};

#endif