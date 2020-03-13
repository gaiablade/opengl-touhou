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
            -(float)this->size.width / 2, -(float)this->size.height / 2, 0.0f, 0.0f,
             (float)this->size.width / 2, -(float)this->size.height / 2, 1.0f, 0.0f,
             (float)this->size.width / 2,  (float)this->size.height / 2, 1.0f, 1.0f,
            -(float)this->size.width / 2,  (float)this->size.height / 2, 0.0f, 1.0f
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
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(this->position.x, this->position.y, 0.0f));
        model = glm::rotate(model, glm::radians(this->rotation.angle), glm::vec3(0.0f, 0.0f, 1.0f));
        this->shader->SetUniformMat4f("Model", model);
    }

    void Sprite::Unbind() {
        this->shader->Unbind();
        this->texture->Unbind();
        this->va->Unbind();
        this->ib->Unbind();
    }
};
