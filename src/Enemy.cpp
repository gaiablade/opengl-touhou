#include "Enemy.h"

Enemy::Enemy(ga::Shader* shader)
    : Entity("res/textures/enemy_22x23.png", shader)
{
    this->position.x = 100;
    this->position.y = 600;
}

Enemy::~Enemy() {
}

void Enemy::update(float dt) {
    this->position.y -= dt * ENEMY_SPEED;
    this->sprite.setPosition(this->position.x, this->position.y);
}
