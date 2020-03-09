#include "Rect2D.h"

namespace ga {
    Rect2D::Rect2D() {
    }

    Rect2D::Rect2D(ga::Texture* texture)
        : rect(new ga::Sprite(texture))
    {
        if (!ShaderManager::genericSpriteShader) {
            ShaderManager::genericSpriteShader = new ga::Shader("OpenGLLib/Graphics/shaders/spriteShader.glsl");
        }
        //this->shader = ShaderManager::genericSpriteShader;
        this->shader = new ga::Shader("OpenGLLib/Graphics/shaders/spriteShader.glsl");
        this->rect->setShader(this->shader);
    }

    Rect2D::Rect2D(ga::Color color, const float& width, const float& height)
        : rect(new ga::ColorRect(color, width, height))
    {
        if (!ShaderManager::genericColorShader) {
            ShaderManager::genericColorShader = new ga::Shader("OpenGLLib/Graphics/shaders/colorShader.glsl");
        }
        //this->shader = ShaderManager::genericColorShader;
        this->shader = new ga::Shader("OpenGLLib/Graphics/shaders/colorShader.glsl");
        this->rect->setShader(this->shader);
    }

    void Rect2D::setColor(ga::Color color) {
        if (!ShaderManager::genericColorShader) {
            ShaderManager::genericColorShader = new ga::Shader("OpenGLLib/Graphics/shaders/colorShader.glsl");
        }
        //this->shader = ShaderManager::genericColorShader;
        this->shader = new ga::Shader("OpenGLLib/Graphics/shaders/colorShader.glsl");
        this->rect->setShader(this->shader);
    }

    void Rect2D::setColor(const int& r, const int& g, const int& b, const int& a) {
        if (!ShaderManager::genericColorShader) {
            ShaderManager::genericColorShader = new ga::Shader("OpenGLLib/Graphics/shaders/colorShader.glsl");
        }
        //this->shader = ShaderManager::genericColorShader;
        this->shader = new ga::Shader("OpenGLLib/Graphics/shaders/colorShader.glsl");
        this->rect->setShader(this->shader);
        //this->color = {r, g, b, a};
    }
};
