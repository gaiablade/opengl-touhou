#pragma once
#include "pch.h"
#include <GaiaGL/Graphics.h>
#include <GaiaGL/System.h>

namespace th {

    enum class POSITION {
        NONE = 0, OWNER, CUSTOM
    };

    enum class FORMATION {
        NONE = 0, RADIAL, WHIRLPOOL
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
        ga::Position2D<float> position;
        union {
            ga::Position2D<float> center;
        };
        union {
            ga::Vector2<float> direction;
            float speed;
        };
        ga::Rotation2D rotation;
        ga::Collider coll;
        bool OOB;
        int lifetime = 0;
    };

    class Spell {
        public:
        Spell(SpellInfo& si, const ga::Position2D<float>& position, const int& rotation = 0);
        void update();
        void render(ga::Window& window);

        int formation;
        std::list<Bullet> bullets;
        ga::Sprite* sprite;
        ga::Position2D<float> position;
        double lifetime;
        bool empty;
    };

}