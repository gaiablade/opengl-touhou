#include "Touhou.hpp"

namespace th {
    // Default constructor = delete

    // EDIT THIS CONSTRUCTOR TO CHANGE DEFAULT GAME STATE
    Game::Game(const int& width, const int& height, const std::string& title)
        : window(width, height, title)
    {
        // In final production, initialize to loading screen, intro, or something more appropriate
        curr_state.emplace(new MenuState(width, height)); // Initialize to menu state
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

        // IDEA: Create a table of states and their possible next state(s) and use this to determine
        //       which state to use next
        if (curr_state.top()->status == 1) {
            delete curr_state.top();
            curr_state.pop();
            curr_state.emplace(new DanmakuTest(this->window.getWidth(), this->window.getHeight(), &this->window));
        }
    }
}