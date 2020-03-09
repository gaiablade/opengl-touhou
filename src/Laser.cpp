#include "Laser.h"

ga::Shader* Laser::laserShader = nullptr;

Laser::Laser(const int& width, const int& height, const float& x, const float& y, ga::Shader* shader)
    : sprite(ga::Color{0.0f, 1.0f, 0.0f, 1.0f}, width, height)
{
    if (!Laser::laserShader) {
        Laser::laserShader = new Shader("res/shaders/colorShader.glsl");
    }
    this->shader = Laser::laserShader;
    this->sprite.setShader(this->shader);
    this->sprite.setColor(0.0f, 1.0f, 0.0f);
    this->position.x = x;
    this->position.y = y;
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
