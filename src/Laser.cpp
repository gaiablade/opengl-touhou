#include "Laser.h"

Laser::Laser(const int& width, const int& height, ga::Shader* shader)
    : sprite(width, height)
{
    if (!shader) this->shader = new ga::Shader("res/shaders/colorShader.glsl");
    else this->shader = shader;
    this->sprite.setShader(this->shader);
    this->sprite.setColor(0.0f, 1.0f, 0.0f);
    this->position.x = 100.0f;
    this->position.y = 50.0f;
    this->sprite.setPosition(this->position.x, this->position.y);
}

Laser::~Laser() {
}

void Laser::update(float dt) {
    this->position.y += LASER_SPEED * dt;
    this->sprite.setPosition(this->position.x, this->position.y);
}

void Laser::draw(ga::Renderer* renderer) {
    renderer->Draw(this->sprite);
}
