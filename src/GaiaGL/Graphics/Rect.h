/*
 * Rect.h
 * Author: Caleb Geyer
 * Description: Base Rect class with Vertex data. Pure virtual.
 */
#pragma once
#include <iostream>
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayoutData.h"
#include "Shader.h"
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

    /*
     * Rect class:
     * Type: Base, Pure Virtual.
     */
    class Rect {
        protected:
            ga::VertexBuffer* vb;
            std::vector<float> data;
            ga::BufferLayoutData* bld;
            ga::IndexBuffer* ib;
            std::vector<unsigned int> indices;
            ga::VertexArray* va;
            ga::Shader* shader;
            ga::Size2D size;
            ga::Position2D position;
        public:
            Rect();
            virtual ~Rect();

            inline uint32_t getWidth() const { return this->size.width; }
            inline uint32_t getHeight() const { return this->size.height; }
            virtual inline ga::Color getColor() const { return ga::Color{0.0f, 0.0f, 0.0f, 0.0f}; }
            inline ga::IndexBuffer* getIndexBuffer() const { return this->ib; }
            inline ga::Shader* getShader() const { return this->shader; }

            inline void setWidth(const uint32_t& width) { this->size.width = width; }
            inline void setHeight(const uint32_t& height) { this->size.height = height; }
            inline void setPosition(const float& x, const float& y) { this->position.x = x; this->position.y = y; }
            inline void setShader(ga::Shader* shader) { this->shader = shader; }
            virtual inline void setColor(ga::Color color) { return; }

            virtual void Bind() = 0;
            virtual void Unbind() = 0;
    };
};
