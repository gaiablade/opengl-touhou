#include "Rect2D.h"

namespace ga {
    Rect2D::Rect2D()
        : rect(nullptr)
    {
    }

    Rect2D::Rect2D(ga::Texture* texture)
        : rect(new ga::Sprite(texture))
    {
        if (!ShaderManager::genericSpriteShader) {
            ShaderManager::genericSpriteShader = new ga::Shader("GaiaGL/Graphics/shaders/spriteShader.glsl");
        }
        this->shader = ShaderManager::genericSpriteShader;
        this->rect->setShader(this->shader);
    }

    Rect2D::Rect2D(ga::Color color, const float& width, const float& height)
        : rect(new ga::ColorRect(color, width, height))
    {
        if (!ShaderManager::genericColorShader) {
            ShaderManager::genericColorShader = new ga::Shader("GaiaGL/Graphics/shaders/colorShader.glsl");
        }
        this->shader = ShaderManager::genericColorShader;
        this->rect->setShader(this->shader);
    }

    Rect2D::~Rect2D() {
        delete this->rect;
    }

    void Rect2D::setColor(ga::Color color) {
        if (!ShaderManager::genericColorShader) {
            ShaderManager::genericColorShader = new ga::Shader("GaiaGL/Graphics/shaders/colorShader.glsl");
        }
        this->shader = ShaderManager::genericColorShader;
        this->rect->setShader(this->shader);
        this->rect->setColor(color);
    }

    void Rect2D::setColor(const int& r, const int& g, const int& b, const int& a) {
        if (!ShaderManager::genericColorShader) {
            ShaderManager::genericColorShader = new ga::Shader("GaiaGL/Graphics/shaders/colorShader.glsl");
        }
        this->shader = ShaderManager::genericColorShader;
        this->rect->setShader(this->shader);
        this->rect->setColor(ga::Color{r, g, b, a});
    }
};
