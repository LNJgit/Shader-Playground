#ifndef MESH_H
#define MESH_H

#include <glad/gl.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>

class Mesh {
public:
    Mesh();
    ~Mesh();

    void loadFromVertices(const std::vector<float>& vertices, int components = 3);
    bool loadFromOBJ(const std::string& filepath);
    void computeBounds();
    glm::vec3 getBoundingSphereCentre();
    float getBoundingSphereRadius();
    void draw() const;

private:
    GLuint VAO, VBO;
    int vertexCount;
    std::vector<float> _vertices;
    glm::vec3 maxBound, minBound;
    glm::vec3 boundSphereCenter;
    float boundSphereRadius;
};

#endif
