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

ga::Vector2<float> homing_dir(const ga::v2f& spawn, const ga::v2f& target);

namespace th {
    enum class FORM {
        NONE = 0,
        // Simple Spell formations
        RAD, // radial
        WHIRL, // whirlpool
        HOMING,

        // More complex formations
        RUMIA_HOMING_LINE_1,
        RUMIA_SEMICIRCLE_2,
        RUMIA_LASER_3,
    };

    class Bullet {
        public:
        ga::v2f v_Position;
        ga::v2f v_Direction;
        union {
            ga::v2f v_Center;
            ga::v2f v_Target;
        };
        int n_Duration{};
        float f_Rotation{};
        float f_Speed{};
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

        template <FORM form>
        void initSpell(const C_SpellParams& csp, const D_SpellParams& dsp);

        void render(ga::Window& window);

        void update();

        // Specialized update function
        template <FORM form>
        void updateSpell();

        int n_Formation;
        int n_NumBullets;
        int n_Lifetime;
        int n_Duration;
        float f_Speed;
        bool b_Empty{false};
        ga::v2f v_Position;
        std::list<Bullet> l_Bullets;
        ga::Window* windowPointer;
        union {
            ga::Sprite* sprite;
            ga::ColorRect* rect;
        };
    };
}
