#include "EditSpell.hpp"

namespace th {
    EditSpell::EditSpell(int width, int height, ga::Window* window)
        : window(window), imgui(*window), playerTex(new ga::Texture("assets/images/marisa.png")),
            playerSprite(new ga::Sprite(playerTex)), frame(0), currentSpellSelected(0)
    {
        texture = new ga::Texture("assets/images/red_arrow.png");
        sprite = new ga::Sprite(texture);

        this->formationNames = {
                "None", "Radial", "Whirlpool",
                "Homing", "Rumia_1", "Rumia_2",
                "Rumia_3"
        };

        // Player
        this->player.sprite = this->playerSprite;
        this->player.position = { 450.f, 500.f };

        this->initCSPS();

        this->dsp = {
                .v_SpellPosition = {
                        static_cast<float>(window->getWidth()) / 2, static_cast<float>(window->getHeight()) / 2
                },
                .v_PlayerPosition = {player.position.x, player.position.y}
        };
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

        ImGui::Begin("Spells");
        ImGui::SliderInt("Spell", &currentSpellSelected, 0, this->csps.size() - 1);
        ImGui::LabelText("Spell Parameters", nullptr);
        ImGui::ListBox("Formation", &this->csps[currentSpellSelected].n_Formation,
                       this->formationNames.data(), this->formationNames.size());
        ImGui::SliderInt("Frame Duration", &this->csps[currentSpellSelected].n_Duration, 1, 800);
        ImGui::SliderInt("NumBullets", &this->csps[currentSpellSelected].n_NumBullets, 1, 100);
        ImGui::SliderFloat("Speed", &this->csps[currentSpellSelected].f_Speed, 0.f, 20.f);
        ImGui::End();

        imgui.Begin("Main");
        ImGui::SliderFloat("PlayerX", &player.position.x, 0.f, this->window->getWidth());
        ImGui::SliderFloat("PlayerY", &player.position.y, 0.f, this->window->getHeight());
        if (ImGui::Button("Fire")) {
            createSpell();
        }
        if (ImGui::Button("Add Spell")) {
            this->csps.emplace_back(C_SpellParams{
                .n_Formation = static_cast<int>(FORM::RAD),
                .n_NumBullets = 4,
                .n_Duration = 60,
                .f_Speed = 3.f,
                .sprite = this->sprite
            });
        }
        if (ImGui::Button("Reset Spells")) {
            this->initCSPS();
        }
        imgui.End();

        imgui.Render();
    }

    void EditSpell::update(ga::Window& window)
    {
        frame++;
        this->dsp.v_PlayerPosition = { player.position.x, player.position.y };
        spells.remove_if([&](Spell& spell) {
            spell.update();
            return spell.b_Empty;
        });
        player.update();
    }

    void EditSpell::createSpell() {
        for (auto& csp : this->csps) {
            this->spells.emplace_back(Spell(csp, dsp, this->window));
        }
    }

    void EditSpell::initCSPS() {
        csps.clear();
        for (int i = 0; i < 3; i++) {
            this->csps.emplace_back(C_SpellParams{
                    .n_Formation = static_cast<int>(FORM::RAD),
                    .n_NumBullets = 4,
                    .n_Duration = 60,
                    .f_Speed = 3.f,
                    .sprite = this->sprite
            });
        }
    }
}