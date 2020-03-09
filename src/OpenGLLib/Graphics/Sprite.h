#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "Rect.h"
#include "ShaderManager.h"

#include "stb_image/stb_image.h"

namespace ga {
    class Sprite : public Rect {
        public:
            Sprite();
            Sprite(ga::Texture* texture);
            ~Sprite();
            void Bind() const;
            inline ga::Texture* getTexture() const { return this->texture; }
            inline Shader* getShader() const { return this->shader; }
            inline ga::IndexBuffer* getIndexBuffer() const { return this->ib; }
            inline void setShader(Shader* shader) { this->shader = shader; }
        private:
            // Sprite has a texture, ColorRect does not:
            ga::Texture* texture;
    };
};
