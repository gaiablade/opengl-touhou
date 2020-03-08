#include "Player.h"

bool Player::left = false;
bool Player::right = false;
bool Player::up = false;
bool Player::down = false;

Player::Player() {
    this->texture = new ga::Texture("res/textures/ship_34x37.png");
    this->shader = new ga::Shader("res/shaders/spriteShader.glsl");
    this->sprite = ga::Sprite(this->texture);
    this->sprite.setShader(this->shader);
    this->inputHandler.callback = this->dcCallback;
}

Player::~Player() {
}

void Player::update(float dt) {
    this->position.x -= (int)Player::left * dt * PLAYER_SPEED;
    this->position.x += (int)Player::right * dt * PLAYER_SPEED;
    this->position.y -= (int)Player::down * dt * PLAYER_SPEED;
    this->position.y += (int)Player::up * dt * PLAYER_SPEED;
    this->sprite.setPosition(this->position.x, this->position.y);
}

void Player::draw(ga::Renderer* renderer) {
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
    }
}
