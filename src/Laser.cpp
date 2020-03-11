#include "Laser.h"

ga::Shader* Laser::laserShader = nullptr;

Laser::Laser(const int& width, const int& height, const float& x, const float& y)
    : sprite(ga::Color{0.0f, 1.0f, 0.0f, 1.0f}, width, height), rValue(0.0f)
{
    this->position.x = x;
    this->position.y = y;
    this->sprite.setPosition(this->position.x, this->position.y);
}

Laser::~Laser() {
}

void Laser::update(float dt) {
    this->position.y += LASER_SPEED * dt;
    this->sprite.setPosition(this->position.x, this->position.y);
    this->rValue += 0.1;
    if (this->rValue > 1) this->rValue = 0;
    ga::Color col = this->sprite.rect->getColor();
    this->sprite.rect->setColor(ga::Color{this->rValue, col.g, col.b, col.a});
}

void Laser::draw(ga::Renderer* renderer) {
    renderer->Draw(this->sprite);
}
