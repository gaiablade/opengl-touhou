#include "Entity.h"

Entity::Entity(const std::string& textureFile, ga::Shader* shader)
{
    this->texture = new ga::Texture(textureFile);
    this->size = { this->texture->getWidth(), this->texture->getHeight() };
    if (!shader) this->shader = new ga::Shader("res/shaders/spriteShader.glsl");
    else this->shader = shader;
    this->sprite = ga::Sprite(this->texture);
    this->sprite.setShader(this->shader);
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
