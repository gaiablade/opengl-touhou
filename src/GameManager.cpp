#include "GameManager.h"

GameManager::GameManager(GLFWwindow* window, float width, float height)
    : window(window), dt(0), width(width), height(height), renderer(width, height),
    shaderManager("shaderList.txt"), player(this->shaderManager.shaders["res/shaders/spriteShader.glsl"]),
    bgTexture("res/textures/space_800x600.png"),
    background(&bgTexture),
    statBar(ga::Color{0.7098f, 0.1529f, 0.0f, 1.0f}, STAT_BAR_WIDTH, 600),
    lastEnemy(ENEMY_SPAWN_RATE)
{
    this->lastTime = std::chrono::high_resolution_clock::now();
    this->statBar.setPosition(800.0f - STAT_BAR_WIDTH, 0.0f);
}

GameManager::~GameManager() {
}

void GameManager::start() {
    while (!glfwWindowShouldClose(window)) {
        this->updateDt();
        this->updateInput();
        this->lastEnemy += dt;
        if (this->lastEnemy > ENEMY_SPAWN_RATE) {
            //this->enemies.push_back(Enemy(this->shaderManager.shaders["res/shaders/spriteShader.glsl"]));
            this->lastEnemy = 0.0f;
        }
        for (auto& enemy : this->enemies) {
            enemy.update(dt);
        }
        this->player.update(this->dt);
        this->renderer.Clear();
        renderer.Draw(this->background);
        this->player.draw(&this->renderer);
        for (auto& enemy : this->enemies) {
            enemy.draw(&this->renderer);
        }
        renderer.Draw(this->statBar);
        glfwSwapBuffers(window);
        glfwPollEvents();
        dt = 0.0f;
    }
}

void GameManager::updateInput() const {
    if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        this->player.inputHandler.callback(1u);
    }
    else {
        this->player.inputHandler.callback(5u);
    }
    if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        this->player.inputHandler.callback(2u);
    }
    else {
        this->player.inputHandler.callback(6u);
    }
    if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS) {
        this->player.inputHandler.callback(3u);
    }
    else {
        this->player.inputHandler.callback(7u);
    }
    if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        this->player.inputHandler.callback(4u);
    }
    else {
        this->player.inputHandler.callback(8u);
    }
    if (glfwGetKey(this->window, GLFW_KEY_Z) == GLFW_PRESS) {
        this->player.inputHandler.callback(9u);
    }
    else {
        this->player.inputHandler.callback(10u);
    }
}

void GameManager::updateDt() {
    std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = now - lastTime;
    this->dt = duration.count();
    this->lastTime = now;
}
