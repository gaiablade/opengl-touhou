#include "EditSpell.hpp"

int curr_item = 1;
const char* itemNames[] = { "None", "Radial", "Whirlpool", "Homing" };

namespace th {
    EditSpell::EditSpell(int width, int height, ga::Window* window)
        : window(window), imgui(*window), playerTex(new ga::Texture("assets/images/marisa.png")), playerSprite(new ga::Sprite(playerTex)), frame(0)
    {
        texture = new ga::Texture("assets/images/red_arrow.png");
        sprite = new ga::Sprite(texture);

        // Player
        this->player.sprite = this->playerSprite;
        this->player.position = { 450.f, 500.f };

        this->csp = { .n_Formation = static_cast<int>(FORM::RAD), .n_NumBullets = 4, .n_Duration = 60, .f_Speed = 3.f, .sprite = this->sprite };
        this->dsp = { .v_SpellPosition = { window->getWidth() / 2, window->getHeight() / 2 }, .v_PlayerPosition = { player.position.x, player.position.y } };
    }

    EditSpell::~EditSpell()
    {
        delete this->sprite;
        delete this->texture;
    }

    void EditSpell::render(ga::Window& window)
    {
        std::for_each(spells.begin(), spells.end(), [&](Spell& spell) {
            spell.render(window);
        });
        this->player.render(window);
        imgui.NewFrame();
        imgui.Begin("Edit Spell");
        ImGui::SliderFloat("Speed", &csp.f_Speed, 1, 30);
        ImGui::SliderInt("NumBullets", &csp.n_NumBullets, 1, 100);
        ImGui::SliderInt("Frame Lifetime", &csp.n_Duration, 1, 800);
        ImGui::ListBox("Option List", &csp.n_Formation, itemNames, 4);
        ImGui::SliderFloat("PlayerX", &player.position.x, 0.f, 800.f);
        imgui.End();
        imgui.Render();
    }

    void EditSpell::update(ga::Window& window)
    {
        frame++;
        this->dsp.v_PlayerPosition = { player.position.x, player.position.y };
        if (frame % 100 == 0) {
            this->spells.emplace_back(Spell(csp, dsp, this->window));
        }
        spells.remove_if([&](Spell& spell) {
            spell.update();
            return spell.b_Empty;
        });
        player.update();
    }
}