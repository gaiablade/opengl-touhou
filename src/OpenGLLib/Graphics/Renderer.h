#pragma once
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Model.h"
#include "Sprite.h"
#include "GLCall.h"

namespace ga {
    class Renderer {
        private:
            float width, height;
        public:
            Renderer(float screenWidth, float screenHeight) : width(screenWidth), height(screenHeight) {}
            void Draw(const ga::VertexArray& va, const ga::IndexBuffer& ib, const ga::Shader& shader) const;
            void Draw(ga::Model& model, Shader& shader);
            void Draw(ga::Sprite& sprite);
            void Clear() const;
    };
};

using namespace ga;