#pragma once
#include <iostream>

#include "Rect.h"
#include "Sprite.h"
#include "ColorRect.h"
#include "ShaderManager.h"

namespace ga {
    class Renderer;

    class Rect2D {
        friend class ga::Renderer;
        public:
            Rect2D();
            Rect2D(ga::Texture* texture);
            Rect2D(ga::Color color, const float& width, const float& height);
            void setColor(ga::Color color);
            void setColor(const int& r, const int& g, const int& b, const int& a = 1.0f);
            inline void setShader(ga::Shader* shader) { this->shader = shader; }
            inline ga::Shader* getShader() const { return this->shader; }
            inline void setPosition(const float& x, const float& y) { this->rect->setPosition(x, y); }
            ga::Rect* rect;
            ga::Shader* shader;
    };
};
