#pragma once
#include <GaiaGL/Graphics.h>
#include <stack>
#include "State.hpp"
#include "Menu.hpp"
#include "Parse.hpp"
#include "DanmakuTest.hpp"

namespace th {
    class Game {
        public:
        Game() = delete;
        Game(const int& width, const int& height, const std::string& title);
        ~Game();
        void Run();
        void update();

        //private:
        ga::Window window;
        std::stack<State*> curr_state;
    };
}