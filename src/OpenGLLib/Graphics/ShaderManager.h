#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "Shader.h"

namespace ga {
    class ShaderManager {
        public:
            ShaderManager(const std::string& shaderList);
            ~ShaderManager();
            std::unordered_map<std::string, ga::Shader*> shaders;
            static ga::Shader* genericColorShader, *genericSpriteShader;
    };
};
