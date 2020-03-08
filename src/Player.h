#pragma once
#include <iostream>
#include "OpenGLLib/Graphics.h"
#include "OpenGLLib/Input.h"

const int PLAYER_SPEED = 100;

class Player {
    private:
        ga::Position2D position;
        ga::Velocity2D velocity;
        ga::Texture* texture;
        ga::Sprite sprite;
        ga::Shader* shader;
    public:
        Player(ga::Shader* shader = nullptr);
        ~Player();
        void update(float dt);
        void draw(ga::Renderer* renderer);
        static void dcCallback(uint32_t keyCode);
        static bool left, right, down, up;
        ga::DirectionalComponent inputHandler;
};
