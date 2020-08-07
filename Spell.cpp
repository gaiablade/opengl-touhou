#include "Spell.hpp"

ga::Vector2<float> homing_dir(const ga::v2f& spawn, const ga::v2f& target) {
    ga::Vector2<float> v;
    v.x = target.x - spawn.x;
    v.y = target.y - spawn.y;
    return v.unitVector();
}

// Init Spell
namespace th {
    template <FORM form>
    void th::Spell::initSpell(const C_SpellParams& csp, const D_SpellParams& dsp) {
    }

    template <>
    void th::Spell::initSpell<th::FORM::RAD>(const C_SpellParams& csp, const D_SpellParams& dsp) {
        // TODO: Make compliant with FLP30-C
        float angle = 360.0f / static_cast<float>(n_NumBullets);
        for (float i = 0; i < 360.0f; i += angle) {
            this->l_Bullets.emplace_back(Bullet{
                    .v_Position  = { static_cast<float>(cos(i * PI / 180) + v_Position.x),
                                     static_cast<float>(sin(i * PI / 180) + v_Position.y) },
                    .v_Direction = { static_cast<float>(cos(i * PI / 180) * f_Speed),
                                     static_cast<float>(sin(i * PI / 180) * f_Speed) },
                    .n_Duration = this->n_Duration,
                    .f_Rotation = i,
                    .f_Speed = this->f_Speed,
                    .c_Collider = { ga::ColliderOpt{ .width = 10.f, .height = 10.f } }
            });
            this->l_Bullets.back().c_Collider.setRotation(l_Bullets.back().f_Rotation);
        }
    }

    template<>
    void th::Spell::initSpell<th::FORM::WHIRL>(const C_SpellParams& csp, const D_SpellParams& dsp) {
        // TODO: Make compliant with FLP30-C
        float angle = 360.0f / static_cast<float>(n_NumBullets);
        for (float i = 0.f; i < 360.0f; i += angle) {
            this->l_Bullets.emplace_back(Bullet {
                    .v_Position = { static_cast<float>(cos((i) * PI / 180) + v_Position.x),
                                    static_cast<float>(sin((i) * PI / 180) + v_Position.y) },
                    .v_Center = { this->v_Position.x, this->v_Position.y },
                    .n_Duration = this->n_Duration,
                    .f_Rotation = i,
                    .f_Speed = this->f_Speed,
                    .c_Collider = ga::Collider(ga::ColliderOpt{ .width = 10.f, .height = 10.f }),
            });
            this->l_Bullets.back().c_Collider.setRotation(l_Bullets.back().f_Rotation);
        }
    }

    template<>
    void th::Spell::initSpell<th::FORM::HOMING>(const C_SpellParams& csp, const D_SpellParams& dsp) {
        this->l_Bullets.emplace_back(Bullet {
                .v_Position = { v_Position.x, v_Position.y },
                .v_Direction = homing_dir({v_Position.x, v_Position.y}, dsp.v_PlayerPosition),
                .v_Target = dsp.v_PlayerPosition,
                .n_Duration = this->n_Duration,
                .f_Rotation = 0,
                .f_Speed = this->f_Speed,
                .c_Collider = { ga::ColliderOpt{ .width = 10.f, .height = 10.f } },
        });
        this->l_Bullets.back().f_Rotation = this->l_Bullets.back().v_Direction.unitVector().angle();
        this->l_Bullets.back().c_Collider.setRotation(l_Bullets.back().f_Rotation);
    }

    template<>
    void th::Spell::initSpell<th::FORM::RUMIA_HOMING_LINE_1>(const C_SpellParams& csp, const D_SpellParams& dsp) {
        //some bullets are faster than others
        for (int i = 0; i < csp.n_NumBullets; i++) {
            this->l_Bullets.emplace_back(Bullet {
                .v_Position = { v_Position.x, v_Position.y },
                .v_Direction = homing_dir({ v_Position.x, v_Position.y }, dsp.v_PlayerPosition),
                .v_Target = dsp.v_PlayerPosition,
                .n_Duration = this->n_Duration,
                .f_Rotation = {},
                .f_Speed = this->f_Speed + static_cast<float>(i),
                .c_Collider = { ga::ColliderOpt{ .width = 10.f, .height = 10.f } }
            });
            this->l_Bullets.back().f_Rotation = this->l_Bullets.back().v_Direction.unitVector().angle();
            this->l_Bullets.back().c_Collider.setRotation(this->l_Bullets.back().f_Rotation);
        }
    }

