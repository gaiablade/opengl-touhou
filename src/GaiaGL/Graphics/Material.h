/*
 * Material.h
 * Author: Caleb Geyer
 * Description: Model material, contains attributes such as texture.
 */
#pragma once
#include "Texture.h"

namespace ga {
    /*
     * Material Class: Mesh/Model attributes.
     * Type: Standalone.
     */
    class Material {
        public:
            Material() {}
            Material(const std::string& textureFile);
            ~Material();
            void Bind() const;
            ga::Texture* texture;
    };
};
