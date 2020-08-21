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
        ~EditSpell() override;
        void render(ga::Window& window) override;
        void update(ga::Window& window) override;
        void createSpell();
        void initCSPS();

        private:
        ga::Window* window;
        ga::ImGuiInst imgui;
        std::list<Spell> spells;
        //C_SpellParams csp;
        std::vector<C_SpellParams> csps;
        D_SpellParams dsp;
        ga::Texture* texture;
        ga::Sprite* sprite;
        ga::Texture* playerTex;
        ga::Sprite* playerSprite;
        Player player;
        int frame;
        int currentSpellSelected;
        std::array<const char*, 7> formationNames{};

        bool b_CollisionDetected{false};
    };
}
