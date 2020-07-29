#pragma once
#include <GaiaGL/Graphics.hpp>
#include <stack>
#include "State.hpp"
#include "Menu.hpp"
//#include "DanmakuTest.hpp"
#include "EditSpell.hpp"

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