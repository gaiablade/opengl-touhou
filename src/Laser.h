#pragma once
#include <iostream>
#include "OpenGLLib/Graphics.h"

#include "Player.h"

const float LASER_SPEED = 300;

class Laser {
    friend class Player;
    public:
        Laser(const int& width, const int& height, const float& x, const float& y, ga::Shader* shader = nullptr);
        ~Laser();
        void update(float dt);
        void draw(ga::Renderer* renderer);
        static ga::Shader* laserShader;
    private:
        ga::Position2D position;
        ga::Velocity2D velocity;
        ga::Sprite sprite;
        ga::Shader* shader;
};
