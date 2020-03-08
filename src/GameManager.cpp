#include "GameManager.h"

GameManager::GameManager(GLFWwindow* window, float width, float height)
    : window(window), dt(0), width(width), height(height), renderer(width, height)
{
    this->lastTime = std::chrono::high_resolution_clock::now();
}

GameManager::~GameManager() {
}

void GameManager::start() {
    while (!glfwWindowShouldClose(window)) {
        this->updateDt();
        this->updateInput();
        this->player.update(this->dt);
        this->renderer.Clear();
        this->player.draw(&this->renderer);
        glfwSwapBuffers(window);
        glfwPollEvents();
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
}

void GameManager::updateDt() {
    std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = now - lastTime;
    this->dt = duration.count();
    this->lastTime = now;
}
