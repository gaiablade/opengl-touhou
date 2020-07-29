#include "Spell.hpp"

ga::Vector2<float> homing_dir(const ga::v2f& spawn, const ga::v2f& target) {
    ga::Vector2<float> v;
    v.x = target.x - spawn.x;
    v.y = target.y - spawn.y;
    return v.unitVector();
}
namespace th {
    void Bullet::Move_Radial() {
        this->v_Position.x += this->v_Direction.x;
        this->v_Position.y += this->v_Direction.y;
    }
    void Bullet::Move_Whirlpool() {
        this->f_Rotation += 0.2;
        this->v_Position.x = this->v_Center.x + ((this->n_Lifetime * this->f_Speed) * cos((this->f_Rotation) * PI / 180));
        this->v_Position.y = this->v_Center.y + ((this->n_Lifetime * this->f_Speed) * sin((this->f_Rotation) * PI / 180));
    }
    void Bullet::Move_Homing() {
        this->v_Position.x += this->v_Direction.x * this->f_Speed;
        this->v_Position.y += this->v_Direction.y * this->f_Speed;
    }
}

namespace th {
    Spell::Spell(const C_SpellParams& csp, const D_SpellParams& dsp, ga::Window* windowPointer) {
        this->sprite = csp.sprite;
        this->n_Formation = csp.n_Formation;
        this->n_NumBullets = csp.n_NumBullets;
        this->n_Lifetime = 0;
        this->n_Duration = csp.n_Duration;
        this->f_Speed = csp.f_Speed;
        this->v_Position = dsp.v_SpellPosition;
        this->windowPointer = windowPointer;

        switch (this->n_Formation) {
            case (int)FORM::RAD:
                initRadial(csp, dsp);
                break;
            case (int)FORM::WHIRL:
                initWhirlpool(csp, dsp);
                break;
            case (int)FORM::HOMING:
                initHoming(csp, dsp);
                break;
        }
    }

    void Spell::initRadial(const C_SpellParams& csp, const D_SpellParams& dsp) {
        float angle = 360.0f / n_NumBullets;
        for (float i = 0; i < 360.0f; i += angle) {
            this->l_Bullets.emplace_back(Bullet{
                .v_Position  = { cos(i * PI / 180) + v_Position.x, sin(i * PI / 180) + v_Position.y },
                .v_Direction = { cos(i * PI / 180) * f_Speed, sin(i * PI / 180) * f_Speed },
                .n_Duration = this->n_Duration,
                .f_Rotation = i,
                .f_Speed = this->f_Speed,
                .c_Collider = { ga::ColliderOpt{ .width = 10.f, .height = 10.f } }
            });
            this->l_Bullets.back().c_Collider.setRotation(l_Bullets.back().f_Rotation);
        }
    }

    void Spell::initWhirlpool(const C_SpellParams& csp, const D_SpellParams& dsp) {
        float angle = 360.0f / n_NumBullets;
        for (float i = 0.f; i < 360.0f; i += angle) {
            this->l_Bullets.emplace_back(Bullet {
                .v_Position = { cos((i) * PI / 180) + v_Position.x, sin((i) * PI / 180) + v_Position.y },
                .v_Center = { this->v_Position.x, this->v_Position.y },
                .n_Duration = this->n_Duration,
                .f_Rotation = i,
                .f_Speed = this->f_Speed,
                .c_Collider = ga::Collider(ga::ColliderOpt{ .width = 10.f, .height = 10.f }),
            });
            this->l_Bullets.back().c_Collider.setRotation(l_Bullets.back().f_Rotation);
        }
    }

    void Spell::initHoming(const C_SpellParams& csp, const D_SpellParams& dsp) {
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

    void Spell::render(ga::Window& window) {
        for (auto& bullet : l_Bullets) {
            this->sprite->setPosition(ga::Position2D<float>(bullet.v_Position.x, bullet.v_Position.y));
            this->sprite->setRotation(bullet.f_Rotation);
            window.getRenderer().Draw(*sprite);
        }
    }
    
    void Spell::update() {
        this->n_Lifetime++;
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
                    bullet.Move_Homing();
                    break;
                default: break;
            }
            bullet.c_Collider.setPosition(ga::Position2D<float>( bullet.v_Position.x, bullet.v_Position.y ));
            return bullet.n_Lifetime > bullet.n_Duration;
        });
        this->b_Empty = this->l_Bullets.empty();
    }
}