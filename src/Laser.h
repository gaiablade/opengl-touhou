#pragma once
#include <iostream>
#include "GaiaGL/Graphics.h"

const float LASER_SPEED = 300;

class Laser {
    friend class Player;
    public:
        Laser(const int& width, const int& height, const float& x, const float& y);
        ~Laser();
        void update(float dt);
        void draw(ga::Renderer* renderer);
        static ga::Shader* laserShader;
    private:
        ga::Position2D position;
        ga::Velocity2D velocity;
        //ga::ColorRect sprite;
        float rValue;
        ga::Rect2D sprite;
        ga::Shader* shader;
};
