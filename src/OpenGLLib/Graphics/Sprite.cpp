#include "Sprite.h"

namespace ga {
    Sprite::Sprite()
        : width(0), height(0), texture(nullptr),
        position({0.0f, 0.0f})
    {
    }

    Sprite::Sprite(uint32_t width, uint32_t height)
        : width(width), height(height), texture(nullptr),
        position({0.0f, 0.0f})
    {
    }

    Sprite::Sprite(Texture* texture)
        : texture(texture),
        position({0.0f, 0.0f})
    {
        this->width = this->texture->getWidth();
        this->height = this->texture->getHeight();
        this->initializeTexture();
    }

    Sprite::~Sprite() {
    }

    void Sprite::initializeTexture() {
        this->data = {
            0.0f,               0.0f,                0.0f, 0.0f,
            (float)this->width, 0.0f,                1.0f, 0.0f,
            (float)this->width, (float)this->height, 1.0f, 1.0f,
            0.0f,               (float)this->height, 0.0f, 1.0f
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
    }

    void Sprite::initializeColor() {
        this->data = {
            0.0f,               0.0f,                0.0f, 0.0f,
            (float)this->width, 0.0f,                1.0f, 0.0f,
            (float)this->width, (float)this->height, 1.0f, 1.0f,
            0.0f,               (float)this->height, 0.0f, 1.0f
        };
        this->vb = new VertexBuffer((const void*)&this->data[0], 16 * sizeof(float));
        this->bld = new BufferLayoutData;
        bld->Insert<float>(2); // pos
        bld->Insert<float>(2); // dummy tex coords
        this->indices = {
            0, 1, 2,
            2, 3, 0
        };
        this->ib = new IndexBuffer((const void*)&this->indices[0], 6);
        this->va = new VertexArray;
        va->AddBuffer(*this->vb, *this->bld);
    }

    void Sprite::Bind() const {
        this->shader->Bind();
        if (this->texture) this->texture->Bind();
        this->va->Bind();
        this->ib->Bind();

        // Calculate Model Matrix:
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(this->position.x, this->position.y, 0.0f));
        this->shader->SetUniformMat4f("Model", model);
    }

    void Sprite::setColor(const float r, const float g, const float b) {
        this->shader->Bind();
        this->color = {r, g, b, 1.0f};
        this->shader->SetUniform4f("u_Color", this->color.r, this->color.g, this->color.b, 1.0f);
        this->initializeColor();
    }
};

