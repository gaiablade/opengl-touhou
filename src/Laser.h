#pragma once
#include <iostream>

#include "OpenGLLib/Graphics.h"

const float LASER_SPEED = 300;

class Laser {
    public:
        Laser(const int& width, const int& height, ga::Shader* shader = nullptr);
        ~Laser();
        void update(float dt);
        void draw(ga::Renderer* renderer);
    private:
        ga::Position2D position;
        ga::Velocity2D velocity;
        ga::Sprite sprite;
        ga::Shader* shader;
};
