#include "Menu.hpp"

namespace th {
    MenuState::MenuState(int width, int height)
        : backgroundTexture("assets/images/menu.png"), background(&backgroundTexture, width, height),
            startTexture("assets/images/Start_Option.png"), start(&startTexture),
            underline(ga::Color(1.0f, 0.0f, 0.0f, 1.0f), start.getWidth(), 10.0f)
    {
        this->status = 0;
        this->background.setPosition(ga::Position2D<float>(width/2, height/2));
        this->start.setPosition(width - start.getWidth()/2 - 30.0f, height/2);
        this->underline.setPosition(ga::Position2D<float>(start.getPosition().x, start.getPosition().y + 30.0f));
        this->buttonStates = {
            0, 0, 0, 0
        };
    }

    void MenuState::render(ga::Window& window) {
        window.getRenderer().Draw(this->background);
        window.getRenderer().Draw(this->start);
        window.getRenderer().Draw(this->underline);
    }

    void MenuState::update(ga::Window& window) {
        updateInput(window);
        if (buttonStates[2]) {
            this->status = 1;
        }
    }

    void MenuState::updateInput(ga::Window& window) {
        // Input
        if (ga::Input::IsKeyPressed(GA_KEY_UP, window)) {
            buttonStates[0] += 1;
        }
        else {
            buttonStates[0] = 0;
        }
        if (ga::Input::IsKeyPressed(GA_KEY_DOWN, window)) {
            buttonStates[1] += 1;
        }
        else {
            buttonStates[1] = 0;
        }
        if (ga::Input::IsKeyPressed(GA_KEY_ENTER, window)) {
            buttonStates[2] += 1;
        }
        else {
            buttonStates[2] = 0;
        }
        if (ga::Input::IsKeyPressed(GA_KEY_ESCAPE, window)) {
            buttonStates[3] += 1;
        }
        else {
            buttonStates[3] = 0;
        }
    }

}