#include "Enemy.hpp"

using namespace std::string_literals;

namespace th {

    Enemy::Enemy(EnemyParams* ep) {
        this->frame = 0;
        this->sprite = ep->sprite;
        this->conditionalBehvaiours = ep->conditionalBehaviours;
        this->staticBehaviours = ep->staticBehaviours;
        this->position.x = ep->x;
        this->position.y = ep->y;
        this->ap = ep->ap;
        this->currentAnimation = ep->defaultAnimation;
        this->currentFrame = ep->ap[ep->defaultAnimation].sequence[0];
    }

    Enemy::Enemy(const Enemy& old_obj)
    {
        this->sprite = new ga::Sprite(*old_obj.sprite);
    }

    Enemy::~Enemy() {
    }

    void Enemy::loop() {
        this->frame++;

        // Animation:
        if (frame % this->ap[this->currentAnimation].framesPerStep == 0) {
            this->currentFrame = (currentFrame + 1) % ap[this->currentAnimation].sequence.size();
            this->sprite->setTextureCoordinates(this->ap[this->currentAnimation].sequence[currentFrame], 0);
        }

        auto& c = conditionalBehvaiours;
        bool passed = false;
        for (int i = 0; i < this->conditionalBehvaiours.size(); i++) {
            switch (c[i].conditional) {
                case (int)CONDITIONAL::NONE:
                case (int)CONDITIONAL::IF:
                    break;
                case (int)CONDITIONAL::ELSEIF:
                case (int)CONDITIONAL::ELSE:
                    if (!passed) break;
                default: continue;
            }
            bool result = isTrue(c[i].dependence, c[i].conditional, c[i].op, c[i].value, c[i].value2);
            if (result) {
                for (auto& b : c[i].behaviours) {
                   perform(b);
                }
            }
            switch (c[i].conditional) {
                case (int)CONDITIONAL::NONE: return;
                case (int)CONDITIONAL::IF:
                case (int)CONDITIONAL::ELSEIF:
                    passed = result;
                default: continue;
            }
        }
    }

    void Enemy::render(ga::Window& window) {
        this->sprite->setPosition(this->position);
        window.getRenderer().Draw(*this->sprite);
    }

    bool Enemy::isTrue(int dependence, int condition, int op, int value, int value2) {
        uint64_t* dependent;
        switch (dependence) {
            case (int)DEPEND::FRAME:
                dependent = &this->frame;
                break;
            case (int)DEPEND::NONE:
                dependent = nullptr;
                break;
            default:
                break;
        }
        auto greaterthan = [&](){ if (*dependent > value) return true; return false; };
        auto lessthan    = [&](){ if (*dependent < value) return true; return false; };
        auto notequal    = [&](){ if (*dependent != value) return true; return false; };
        auto between     = [&](){ if (*dependent > value && *dependent < value2) return true; return false; };
        auto equal       = [&](){ if (*dependent == value) return true; return false; };
        std::function<bool()> compareFunction;
        switch (op) {
            case (int)OPERATOR::GREATERTHAN:
                compareFunction = greaterthan;
                break;
            case (int)OPERATOR::LESSTHAN:
                compareFunction = lessthan;
                break;
            case (int)OPERATOR::NOTEQUAL:
                compareFunction = notequal;
                break;
            case (int)OPERATOR::BETWEEN:
                compareFunction = between;
                break;
            case (int)OPERATOR::EQUAL:
                compareFunction = equal;
                break;
            case (int)OPERATOR::NONE:
                return true;
            default: return false;
        }
        return compareFunction();
    }

    void Enemy::perform(Behaviour& behaviour) {
        switch (behaviour.action) {
            case (int)ACTION::MOVEX:
                this->position.x += (float)behaviour.values[0];
                break;
            case (int)ACTION::MOVEY:
                this->position.y += (float)behaviour.values[0];
                break;
            case (int)ACTION::FIRE:
                this->polledSpell.spell = behaviour.values[0];
                this->polledSpell.rotation = behaviour.values[1];
                break;
            default: break;
        }
    }

}