/*
 * Renderer.h
 * Author: Caleb Geyer
 * Description: Renderer that draws objects to window.
 */
#pragma once
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Model.h"
#include "Rect2D.h"
#include "GLCall.h"

namespace ga {
    /*
     * Renderer Class: Draws objects to the screen.
     * Type: Standalone.
     */
    class Renderer {
        private:
            float width, height;
        public:
            Renderer(float screenWidth, float screenHeight) : width(screenWidth), height(screenHeight) {}
            void Draw(const ga::VertexArray& va, const ga::IndexBuffer& ib, const ga::Shader& shader) const;
            void Draw(ga::Model& model, Shader& shader);
            void Draw(ga::Rect2D& rect2d);
            void Draw(ga::Rect& rect);
            void Clear() const;
    };
};
