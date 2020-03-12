#include "Enemy.h"

Enemy::Enemy(ga::Shader* shader)
    : Entity("res/textures/enemy_22x23.png", shader),
    destroyed(false)
{
    this->position.x = rand() % 800;
    this->position.y = 600;
    this->sprite.setPosition(this->position.x, this->position.y);
}

Enemy::~Enemy() {
}

void Enemy::update(float dt) {
    this->position.y -= dt * ENEMY_SPEED;
    this->sprite.setPosition(this->position.x, this->position.y);
}
