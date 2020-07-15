#include "Spell.hpp"

//#define PI 3.141596
const float speed = 2.f;
const int numBullet = 16;

// Movement Functions:
void mov_linear(th::Bullet& bullet) {
    bullet.position.x += bullet.direction.x;
    bullet.position.y += bullet.direction.y;
}

void mov_whirlpool(th::Bullet& bullet) {
    bullet.rotation.angle += 0.2;
    bullet.position.x = bullet.center.x + ((bullet.lifetime * bullet.speed) * cos((bullet.rotation.angle) * PI / 180));
    bullet.position.y = bullet.center.y + ((bullet.lifetime * bullet.speed) * sin((bullet.rotation.angle) * PI / 180));
}

namespace th {

    Spell::Spell(ga::Sprite* sprite) : sprite(sprite) {
        lifetime = 0;
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

    Spell::Spell(SpellInfo& si, const ga::Position2D<float>& position, const int& rotation)
        : formation(si.formation), lifetime(0), empty(false), sprite(si.sprite)
    {
        this->sprite = si.sprite;
        float angle = 360.0f / si.numBullets;
        this->position.x = position.x;
        this->position.y = position.y;
        switch (si.formation) {
            case (int)FORMATION::RADIAL:
                for (float i = 0; i < 360.0f; i += angle) {
                    switch (si.startingPosition) {
                        case (int)POSITION::OWNER:
                            this->bullets.emplace_back(Bullet {
                                .position = ga::Position2D<float>(cos((i + rotation) * PI / 180) + position.x, sin((i + rotation) * PI / 180) + position.y),
                                .direction = ga::Vector2<float>(cos((i + rotation) * PI / 180) * si.speed, sin((i + rotation) * PI / 180) * si.speed),
                                .rotation = ga::Rotation2D(i + rotation),
                                .coll = ga::Collider(ga::ColliderOpt{ .width = 10.f, .height = 10.f }),
                                .OOB = false,
                                .lifetime = 0
                            });
                            this->bullets.back().coll.setRotation(bullets.back().rotation);
                            break;
                        case (int)POSITION::CUSTOM:
                            break;
                    }
                }
                break;
            case (int)FORMATION::WHIRLPOOL:
                for (float i = 0.f; i < 360.0f; i += angle) {
                    this->bullets.emplace_back(Bullet {
                        .position = ga::Position2D<float>(cos((i + rotation) * PI / 180) + position.x, sin((i + rotation) * PI / 180) + position.y),
                        .center = ga::Position2D<float>(this->position.x, this->position.y),
                        .speed = si.speed,
                        .rotation = ga::Rotation2D(i + rotation),
                        .coll = ga::Collider(ga::ColliderOpt{ .width = 10.f, .height = 10.f }),
                        .OOB = false,
                        .lifetime = 0
                    });
                    this->bullets.back().coll.setRotation(bullets.back().rotation);
                }
                break;
        }
    }

    void Spell::update() {
        this->lifetime++;
        bullets.remove_if([&](Bullet& bullet) {
            // UPDATE BULLETS HERE
            bullet.lifetime++;
            switch (this->formation) {
                case (int)FORMATION::RADIAL:
                    mov_linear(bullet);
                    break;
                case (int)FORMATION::WHIRLPOOL:
                    mov_whirlpool(bullet);
                    break;
                default: break;
            }
            return bullet.OOB;
        });
        this->empty = bullets.empty();
    }

    void Spell::render(ga::Window& window) {
        for (auto& bullet : bullets) {
            this->sprite->setPosition(ga::Position2D<float>(bullet.position.x, bullet.position.y));
            this->sprite->setRotation(bullet.rotation);
            window.getRenderer().Draw(*sprite);
        }
    }
}