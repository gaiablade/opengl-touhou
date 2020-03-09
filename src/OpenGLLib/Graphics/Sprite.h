#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayoutData.h"
#include "Texture.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "GLCall.h"

#include "stb_image/stb_image.h"

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

    class Sprite {
        public:
            Sprite();
            Sprite(uint32_t width, uint32_t height);
            Sprite(ga::Texture* texture);
            ~Sprite();
            void initializeTexture();
            void initializeColor();
            void Bind() const;
            void setColor(const float r, const float g, const float b);
            inline ga::Texture* getTexture() const { return this->texture; }
            inline uint32_t getWidth() const { return this->width; }
            inline uint32_t getHeight() const { return this->height; }
            inline Shader* getShader() const { return this->shader; }
            inline ga::IndexBuffer* getIndexBuffer() const { return this->ib; }
            inline void setWidth(const uint32_t& width) { this->width = width; }
            inline void setHeight(const uint32_t& height) { this->height = height; }
            inline void setShader(Shader* shader) { this->shader = shader; }
            inline void setPosition(float x, float y) { this->position = {x, y}; }
        private:
            uint32_t width, height;
            ga::Position2D position;
            ga::Color color;

            // OpenGL:
            ga::Texture* texture;
            ga::VertexBuffer* vb;
            ga::BufferLayoutData* bld;
            std::vector<float> data;
            std::vector<unsigned int> indices;
            ga::IndexBuffer* ib;
            ga::VertexArray* va;
            ga::Shader* shader;
    };
};
