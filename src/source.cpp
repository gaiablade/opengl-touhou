#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <cmath>

#include "GaiaGL/Graphics.h"
#include "GaiaGL/Input.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "GLCall.h"

#include "GameManager.h"

struct screenDimensions {
    static const int width = 800, height = 600;
};

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(screenDimensions::width, screenDimensions::height, "Game", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    ga::Renderer renderer(screenDimensions::width, screenDimensions::height);

    GameManager gm(window, screenDimensions::width, screenDimensions::height);
    gm.start();

    glfwTerminate();
    return 0;
}
