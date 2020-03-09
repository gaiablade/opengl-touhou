#pragma once
#include <iostream>
#include "OpenGLLib/Graphics.h"
#include "OpenGLLib/Input.h"

struct Size2D {
    float width, height;
};

class Entity {
    protected:
        ga::Position2D position;
        ga::Velocity2D velocity;
        ga::Size2D size;
        ga::Texture* texture;
        ga::Sprite sprite;
        ga::Shader* shader;
    public:
        Entity(const std::string& textureFile, ga::Shader* shader = nullptr);
        ~Entity();
        virtual void update(float dt);
        virtual void draw(ga::Renderer* renderer);
};
