#include "Laser.h"

#define PI 3.14159265

ga::Shader* Laser::laserShader = nullptr;

Laser::Laser(const int& width, const int& height, const float& x, const float& y)
    : rValue(0.0f)
{
    this->size.width = width;
    this->size.height = height;

    ga::Color laserColor{0.5f, 1.0f, 0.3f, 0.7f};

    ga::Rect2D* centerLaser = new ga::Rect2D(laserColor, width, height);
    this->sprites.push_back(centerLaser);
    this->velocities.push_back(ga::Velocity2D{0.0f, 1.0f});
    this->positions.push_back(ga::Position2D{x, y});

    float leftAngle = 15.0f;
    ga::Rect2D* rightLaser = new ga::Rect2D(laserColor, width, height);
    rightLaser->setRotation(360.0f - leftAngle);
    this->sprites.push_back(rightLaser);
    this->velocities.push_back(ga::Velocity2D{sin(leftAngle * PI / 180), cos(leftAngle * PI / 180)});
    this->positions.push_back(ga::Position2D{x, y});

    float rightAngle = -15.0f;
    ga::Rect2D* leftLaser = new ga::Rect2D(laserColor, width, height);
    leftLaser->setRotation(360.0f - rightAngle);
    this->sprites.push_back(leftLaser);
    this->velocities.push_back(ga::Velocity2D{sin(rightAngle * PI / 180), cos(rightAngle * PI / 180)});
    this->positions.push_back(ga::Position2D{x, y});
}

Laser::~Laser() {
}

void Laser::update(float dt) {
    for (int i = 0; i < this->sprites.size(); i++) {
        this->positions[i].x += this->velocities[i].x * dt * LASER_SPEED;
        this->positions[i].y += this->velocities[i].y * dt * LASER_SPEED;
        this->sprites[i]->setPosition(this->positions[i].x, this->positions[i].y);
    }
}

void Laser::draw(ga::Renderer* renderer) {
    for (auto& laser: this->sprites) {
        renderer->Draw(*laser);
    }
}
