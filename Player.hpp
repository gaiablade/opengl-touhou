#pragma once

#include <GaiaGL/Graphics.hpp>
#include <GaiaGL/System.hpp>

namespace th {
    class Player {
        public:
        ga::Collider coll;
        ga::Sprite* sprite;
        int frame;
        ga::Position2D<float> position;

        Player();
        void update();
        void render(ga::Window& window);
    };
}