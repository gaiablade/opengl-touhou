#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <GaiaGL/Graphics.h>
#include <GaiaGL/System.h>

namespace th {

    enum class POSITION {
        NONE = 0, OWNER, CUSTOM
    };

    enum class FORMATION {
        NONE = 0, RADIAL
    };

    struct SpellInfo {
        std::string name;
        int startingPosition;
        ga::Position2D<int> position = { 0, 0 };
        int formation;
        int numBullets;
        float speed;
        ga::Sprite* sprite;
    };

    struct Bullet {
        ga::Vector2<float> direction;
        ga::Position2D<float> position;
        void update() {
            this->position.x += direction.x;
            this->position.y += direction.y;
        }
    };

    class Spell {
        public:
        Spell(ga::Sprite* sprite);
        Spell(SpellInfo& si, const ga::Position2D<float>& position);
        void update();
        void render(ga::Window& window);

        std::vector<Bullet> bullets;
        ga::Sprite* sprite;
        double lifetime;
    };

}