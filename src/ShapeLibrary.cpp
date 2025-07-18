#include "ShapeLibrary.h"

std::vector<float> ShapeLibrary::getVertices(ShapeType type) {
    switch (type) {
        case ShapeType::Quad:
            return {
                -1.0f,  1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f,
                 1.0f, -1.0f, 0.0f,
                -1.0f,  1.0f, 0.0f,
                 1.0f, -1.0f, 0.0f,
                 1.0f,  1.0f, 0.0f
            };
        case ShapeType::Triangle:
            return {
                 0.0f,  0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f
            };
        case ShapeType::FullscreenTriangle:
            return {
                -1.0f, -1.0f, 0.0f,
                 3.0f, -1.0f, 0.0f,
                -1.0f,  3.0f, 0.0f
            };
        default:
            return {};
    }
}
