#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "Player.h"
#include "Enemy.h"
#include "Laser.h"
#include "OpenGLLib/Graphics.h"

class Player;

class GameManager {
    private:
        ga::ShaderManager shaderManager;
        float width, height;
        GLFWwindow* window;
        Player player;
        Enemy enemy;
        ga::Renderer renderer;
        float elapsedTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
        float dt;
    public:
        GameManager(GLFWwindow* window, float width, float height);
        ~GameManager();
        void start();
        void updateInput() const;
        void updateDt();
};
