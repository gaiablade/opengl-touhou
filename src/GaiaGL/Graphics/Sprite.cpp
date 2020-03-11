#include "Sprite.h"

namespace ga {
    Sprite::Sprite()
        : texture(nullptr)
    {
    }

    Sprite::Sprite(Texture* texture)
        : texture(texture)
    {
        this->size.width = this->texture->getWidth();
        this->size.height = this->texture->getHeight();
        this->data = {
            0.0f,                    0.0f,                     0.0f, 0.0f,
            (float)this->size.width, 0.0f,                     1.0f, 0.0f,
            (float)this->size.width, (float)this->size.height, 1.0f, 1.0f,
            0.0f,                    (float)this->size.height, 0.0f, 1.0f
        };
        this->vb = new VertexBuffer((const void*)&this->data[0], 16 * sizeof(float));
        this->bld = new BufferLayoutData;
        bld->Insert<float>(2);
        bld->Insert<float>(2);
        this->indices = {
            0, 1, 2,
            2, 3, 0
        };
        this->ib = new IndexBuffer((const void*)&this->indices[0], 6);
        this->va = new VertexArray;
        va->AddBuffer(*this->vb, *this->bld);
        this->shader = new ga::Shader("GaiaGL/Graphics/shaders/spriteShader.glsl");
    }

    void Sprite::Bind() {
        this->shader->Bind();
        this->texture->Bind();
        this->va->Bind();
        this->ib->Bind();

        // Calculate Model Matrix:
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(this->position.x, this->position.y, 0.0f));
        this->shader->SetUniformMat4f("Model", model);
        this->shader->SetUniform1i("u_Texture", 0);
    }

    void Sprite::Unbind() {
        this->shader->Unbind();
        this->texture->Unbind();
        this->va->Unbind();
        this->ib->Unbind();
    }
};
