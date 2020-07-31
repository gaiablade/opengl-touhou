#include "EditSpell.hpp"

int curr_item = 1;
const char* itemNames[] = { "None", "Radial", "Whirlpool", "Homing" };

namespace th {
    EditSpell::EditSpell(int width, int height, ga::Window* window)
        : window(window), imgui(*window), playerTex(new ga::Texture("assets/images/marisa.png")), playerSprite(new ga::Sprite(playerTex)), frame(0),
            currentSpellSelected(0)
    {
        texture = new ga::Texture("assets/images/red_arrow.png");
        sprite = new ga::Sprite(texture);

        // Player
        this->player.sprite = this->playerSprite;
        this->player.position = { 450.f, 500.f };

        csps.reserve(3);
        this->csps[0] = { .n_Formation = static_cast<int>(FORM::RAD), .n_NumBullets = 4, .n_Duration = 60, .f_Speed = 3.f, .sprite = this->sprite };
        this->csps[1] = { .n_Formation = static_cast<int>(FORM::RAD), .n_NumBullets = 4, .n_Duration = 60, .f_Speed = 3.f, .sprite = this->sprite };
        this->csps[2] = { .n_Formation = static_cast<int>(FORM::RAD), .n_NumBullets = 4, .n_Duration = 60, .f_Speed = 3.f, .sprite = this->sprite };
        this->dsp = { .v_SpellPosition = { window->getWidth() / 2, window->getHeight() / 2 }, .v_PlayerPosition = { player.position.x, player.position.y } };

        names.push_back("1");
        names.push_back("2");
        names.push_back("3");
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
        ImGui::ListBox("Choose a spell", &currentSpellSelected, &names[0], names.size());
        ImGui::End();

        imgui.Begin("Main");
        ImGui::SliderFloat("PlayerX", &player.position.x, 0.f, this->window->getWidth());
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
            std::stringstream ss;
            auto s = (int)names.size();
            std::cout << s << '\n';
            ss << (int)s;
            std::cout << ss.str();
            this->names.push_back({ss.str().c_str()});
        }
        imgui.End();

        imgui.Render();
    }

    void EditSpell::update(ga::Window& window)
    {
        frame++;
        this->dsp.v_PlayerPosition = { player.position.x, player.position.y };
        /*
        if (frame % 100 == 0) {
            createSpell();
        }
        */
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
}