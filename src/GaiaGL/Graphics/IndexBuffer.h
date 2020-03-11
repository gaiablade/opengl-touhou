/*
 * IndexBuffer.h
 * Author: Caleb Geyer
 * Description: Represents a collection of vertex indices to be drawn in a call.
 */
#pragma once
#include <GL/glew.h>
#include "GLCall.h"

namespace ga {
    /*
     * IndexBuffer Class: Collection of vertex indices.
     * Type: Standalone.
     */
    class IndexBuffer {
        private:
            unsigned int ID;
            unsigned int indexCount;
        public:
            IndexBuffer(const void* data, unsigned int count);
            ~IndexBuffer();

            void Bind() const;
            void Unbind() const;

            inline unsigned int getCount() const { return this->indexCount; }
    };
};
