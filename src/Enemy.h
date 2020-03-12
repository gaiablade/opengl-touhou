#pragma once
#include <iostream>
#include "GaiaGL/Graphics.h"

#include "Entity.h"

const float ENEMY_SPEED = 75.0f;

class Enemy : public Entity {
    public:
        Enemy(ga::Shader* shader = nullptr);
        ~Enemy();
        void update(float dt);
        bool destroyed;
    private:
};
