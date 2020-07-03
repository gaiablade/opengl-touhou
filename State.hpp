#pragma once
#include <iostream>
#include <GaiaGL/Graphics.h>
#include <GaiaGL/Input.h>

namespace th {

    class State {
        public:
        State();
        virtual ~State();
        virtual void render(ga::Window& window) = 0;
        virtual void update(ga::Window& window) = 0;
        int status;

        protected:
    };

}