    template<>
    void th::Spell::initSpell<th::FORM::RUMIA_SEMICIRCLE_2>(const C_SpellParams& csp, const D_SpellParams& dsp) {
        this->l_Bullets.emplace_back(Bullet {
                .v_Position  = { static_cast<float>(cos(0) + v_Position.x),
                                 static_cast<float>(sin(0) + v_Position.y) },
                .v_Direction = { static_cast<float>(cos(0) * f_Speed),
                                 static_cast<float>(sin(0) * f_Speed) },
                .n_Duration = this->n_Duration,
                .f_Rotation = {},
                .f_Speed = this->f_Speed,
                .c_Collider = { ga::ColliderOpt{ .width = 10.f, .height = 10.f } }
        });
    }

    template<>
    void th::Spell::initSpell<th::FORM::RUMIA_LASER_3>(const C_SpellParams& csp, const D_SpellParams& dsp) {
        this->l_Bullets.emplace_back(Bullet {
                .v_Position = { v_Position.x, v_Position.y },
                .v_Direction = homing_dir({ v_Position.x, v_Position.y }, dsp.v_PlayerPosition).unitVector(),
                .n_Duration = this->n_Duration,
                .f_Rotation = {},
                .f_Speed = {},
                .c_Collider = { ga::ColliderOpt{ .width = 10.f, .height = 800.f }}
        });
        this->l_Bullets.back().f_Rotation = this->l_Bullets.back().v_Direction.unitVector().angle();
        this->l_Bullets.back().c_Collider.setRotation({this->l_Bullets.back().f_Rotation});
        std::cout << l_Bullets.back().v_Direction.unitVector().angle() << '\n';
    }
}

// Update Spell
namespace th {
    template<th::FORM form>
    void Spell::updateSpell() {
    }

    template<>
    void Spell::updateSpell<th::FORM::NONE>() {
    }

    template<>
    void Spell::updateSpell<th::FORM::RUMIA_SEMICIRCLE_2>() {
        const static int framesPerBullet = 10;
        const int angle = 180 / this->n_NumBullets;
        if (this->n_Lifetime % framesPerBullet == 0 && this->n_Lifetime / framesPerBullet < this->n_NumBullets) {
            const auto num = this->n_Lifetime / framesPerBullet;
            this->l_Bullets.emplace_back(Bullet {
                .v_Position  = { static_cast<float>(cos(angle * num * PI / 180) + v_Position.x),
                                 static_cast<float>(sin(angle * num * PI / 180) + v_Position.y) },
                .v_Direction = { static_cast<float>(cos(angle * num * PI / 180) * (f_Speed + num)),
                                 static_cast<float>(sin(angle * num * PI / 180) * (f_Speed + num)) },
                .n_Duration = this->n_Duration,
                .f_Rotation = {},
                .f_Speed = this->f_Speed + static_cast<float>(num),
                .c_Collider = { ga::ColliderOpt{ .width = 10.f, .height = 10.f } }
            });
            this->l_Bullets.back().f_Rotation = this->l_Bullets.back().v_Direction.unitVector().angle();
            this->l_Bullets.back().c_Collider.setRotation(this->l_Bullets.back().f_Rotation);
        }
    }

    template<>
    void Spell::updateSpell<th::FORM::RUMIA_LASER_3>() {
    }
}

