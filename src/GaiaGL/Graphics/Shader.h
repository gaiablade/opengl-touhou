/*
 * Shader.h
 * Author: Caleb Geyer
 * Description: Program that runs on the GPU.
 */
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLCall.h"

namespace ga {
    enum class ShaderType {
        NONE = -1, Vertex = 0, Fragment = 1
    };

    /*
     * ShaderData Struct: Components of a single shader.
     * Type: Standalone.
     */
    struct ShaderData {
        std::string VertexShader;
        std::string FragmentShader;
    };

    /*
     * Shader Class: Program that runs on the GPU.
     * Type: Standalone.
     */
    class Shader {
        private:
            unsigned int ID;
            std::map<std::string, int> uniforms;

            ShaderData ReadShader(const std::string& filename);
            unsigned int CompileShader(unsigned int type, const std::string& src);
            unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
        public:
            Shader(const std::string& filename);
            ~Shader();

            int GetUniformLocation(const std::string& name);
            void SetUniform1i(const std::string& name, int i);
            void SetUniform1f(const std::string& name, float f);
            void SetUniform3f(const std::string& name, float f0, float f1, float f2);
            void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
            void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

            void Bind() const;
            void Unbind() const;
    };
};
