#pragma once
#include "pch.h"
#include <GaiaGL/ImGui.hpp>
#include <filesystem>
#include "State.hpp"
#include "Enemy.hpp"
#include "Spell.hpp"
#include "Player.hpp"

namespace fs = std::filesystem;

namespace th {
    class EditSpell : public State {
        public:
        EditSpell(int width, int height, ga::Window* window);
        ~EditSpell();
        void render(ga::Window& window) override;
        void update(ga::Window& window) override;

        private:
        ga::Window* window;
        ga::ImGuiInst imgui;
        std::list<Spell> spells;
        C_SpellParams csp;
        D_SpellParams dsp;
        ga::Texture* texture;
        ga::Sprite* sprite;
        ga::Texture* playerTex;
        ga::Sprite* playerSprite;
        Player player;
        int frame;
    };
}