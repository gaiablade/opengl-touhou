#pragma once

namespace ga {
    struct Scale2D {
        float x, y;
        Scale2D() : x(1.0f), y(1.0f) {}
        Scale2D(const float& x, const float& y) : x(x), y(y) {}
    };
};
