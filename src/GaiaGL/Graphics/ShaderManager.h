/*
 * ShaderManager.h
 * Author: Caleb Geyer
 * Description: Loads global shaders.
 */
#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "Shader.h"

namespace ga {
    /*
     * ShaderManager Class: Loads global shaders.
     * Type: Standalone.
     */
    class ShaderManager {
        public:
            ShaderManager(const std::string& shaderList);
            ~ShaderManager();
            std::unordered_map<std::string, ga::Shader*> shaders;
            static ga::Shader* genericColorShader, *genericSpriteShader;
    };
};
