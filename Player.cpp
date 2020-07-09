#include "Player.hpp"

namespace th {
    Player::Player()
        : coll(ga::ColliderOpt{10.f, 10.f})
    {
        this->sprite = nullptr;
    }

    void Player::update() {
        frame++;
        this->coll.setPosition(this->position);
    }

    void Player::render(ga::Window& window) {
        this->sprite->setPosition(this->position);
        window.getRenderer().Draw(*sprite);
        this->sprite->setColor(ga::Color(1.0f, 0.0f, 0.0f, 1.0f));
    }
}