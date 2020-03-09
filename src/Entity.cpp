#include "Entity.h"

Entity::Entity(const std::string& textureFile, ga::Shader* shader)
    : texture(new ga::Texture(textureFile)), sprite(this->texture)
{
    this->size = { this->texture->getWidth(), this->texture->getHeight() };
    this->position.x = 0;
    this->position.y = 0;
}

Entity::~Entity() {
}

void Entity::update(float dt) {
    this->sprite.setPosition(this->position.x, this->position.y);
}

void Entity::draw(ga::Renderer* renderer) {
    renderer->Draw(this->sprite);
}
