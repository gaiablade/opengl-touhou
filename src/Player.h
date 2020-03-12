#pragma once
#include <iostream>
#include <list>
#include "GaiaGL/Graphics.h"
#include "GaiaGL/Input.h"

#include "Entity.h"
#include "Enemy.h"
#include "Laser.h"

class Laser;

const int PLAYER_SPEED = 200;
const float LASER_DELAY = 0.2f;

class Player : public Entity {
    private:
        float lastLaser;
        std::list<Laser*> lasers;
        std::list<Enemy*>* enemies;
    public:
        Player(ga::Shader* shader = nullptr);
        ~Player();
        void update(float dt);
        void draw(ga::Renderer* renderer);
        static void dcCallback(uint32_t keyCode);
        static bool left, right, down, up, z;
        ga::DirectionalComponent inputHandler;
        inline void setEnemyListPointer(std::list<Enemy*>* enemyList) { this->enemies = enemyList; }
        float rotation;
};
