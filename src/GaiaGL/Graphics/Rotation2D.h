#pragma once

namespace ga {
    struct Rotation2D {
        float angle;
        Rotation2D() : angle(0) {}
        Rotation2D(float angle) : angle(angle) {}
    };
};
