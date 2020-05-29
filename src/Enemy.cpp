#include "Enemy.h"

#define EULER 0.577215664901532860606

Enemy::Enemy(ga::Shader* shader)
    : Entity("res/textures/enemy_22x23.png", shader),
    destroyed(false),
    lifespan(0.0)
{
    this->position.x = rand() % 800;
    this->position.y = 600;
    this->sprite.setPosition(this->position.x, this->position.y);
}

Enemy::~Enemy() {
}

void Enemy::update(float dt) {
    this->lifespan += dt;
    this->position.y -= dt * ENEMY_SPEED;
    this->sprite.setPosition(this->position.x, this->position.y);
    this->sprite.setScale(ga::Scale2D(sqrt(lifespan), sqrt(lifespan)));
}
