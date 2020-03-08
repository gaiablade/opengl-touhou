#pragma once
#include "Texture.h"

namespace ga {
    class Material {
        public:
            Material() {}
            Material(const std::string& textureFile);
            ~Material();
            void Bind() const;
            ga::Texture* texture;
    };
};

using namespace ga;
