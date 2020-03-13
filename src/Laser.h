#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "GaiaGL/Graphics.h"

const float LASER_SPEED = 1000.0f;

class Laser {
    friend class Player;
    public:
        Laser(const int& width, const int& height, const float& x, const float& y);
        ~Laser();
        void update(float dt);
        void draw(ga::Renderer* renderer);
        static ga::Shader* laserShader;
    private:
        std::vector<ga::Position2D> positions;
        std::vector<ga::Velocity2D> velocities;
        ga::Size2D size;
        float rValue;
        std::vector<ga::Rect2D*> sprites;
        ga::Shader* shader;
};
