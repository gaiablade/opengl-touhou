#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayoutData.h"
#include "ModelLoader.h"
#include "Texture.h"
#include "Material.h"

namespace ga {
    class Mesh {
        public:
            Mesh();
            ~Mesh();
            void Bind() const;
            void Unbind() const;
            void SetMaterial(ga::Material* material);
            void SetVertexBuffer(ga::VertexBuffer* vb);
            void SetIndexBuffer(ga::IndexBuffer* ib);
            void Delete();
            void ConstructVertexArray();
            ga::IndexBuffer* ib;
        private:
            ga::VertexBuffer* vb;
            ga::VertexArray* va;
            ga::BufferLayoutData* bld;
            ga::Material* material;
    };
};

using namespace ga;
