/*
 * Rect2D.h
 * Author: Caleb Geyer
 * Description: Generic drawable rectangle. Can either be filled with a texture
 *    or color.
 */
#pragma once
#include <iostream>

#include "Rect.h"
#include "Sprite.h"
#include "ColorRect.h"

namespace ga {
    /*
     * Rect2D Class: Generic drawable rectangle.
     * Type: Standalone.
     */
    class Rect2D {
        public:
            Rect2D();
            Rect2D(ga::Texture* texture);
            Rect2D(ga::Color color, const float& width, const float& height);
            ~Rect2D();
            void setColor(ga::Color color);
            void setColor(const int& r, const int& g, const int& b, const int& a = 1.0f);
            inline void setShader(ga::Shader* shader) { this->shader = shader; }
            inline ga::Shader* getShader() const { return this->shader; }
            inline void setPosition(const float& x, const float& y) { this->rect->setPosition(x, y); }
            inline void setRotation(ga::Rotation2D rotation) { this->rect->setRotation(rotation); }
            inline void setScale(ga::Scale2D scale) { this->rect->setScale(scale); }
            ga::Rect* rect;
            ga::Shader* shader;
    };
};
