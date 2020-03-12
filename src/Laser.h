#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "GaiaGL/Graphics.h"

const float LASER_SPEED = 525.0f;

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
        //ga::Position2D position;
        std::vector<ga::Velocity2D> velocities;
        //ga::Velocity2D velocity;
        ga::Size2D size;
        float rValue;
        std::vector<ga::Rect2D*> sprites;
        ga::Shader* shader;
};
