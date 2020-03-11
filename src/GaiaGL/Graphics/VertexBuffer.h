/*
 * VertexBuffer.h
 * Author: Caleb Geyer
 * Description: Vertex Data Object.
 */
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLCall.h"

namespace ga {
    /*
     * VertexBuffer Class: Vertex Data Array.
     * Type: Standalone.
     */
    class VertexBuffer {
        private:
            unsigned int ID;
        public:
            VertexBuffer(const void* data, unsigned int sizeInBytes);
            ~VertexBuffer();

            void Bind() const;
            void Unbind() const;
    };
};
