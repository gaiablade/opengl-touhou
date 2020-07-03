#include "Enemy.hpp"

using namespace std::string_literals;

namespace th {

    Enemy::Enemy(jsonObj& obj, std::map<std::string, ga::Texture*>& textures, ga::Size2D windowSize)
        : sprite(nullptr), frame(0)
    {
        if (obj.has("init") && obj["init"].has("appearance") && obj["init"]["appearance"].has("sprite")) {
            std::string spritePath = obj["init"]["appearance"]["sprite"].val;
            if (textures.find(spritePath) == textures.end()) {
                textures[spritePath] = new ga::Texture("assets/images/"s + spritePath);
            }
            if (obj["init"]["appearance"].has("textureRectangle")) {
                auto& r = obj["init"]["appearance"]["textureRectangle"];
                int left = r["left"].toInt();
                int top = r["top"].toInt();
                int width = r["width"].toInt();
                int height = r["height"].toInt();
                ga::AnimationOptions opt {
                    .nFrames = 1, .nRows = 1, .nColumns = 1, .spriteWidth = width, .spriteHeight = height
                };
                this->sprite = new ga::Sprite(textures[spritePath], opt);
            }
            else {
                this->sprite = new ga::Sprite(textures[spritePath]);
            }

            if (obj["init"].has("position")) {
                auto pos = obj["init"]["position"];
                int x, y;
                if (pos["x"].val.find("center") != std::string::npos) {
                    x = windowSize.width / 2;
                }
                else {
                    x = pos["x"].toInt();
                }
                if (pos["y"].val.find("top") != std::string::npos) {
                    y = 0;
                }
                else {
                    y = pos["y"].toInt();
                }
                this->sprite->setPosition(ga::Position2D<float>(x, y));
            }
        }
        compileBehaviours(obj);
    }

    Enemy::Enemy(EnemyParams* ep) {
        this->frame = 0;
        this->sprite = ep->sprite;
        this->conditionalBehvaiours = ep->conditionalBehaviours;
        this->staticBehaviours = ep->staticBehaviours;
        this->position.x = ep->x;
        this->position.y = ep->y;
    }

    Enemy::Enemy(const Enemy& old_obj)
    {
        this->sprite = new ga::Sprite(*old_obj.sprite);
    }

    Enemy::~Enemy() {
    }

    void Enemy::compileBehaviours(jsonObj& obj) {
        // Compile loop behaviour
        if (obj.has("loop")) {
            // Conditional Behaviour
            if (obj["loop"].has("conditionals")) {
                for (auto& c : obj["loop"]["conditionals"].objs) {
                    int dependence, conditional, op, value, value2;
                    std::vector<Behaviour> behaviours;
                    for (auto& c2 : c.second.objs) {
                        if (c2.first.find("dependence") != std::string::npos) {
                            if (c2.second.val.find("frame") != std::string::npos) {
                                dependence = (int)DEPEND::FRAME;
                            }
                            else {
                                dependence = (int)DEPEND::NONE;
                            }
                        }
                        else if (c2.first.find("op") != std::string::npos) {
                            if (c2.second.val.find("greaterthan") != std::string::npos) {
                                op = (int)OPERATOR::GREATERTHAN;
                            }
                            else if (c2.second.val.find("notequal") != std::string::npos) {
                                op = (int)OPERATOR::NOTEQUAL;
                            }
                            else if (c2.second.val.find("between") != std::string::npos) {
                                op = (int)OPERATOR::BETWEEN;
                            }
                            else {
                                op = (int)OPERATOR::NONE;
                            }
                        }
                        else if (c2.first.find("value2") != std::string::npos) {
                            value2 = c2.second.toInt();
                        }
                        else if (c2.first.find("value") != std::string::npos) {
                            value = c2.second.toInt();
                        }
                        else if (c2.first.find("behaviour") != std::string::npos) {
                            for (auto& c3 : c2.second.objs) {
                                if (c3.first.find("moveX") != std::string::npos) {
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::MOVEX, c3.second["x"].toInt() });
                                }
                                else if (c3.first.find("moveY") != std::string::npos) {
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::MOVEY, c3.second["y"].toInt() });
                                }
                                else if (c3.first.find("fire") != std::string::npos) {
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::FIRE, 0 });
                                }
                            }
                        }
                        else if (c2.first.find("conditional") != std::string::npos) {
                            if (c2.second.val.find("elseif") != std::string::npos) {
                                conditional = (int)CONDITIONAL::ELSEIF;
                            }
                            else if (c2.second.val.find("if") != std::string::npos) {
                                conditional = (int)CONDITIONAL::IF;
                            }
                            else if (c2.second.val.find("else") != std::string::npos) {
                                conditional = (int)CONDITIONAL::ELSE;
                            }
                        }
                    }
                    this->conditionalBehvaiours.emplace_back(Conditional{ .dependence = dependence, .conditional = conditional,
                        .op = op, .value = value, .value2 = value2, .behaviours = behaviours });
                }
            }
        }
    }

    void Enemy::loop() {
        this->frame++;
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
            case (int)OPERATOR::NONE:
                return true;
            default: return false;
        }
        return compareFunction();
    }

    void Enemy::perform(Behaviour& behaviour) {
        switch (behaviour.action) {
            case (int)ACTION::MOVEX:
                this->position.x += (float)behaviour.value;
                break;
            case (int)ACTION::MOVEY:
                this->position.y += (float)behaviour.value;
                break;
            default: break;
        }
    }

}