#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "Rect.h"
#include "ShaderManager.h"

namespace ga {
    class ColorRect : public Rect {
        public:
            ColorRect();
            ColorRect(ga::Color& color, const float& width, const float& height);
            ~ColorRect();
            void Bind() const;
            inline Shader* getShader() const { return this->shader; }
            inline ga::IndexBuffer* getIndexBuffer() const { return this->ib; }
            inline void setShader(Shader* shader) { this->shader = shader; }
        private:
            ga::Color color;
    };
};
