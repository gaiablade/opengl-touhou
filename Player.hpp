#pragma once

#include <GaiaGL/Graphics.h>
#include <GaiaGL/System.h>

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