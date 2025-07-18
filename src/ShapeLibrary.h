#pragma once
#include <vector>

enum class ShapeType {
    Quad,
    Triangle,
    FullscreenTriangle
};

class ShapeLibrary {
public:
    static std::vector<float> getVertices(ShapeType type);
};