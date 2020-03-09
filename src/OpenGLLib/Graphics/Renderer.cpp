#include "Renderer.h"

namespace ga {
    void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
        va.Bind();
        ib.Bind();
        shader.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0));
        shader.Unbind();
    }

    void Renderer::Draw(Model& model, Shader& shader) {
        std::vector<Mesh>* meshes = model.GetMeshes();
        shader.Bind();
        for (auto& mesh : *meshes) {
            mesh.Bind();
            GLCall(glDrawElements(GL_TRIANGLES, mesh.ib->getCount(), GL_UNSIGNED_INT, 0));
        }
    }

    void Renderer::Draw(ga::Rect2D& rect2d) {
        rect2d.rect->Bind();
        rect2d.getShader()->SetUniformMat4f("Projection", glm::ortho(0.0f, this->width, 0.0f, this->height, -1.0f, 1.0f));
        GLCall(glDrawElements(GL_TRIANGLES, rect2d.rect->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0));
    }

    void Renderer::Draw(ga::Sprite& sprite) {
        sprite.Bind();
        sprite.getShader()->SetUniformMat4f("Projection", glm::ortho(0.0f, this->width, 0.0f, this->height, -1.0f, 1.0f));
        sprite.getShader()->SetUniform1i("u_Texture", 0);
        GLCall(glDrawElements(GL_TRIANGLES, sprite.getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0));
    }

    void Renderer::Draw(ga::ColorRect& sprite) {
    }

    void Renderer::Clear() const {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
    }
};
