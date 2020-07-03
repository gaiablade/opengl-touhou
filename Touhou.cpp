#include "Touhou.hpp"

namespace th {
    Game::Game(const int& width, const int& height, const std::string& title)
        : window(width, height, title)
    {
        curr_state.push(new MenuState(width, height));
    }

    Game::~Game() {
        delete curr_state.top();
        curr_state.pop();
    }

    void Game::Run() {
        while (this->window.isOpen()) {
            update();

            window.getRenderer().Clear();

            this->curr_state.top()->render(this->window);

            window.Draw();
            window.Poll();
        }
    }

    void Game::update() {
        curr_state.top()->update(this->window);
        if (curr_state.top()->status == 1) {
            delete curr_state.top();
            curr_state.pop();
            curr_state.push(new DanmakuTest(this->window.getWidth(), this->window.getHeight()));
        }
    }
}