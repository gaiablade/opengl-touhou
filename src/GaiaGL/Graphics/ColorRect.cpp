#include "ColorRect.h"

namespace ga {
    ColorRect::ColorRect()
    {
    }

    ColorRect::ColorRect(ga::Color color, const float& width, const float& height)
        : color(color)
    {
        this->size.width = width;
        this->size.height = height;
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
        this->shader = new ga::Shader("GaiaGL/Graphics/shaders/colorShader.glsl");
    }

    void ColorRect::Bind() {
        this->shader->Bind();
        this->va->Bind();
        this->ib->Bind();

        // Calculate Model Matrix:
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(this->position.x, this->position.y, 0.0f));
        model = glm::rotate(model, glm::radians(this->rotation.angle), glm::vec3(0.0f, 0.0f, 1.0f));
        this->shader->SetUniformMat4f("Model", model);
        this->shader->SetUniform4f("u_Color", this->color.r, this->color.g, this->color.b, this->color.a);
    }

    void ColorRect::Unbind() {
        this->shader->Unbind();
        this->va->Unbind();
        this->ib->Unbind();
    }
};
