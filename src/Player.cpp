#include "Player.h"

bool Player::left = false;
bool Player::right = false;
bool Player::up = false;
bool Player::down = false;
bool Player::z = false;

Player::Player(ga::Shader* shader)
    : Entity("res/textures/ship_34x37.png", shader), lastLaser(LASER_DELAY)
{
    this->inputHandler.callback = this->dcCallback;
    this->position.x = 0;
    this->position.y = 0;
}

Player::~Player() {
}

void Player::update(float dt) {
    this->lastLaser += dt;
    this->position.x -= (Player::left  ? 1 : 0) * dt * PLAYER_SPEED;
    this->position.x += (Player::right ? 1 : 0) * dt * PLAYER_SPEED;
    this->position.y -= (Player::down  ? 1 : 0) * dt * PLAYER_SPEED;
    this->position.y += (Player::up    ? 1 : 0) * dt * PLAYER_SPEED;
    if (Player::z && this->lastLaser >= LASER_DELAY) {
        this->lasers.push_back(new Laser(5, 20, this->position.x + this->size.width / 2, this->position.y + this->size.height - 10));
        this->lastLaser = 0;
    }
    for (std::list<Laser*>::iterator laser = this->lasers.begin(); laser != this->lasers.end(); laser++) {
        (*laser)->update(dt);
        if ((*laser)->position.y > 600) {
            delete *laser;
            this->lasers.erase(laser);
            break;
        }
    }
    this->sprite.setPosition(this->position.x, this->position.y);
}

void Player::draw(ga::Renderer* renderer) {
    for (auto& laser : this->lasers) {
        laser->draw(renderer);
    }
    renderer->Draw(this->sprite);
}

void Player::dcCallback(uint32_t keyCode) {
    switch (keyCode) {
        case 1u: Player::left = true;
                 break;
        case 2u: Player::right = true;
                 break;
        case 3u: Player::up = true;
                 break;
        case 4u: Player::down = true;
                 break;
        case 5u: Player::left = false;
                 break;
        case 6u: Player::right = false;
                 break;
        case 7u: Player::up = false;
                 break;
        case 8u: Player::down = false;
                 break;
        case 9u: Player::z = true;
                 break;
        case 10u: Player::z = false;
                  break;
    }
}
