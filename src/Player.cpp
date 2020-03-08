#include "Player.h"

bool Player::left = false;
bool Player::right = false;
bool Player::up = false;
bool Player::down = false;

Player::Player(ga::Shader* shader) {
    this->texture = new ga::Texture("res/textures/ship_34x37.png");
    if (!shader) this->shader = new ga::Shader("res/shaders/spriteShader.glsl");
    else this->shader = shader;
    this->sprite = ga::Sprite(this->texture);
    this->sprite.setShader(this->shader);
    this->inputHandler.callback = this->dcCallback;
    this->position.x = 0;
    this->position.y = 0;
}

Player::~Player() {
}

void Player::update(float dt) {
    this->position.x -= Player::left  ? 1 : 0 * dt * PLAYER_SPEED;
    this->position.x += Player::right ? 1 : 0 * dt * PLAYER_SPEED;
    this->position.y -= Player::down  ? 1 : 0 * dt * PLAYER_SPEED;
    this->position.y += Player::up    ? 1 : 0 * dt * PLAYER_SPEED;
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
