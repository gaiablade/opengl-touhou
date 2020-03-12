#pragma once
#include <iostream>
#include "GaiaGL/Graphics.h"
#include "GaiaGL/Input.h"

struct Size2D {
    float width, height;
};

class Entity {
    protected:
        ga::Position2D position;
        ga::Velocity2D velocity;
        ga::Size2D size;
        ga::Texture* texture;
        ga::Rect2D sprite;
    public:
        Entity(const std::string& textureFile, ga::Shader* shader = nullptr);
        Entity(ga::Color color, float width, float height);
        ~Entity();
        virtual void update(float dt);
        virtual void draw(ga::Renderer* renderer);
        inline ga::Size2D& getSize() { return this->size; }
        inline ga::Position2D& getPosition() { return this->position; }
};
