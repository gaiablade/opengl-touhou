#include "ShaderManager.h"

ga::Shader* ShaderManager::genericColorShader = nullptr;
ga::Shader* ShaderManager::genericSpriteShader = nullptr;

namespace ga {
    ShaderManager::ShaderManager(const std::string& shaderList) {
        std::string filename;
        std::ifstream list(shaderList);
        while (list >> filename) {
            this->shaders.insert(std::pair<std::string, ga::Shader*>(filename, new ga::Shader(filename)));
        }
    }

    ShaderManager::~ShaderManager() {
        for (auto& shader : this->shaders) {
            delete shader.second;
        }
    }
};
