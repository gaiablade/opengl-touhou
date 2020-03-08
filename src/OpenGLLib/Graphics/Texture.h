#pragma once
#include <iostream>
#include <GL/glew.h>

#include "GLCall.h"

#include "stb_image/stb_image.h"

namespace ga {
    class Texture {
        public:
            std::string filename;
        private:
            unsigned int ID;
            unsigned char* data;
            int textureWidth, textureHeight, bytesPerPixel;
        public:
            Texture(const std::string& filename);
            ~Texture();

            void Bind(int slot = 0) const;
            void Unbind() const;
            inline int getWidth() { return this->textureWidth; }
            inline int getHeight() { return this->textureHeight; }
    };
};

using namespace ga;
