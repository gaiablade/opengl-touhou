#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "GLCall.h"
#include "Texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

// Draw a triangle to a window:
int main() {
    // Window Creation:
    sf::RenderWindow window;
    sf::Event event;
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.sRgbCapable = false;
    window.create(sf::VideoMode(960, 540), "BABYYYYY", sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);


    // Initialize glew:
    glewInit();

    // Triangle vertices:
    float positions[] = {
        100.0f, 100.0f, 0.0f, 0.0f, // Bottom left
        400.0f, 100.0f, 1.0f, 0.0f, // Bottom right
        400.0f, 400.0f, 1.0f, 1.0f, // Top right
        100.0f, 400.0f, 0.0f, 1.0f  // Top left
    };

    float vert2[] = {
        100.0f, 100.0f, 0.0f, 0.0f, // Bottom left
        400.0f, 100.0f, 1.0f, 0.0f, // Bottom right
        400.0f, 400.0f, 1.0f, 1.0f, // Top right
        100.0f, 400.0f, 0.0f, 1.0f  // Top left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Create Vertex Array:
    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexArray va2;
    VertexBuffer vb2(vert2, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    layout.Push(GL_FLOAT, 2);
    va.AddBuffer(vb, layout);
    va2.AddBuffer(vb2, layout);

    // Index Buffer:
    IndexBuffer ib(indices, 2 * 3);

    glm::mat4 proj  = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view  = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 0, 0));

    glm::mat4 mvp = proj * view * model;
//    glm::mat4 mvp = proj;

    Shader shader("res/shaders/Basic.glsl");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    shader.SetUniformMat4f("u_MVP", mvp);

    Texture texture("res/textures/link.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    // Unbind everything:
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.05f;

    while (window.isOpen()) {

        // Bind everything we need:
        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        renderer.Clear();
        renderer.Draw(va, ib, shader);

        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", mvp);
        shader.SetUniform1i("u_Texture", 0);

        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.display();
    }
    return 0;
}
