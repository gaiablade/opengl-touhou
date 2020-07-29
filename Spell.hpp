#pragma once
#include "pch.h"
#include <GaiaGL/Graphics.hpp>
#include <GaiaGL/System.hpp>

/*
 * Constructing a spell can be broken down into two sets of parameters:
 * 1. Static and constant parameters
 * 2. Dynamic parameters
 * ============================================================================
 * Static Parameters are things that will be the same for every copy of a
 * particular spell, such as the formation, speed, number of bullets, etc.
 * 
 * Dynamic Parameters are things that will be potentially different for each
 * copy of a spell, such as the target (player) position
 * ============================================================================
 */

/*
namespace th {

    enum class POSITION {
        NONE = 0, OWNER, CUSTOM
    };

    enum class FORMATION {
        NONE = 0, RADIAL, WHIRLPOOL, HOMING, RAD2
    };

    struct SpellInfo {
        std::string name;
        int startingPosition;
        ga::Position2D<int> position = { 0, 0 };
        int formation;
        int numBullets;
        float speed;
        ga::Sprite* sprite;
        ga::Position2D<float> playerPosition;
    };

    struct Bullet {
        ga::Position2D<float> position;
        union {
            ga::Position2D<float> center; // important for whirlpool
            ga::Position2D<float> target; // important for homing
        };
        union {
            ga::Vector2<float> direction;
        };
        float speed;
        ga::Rotation2D rotation;
        ga::Collider coll;
        bool OOB;
        int lifetime = 0;

        // Movement functions
        void mov_radial();
        void mov_whirlpool();
        void mov_homing();
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
*/

namespace th {
    enum class FORM {
        NONE = 0,
        // Simple Spell formations
        RAD, // radial
        WHIRL, // whirlpool
        HOMING,

        // More complex formations
    };

    class Bullet {
        public:
        ga::v2f v_Position;
        ga::v2f v_Direction;
        union {
            ga::v2f v_Center;
            ga::v2f v_Target;
        };
        int n_Duration;
        float f_Rotation;
        float f_Speed;
        ga::Collider c_Collider;

        // Static
        int n_Lifetime = 0;

        void Move_Radial();
        void Move_Whirlpool();
        void Move_Homing();
    };

    struct C_SpellParams {
        int n_Formation;
        int n_NumBullets;
        int n_Duration;
        float f_Speed;
        ga::Sprite* sprite;
    };

    struct D_SpellParams {
        ga::v2f v_SpellPosition;
        ga::v2f v_PlayerPosition;
    };

    class Spell {
        public:
        Spell() =delete;
        Spell(const C_SpellParams& csp, const D_SpellParams& dsp, ga::Window* windowPointer);

        void initRadial(const C_SpellParams& csp, const D_SpellParams& dsp);
        void initWhirlpool(const C_SpellParams& csp, const D_SpellParams& dsp);
        void initHoming(const C_SpellParams& csp, const D_SpellParams& dsp);

        void render(ga::Window& window);
        void update();

        int n_Formation;
        int n_NumBullets;
        int n_Lifetime;
        int n_Duration;
        float f_Speed;
        bool b_Empty;
        ga::v2f v_Position;
        std::list<Bullet> l_Bullets;
        ga::Window* windowPointer;
        ga::Sprite* sprite;
    };
}