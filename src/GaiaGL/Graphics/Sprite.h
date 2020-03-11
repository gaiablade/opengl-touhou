/*
 * Sprite.h
 * Author: Caleb Geyer
 * Description: Textured Rectangle.
 */
#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "Rect.h"
#include "ShaderManager.h"
#include "Texture.h"

#include "stb_image/stb_image.h"

namespace ga {
    /*
     * Sprite Class: Textured Rectangle.
     * Type: Child.
     */
    class Sprite : public Rect {
        public:
            Sprite();
            Sprite(ga::Texture* texture);
            virtual void Bind();
            virtual void Unbind();
            inline ga::Texture* getTexture() const { return this->texture; }
            inline Shader* getShader() const { return this->shader; }
            inline ga::IndexBuffer* getIndexBuffer() const { return this->ib; }
            inline void setShader(Shader* shader) { this->shader = shader; }
        private:
            // Sprite has a texture, ColorRect does not:
            ga::Texture* texture;
    };
};
