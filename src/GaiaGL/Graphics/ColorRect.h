/*
 * ColorRect.h
 * Author: Caleb Geyer
 * Description: Implements a simple colored rectangle.
 */
#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "Rect.h"
#include "ShaderManager.h"

namespace ga {
    /*
     * ColorRect Class: Colored rectangle.
     * Type: Child.
     */
    class ColorRect : public ga::Rect {
        public:
            ColorRect();
            ColorRect(ga::Color color, const float& width, const float& height);
            virtual void Bind();
            virtual void Unbind();
            inline ga::IndexBuffer* getIndexBuffer() const { return this->ib; }
            inline void setShader(Shader* shader) { this->shader = shader; }
            inline Shader* getShader() const { return this->shader; }
            inline ga::Color getColor() const { return this->color; }
            inline void setColor(ga::Color color) { this->color = color; }
        private:
            ga::Color color;
    };
};
