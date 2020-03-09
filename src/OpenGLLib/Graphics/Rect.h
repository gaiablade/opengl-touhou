#pragma once
#include <iostream>
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayoutData.h"
#include "Texture.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "GLCall.h"

namespace ga {
    struct Position2D {
        float x, y;
    };

    struct Velocity2D {
        float x, y;
    };

    struct Size2D {
        float width, height;
    };

    struct Color {
        float r, g, b, a;
    };

    class Rect {
        protected:
            // VertexBuffer and its data:
            ga::VertexBuffer* vb;
            std::vector<float> data;
            // Buffer Layout:
            ga::BufferLayoutData* bld;
            // Index Buffer:
            ga::IndexBuffer* ib;
            std::vector<unsigned int> indices;
            // Vertex Array:
            ga::VertexArray* va;
            // Shader:
            ga::Shader* shader;
            // Size:
            ga::Size2D size;
            // Position:
            ga::Position2D position;
        public:
            Rect();
            ~Rect();
            inline uint32_t getWidth() const { return this->size.width; }
            inline uint32_t getHeight() const { return this->size.height; }
            inline void setWidth(const uint32_t& width) { this->size.width = width; }
            inline void setHeight(const uint32_t& height) { this->size.height = height; }
            inline void setPosition(const float& x, const float& y) { this->position.x = x; this->position.y = y; }
            inline void setShader(ga::Shader* shader) { this->shader = shader; }
            inline ga::IndexBuffer* getIndexBuffer() const { return this->ib; }
            virtual void Bind() const = 0;
    };
};
