#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/gtc/matrix_transform.hpp> 

//Default constructor
Mesh::Mesh() : VAO(0), VBO(0), vertexCount(0) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

//Destructor
Mesh::~Mesh() {
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
}

void Mesh::loadFromVertices(const std::vector<float> &vertices, int components) {
    vertexCount = vertices.size() / components ;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float),vertices.data() ,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, components, GL_FLOAT, GL_FALSE, components * sizeof(float), (void*)0);
    
    glBindVertexArray(0);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

// Very basic .obj loader (triangles only, no normals/UVs)
bool Mesh::loadFromOBJ(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Failed to load OBJ file: " << filepath << "\n";
        return false;
    }

    std::vector<float> vertices;
    std::vector<glm::vec3> temp_positions;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            temp_positions.emplace_back(x, y, z);
        } else if (prefix == "f") {
            int v1, v2, v3;
            char slash;
            ss >> v1 >> v2 >> v3;
            vertices.insert(vertices.end(), {
                temp_positions[v1 - 1].x, temp_positions[v1 - 1].y, temp_positions[v1 - 1].z,
                temp_positions[v2 - 1].x, temp_positions[v2 - 1].y, temp_positions[v2 - 1].z,
                temp_positions[v3 - 1].x, temp_positions[v3 - 1].y, temp_positions[v3 - 1].z
            });
        }
    }

    loadFromVertices(vertices);
    return true;
}
