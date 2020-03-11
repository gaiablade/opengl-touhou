/*
 * ModelLoader.h
 * Author: Caleb Geyer
 * Description: Parses .obj model file as well as materials and texture
 *  references.
 */
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Model.h"
#include "Mesh.h"
#include "Material.h"

namespace ga {
    class Model;

    enum class FileType {
        OBJ
    };

    /*
     * ModelLoader Class: Parses .obj files.
     * Type: Standalone, static.
     */
    class ModelLoader {
        public:
            static bool LoadModel(const std::string& modelFile, int filetype, Model* model);
    };
};
