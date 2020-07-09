#include "Spell.hpp"

//#define PI 3.141596
const float speed = 2.f;
const int numBullet = 16;

namespace th {
    Spell::Spell(ga::Sprite* sprite) : sprite(sprite) {
        lifetime = 0;
        this->bullets.reserve(numBullet);
        const float angle = 360.0f / numBullet;
        /*
        for (float i = 0; i < 360.; i += angle) {
            this->bullets.emplace_back(Bullet{
                ga::Vector2<float>(cos(i * PI / 180) * speed, sin(i * PI / 180) * speed),
                ga::Position2D<float>(cos(i * PI / 180) * 5 + 300, sin(i * PI / 180) * 5 + 300)
            });
        }
        std::cout << bullets.capacity() << ' ' << bullets.size() << std::endl;
        */
    }

    Spell::Spell(SpellInfo& si, const ga::Position2D<float>& position, const int& rotation) {
        lifetime = 0;
        this->sprite = si.sprite;
        this->bullets.reserve(si.numBullets);
        switch (si.formation) {
            case (int)FORMATION::RADIAL:
                float angle = 360.0f / si.numBullets;
                for (float i = 0; i < 360.0f; i += angle) {
                    switch (si.startingPosition) {
                        case (int)POSITION::OWNER:
                            this->bullets.emplace_back(Bullet{
                                ga::Vector2<float>(cos((i + rotation) * PI / 180) * si.speed, sin((i + rotation) * PI / 180) * si.speed),
                                ga::Position2D<float>(cos((i + rotation) * PI / 180) + position.x, sin((i + rotation) * PI / 180) + position.y),
                                ga::Rotation2D(i + rotation),
                                ga::Collider(ga::ColliderOpt{10.0f, 10.0f})
                            });
                            this->bullets.back().coll.setRotation(bullets.back().rotation);
                            break;
                        case (int)POSITION::CUSTOM:
                            break;
                    }
                }
                break;
        }
    }

    void Spell::update() {
        this->lifetime++;
        for (auto& b : bullets) {
            b.update();
        }
    }

    void Spell::render(ga::Window& window) {
        for (auto& bullet : bullets) {
            this->sprite->setPosition(ga::Position2D<float>(bullet.position.x, bullet.position.y));
            this->sprite->setRotation(bullet.rotation);
            window.getRenderer().Draw(*sprite);
        }
    }
}