#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <list>
#include <chrono>

#include "Player.h"
#include "Enemy.h"
#include "Laser.h"
#include "GaiaGL/Graphics.h"

const float ENEMY_SPAWN_RATE = 1.0f;
const float STAT_BAR_WIDTH = 230.0f;

class Player;

class GameManager {
    private:
        ga::ShaderManager shaderManager;
        ga::Texture bgTexture;
        ga::Rect2D background;
        ga::Rect2D statBar;
        float width, height;
        GLFWwindow* window;
        Player player;
        std::list<Enemy*> enemies;
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
