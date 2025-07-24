#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#define TINYOBJLOADER_IMPLEMENTATION  
#include <tiny_obj_loader.h>

// Constructor
Mesh::Mesh() : VAO(0), VBO(0), vertexCount(0) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

// Destructor
Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::loadFromVertices(const std::vector<float>& vertices, int components) {
    vertexCount = vertices.size() / components;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, components, GL_FLOAT, GL_FALSE, components * sizeof(float), (void*)0);

    glBindVertexArray(0);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void Mesh::computeBounds() {
    minBound = glm::vec3(1e37);
    maxBound = glm::vec3(1e-37);

    for (size_t i = 0; i < _vertices.size(); i += 8) {
        glm::vec3 p{ _vertices[i+0], _vertices[i+1], _vertices[i+2] };
        minBound = glm::min(minBound, p);
        maxBound = glm::max(maxBound, p);
    }

    boundSphereCenter = (minBound + maxBound)*0.5f;
    boundSphereRadius = glm::length(minBound-boundSphereCenter);
}

glm::vec3 Mesh::getBoundingSphereCentre(){
    return boundSphereCenter;
}

float Mesh::getBoundingSphereRadius(){
    return boundSphereRadius;
}

bool Mesh::loadFromOBJ(const std::string& path)
{
    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig cfg;
    cfg.mtl_search_path = path.substr(0, path.find_last_of("/\\"));
    cfg.triangulate = true;

    if (!reader.ParseFromFile(path, cfg)) {
        std::cerr << "tinyobj: " << reader.Error() << "\n";
        return false;
    }

    const auto& attrib  = reader.GetAttrib();
    const auto& shapes  = reader.GetShapes();

    _vertices.clear();
    bool hasNormals = !attrib.normals.empty();

        for (const auto& shape : shapes) {
            size_t index_offset = 0;
            for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
                int fv = shape.mesh.num_face_vertices[f];
                if (fv != 3) {
                    std::cerr << "Non-triangle face detected. Skipping.\n";
                    index_offset += fv;
                    continue;
                }

                glm::vec3 faceVerts[3];
                glm::vec2 faceUVs[3];

                for (size_t v = 0; v < 3; ++v) {
                    tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                    glm::vec3 pos = {
                        attrib.vertices[3*idx.vertex_index + 0],
                        attrib.vertices[3*idx.vertex_index + 1],
                        attrib.vertices[3*idx.vertex_index + 2]
                    };
                    faceVerts[v] = pos;

                    glm::vec2 uv = (idx.texcoord_index >= 0 && !attrib.texcoords.empty())
                        ? glm::vec2(
                            attrib.texcoords[2*idx.texcoord_index + 0],
                            attrib.texcoords[2*idx.texcoord_index + 1]
                        )
                        : glm::vec2(0.0f);
                    faceUVs[v] = uv;
                }

                // Compute flat normal if needed
                glm::vec3 nrm(0.0f);
                if (!hasNormals) {
                    glm::vec3 edge1 = faceVerts[1] - faceVerts[0];
                    glm::vec3 edge2 = faceVerts[2] - faceVerts[0];
                    nrm = glm::normalize(glm::cross(edge1, edge2));
                }

                // Push the triangle
                for (int v = 0; v < 3; ++v) {
                    glm::vec3 pos = faceVerts[v];
                    glm::vec2 uv = faceUVs[v];

                    glm::vec3 finalNrm = nrm;
                    if (hasNormals) {
                        tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                        if (idx.normal_index >= 0) {
                            finalNrm = {
                                attrib.normals[3*idx.normal_index + 0],
                                attrib.normals[3*idx.normal_index + 1],
                                attrib.normals[3*idx.normal_index + 2]
                            };
                        }
                    }

                    _vertices.insert(_vertices.end(), {
                        pos.x, pos.y, pos.z,
                        uv.x, uv.y,
                        finalNrm.x, finalNrm.y, finalNrm.z
                    });
                }

                index_offset += fv;
            }
        }



    // Upload interleaved data: pos(3), uv(2), normal(3)

    vertexCount = static_cast<int>(_vertices.size() / 8);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 _vertices.size() * sizeof(float),
                 _vertices.data(),
                 GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float),
                          (void*)0);

    // uv attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float),
                          (void*)(3 * sizeof(float)));

    // normal attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
                          8 * sizeof(float),
                          (void*)(5 * sizeof(float)));

    glBindVertexArray(0);

    computeBounds();
    return true;
}
