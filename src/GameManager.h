#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <list>
#include <chrono>

#include "Player.h"
#include "Enemy.h"
#include "Laser.h"
#include "OpenGLLib/Graphics.h"

const float ENEMY_SPAWN_RATE = 2.0f;

class Player;

class GameManager {
    private:
        ga::ShaderManager shaderManager;
        float width, height;
        GLFWwindow* window;
        Player player;
        std::list<Enemy> enemies;
        ga::Renderer renderer;
        float elapsedTime;
        float lastEnemy;
        std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
        float dt;
    public:
        GameManager(GLFWwindow* window, float width, float height);
        ~GameManager();
        void start();
        void updateInput() const;
        void updateDt();
};
