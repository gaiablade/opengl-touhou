#pragma once
#include <array>
#include <GaiaGL/Graphics.h>
#include "State.hpp"
#include "Parse.hpp"

namespace th {

    class MenuState : public State {
        public:
        MenuState(int width, int height);
        ~MenuState() = default;
        void render(ga::Window& window) override;
        void update(ga::Window& window) override;
        void updateInput(ga::Window& window);
        private:
        ga::Texture backgroundTexture;
        ga::Sprite background;
        ga::Texture startTexture;
        ga::Sprite start;
        ga::ColorRect underline;
        std::array<int, 4> buttonStates;
    };

}