namespace th {
    void Bullet::Move_Radial() {
        this->v_Position.x += this->v_Direction.x;
        this->v_Position.y += this->v_Direction.y;
    }
    void Bullet::Move_Whirlpool() {
        this->f_Rotation += 0.2;
        this->v_Position.x = this->v_Center.x +
                ((this->n_Lifetime * this->f_Speed) * cos((this->f_Rotation) * PI / 180));
        this->v_Position.y = this->v_Center.y +
                ((this->n_Lifetime * this->f_Speed) * sin((this->f_Rotation) * PI / 180));
    }
    void Bullet::Move_Homing() {
        this->v_Position.x += this->v_Direction.x * this->f_Speed;
        this->v_Position.y += this->v_Direction.y * this->f_Speed;
    }
}

namespace th {
    Spell::Spell(const C_SpellParams& csp, const D_SpellParams& dsp, ga::Window* windowPointer) {
        this->n_Formation = csp.n_Formation;
        this->n_NumBullets = csp.n_NumBullets;
        this->n_Lifetime = 0;
        this->n_Duration = csp.n_Duration;
        this->f_Speed = csp.f_Speed;
        this->v_Position = dsp.v_SpellPosition;
        this->windowPointer = windowPointer;

        switch (this->n_Formation) {
            case (int)FORM::RAD:
                this->sprite = csp.sprite;
                initSpell<FORM::RAD>(csp, dsp);
                break;
            case (int)FORM::WHIRL:
                this->sprite = csp.sprite;
                initSpell<FORM::WHIRL>(csp, dsp);
                break;
            case (int)FORM::HOMING:
                this->sprite = csp.sprite;
                initSpell<FORM::HOMING>(csp, dsp);
                break;
            case (int)FORM::RUMIA_HOMING_LINE_1:
                this->sprite = csp.sprite;
                initSpell<FORM::RUMIA_HOMING_LINE_1>(csp, dsp);
                break;
            case (int)FORM::RUMIA_SEMICIRCLE_2:
                this->sprite = csp.sprite;
                initSpell<FORM::RUMIA_SEMICIRCLE_2>(csp, dsp);
                break;
            case (int)FORM::RUMIA_LASER_3:
                this->rect = new ga::ColorRect({1.f, 1.f, 1.f, 1.f}, 1600.f, 10.f);
                initSpell<FORM::RUMIA_LASER_3>(csp, dsp);
                break;
        }
    }

    void Spell::render(ga::Window& window) {
        switch (this->n_Formation) {
            case (int)FORM::RUMIA_LASER_3:
                for (auto& bullet: l_Bullets) {
                    this->rect->setPosition({bullet.v_Position.x, bullet.v_Position.y});
                    this->rect->setRotation(bullet.f_Rotation);
                    window.getRenderer().Draw(*this->rect);
                }
                break;
            default:
                for (auto& bullet : l_Bullets) {
                    this->sprite->setPosition(ga::Position2D<float>(bullet.v_Position.x, bullet.v_Position.y));
                    this->sprite->setRotation(bullet.f_Rotation + 180.f);
                    window.getRenderer().Draw(*sprite);
                }
                break;
        }
    }

    void Spell::update() {
        this->n_Lifetime++;
        switch (this->n_Formation) {
            case (int)FORM::RUMIA_SEMICIRCLE_2:
                this->updateSpell<FORM::RUMIA_SEMICIRCLE_2>();
                break;
            default:
                this->updateSpell<FORM::NONE>();
                break;
        }
        this->l_Bullets.remove_if([&](Bullet& bullet) {
            // UPDATE BULLETS HERE
            bullet.n_Lifetime++;
            switch (this->n_Formation) {
                case (int)FORM::RAD:
                    bullet.Move_Radial();
                    break;
                case (int)FORM::WHIRL:
                    bullet.Move_Whirlpool();
                    break;
                case (int)FORM::HOMING:
                    //bullet.Move_Homing();
                    //break;
                case (int)FORM::RUMIA_HOMING_LINE_1:
                    bullet.Move_Homing();
                    break;
                case (int)FORM::RUMIA_SEMICIRCLE_2:
                    bullet.Move_Radial();
                    break;
                default: break;
            }
            bullet.c_Collider.setPosition(ga::Position2D<float>( bullet.v_Position.x, bullet.v_Position.y ));
            return bullet.n_Lifetime > bullet.n_Duration;
        });
        this->b_Empty = this->l_Bullets.empty();
    }
}