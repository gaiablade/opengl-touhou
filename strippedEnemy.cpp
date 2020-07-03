#include "strippedEnemy.hpp"

using namespace std::string_literals;

namespace th {

    Enemy::Enemy(jsonObj& obj)
        : frame(0)
    {
        ga::DeltaTime dt;
        if (obj.has("init") && obj["init"].has("appearance") && obj["init"]["appearance"].has("sprite")) {
            std::string spritePath = obj["init"]["appearance"]["sprite"].val;
            if (obj["init"].has("position")) {
                auto pos = obj["init"]["position"];
                int x, y;
                if (pos["x"].val.find("center") != std::string::npos) {
                    x = 0;
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
            }
        }
        compileBehaviours(obj);
        std::cout << dt.getDt() << '\n';
    }

    Enemy::Enemy(const Enemy& old_obj)
    {
    }

    Enemy::~Enemy() {
    }

    void Enemy::compileBehaviours(jsonObj& obj) {
        // Compile loop behaviour
        if (obj.has("loop")) {
            // Conditional Behaviour
            if (obj["loop"].has("conditionals")) {
                for (auto& c : obj["loop"]["conditionals"].objs) {
                    int dependence, condition, value, value2;
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
                        else if (c2.first.find("condition") != std::string::npos) {
                            if (c2.second.val.find("greaterthan") != std::string::npos) {
                                condition = (int)COMPARE::GREATERTHAN;
                            }
                            else if (c2.second.val.find("notequal") != std::string::npos) {
                                condition = (int)COMPARE::NOTEQUAL;
                            }
                            else if (c2.second.val.find("else") != std::string::npos) {
                                condition = (int)COMPARE::ELSE;
                            }
                            else if (c2.second.val.find("between") != std::string::npos) {
                                condition = (int)COMPARE::BETWEEN;
                            }
                            else {
                                condition = (int)COMPARE::NONE;
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
                    }
                    this->conditionalBehvaiours.emplace_back(Conditional{ .dependence = dependence, .condition = condition,
                        .value = value, .value2 = value2, .behaviours = behaviours });
                }
            }
        }
    }

    void Enemy::loop() {
        this->frame++;
        for (auto& condition: this->conditionalBehvaiours) {
            if (isTrue(condition.dependence, condition.condition, condition.value, condition.value2)) {
                passed = true;
                for (auto& b : condition.behaviours) {
                    perform(b);
                }
            }
            else {
                passed = false;
            }
        }
    }

    bool Enemy::isTrue(int dependence, int condition, int value, int value2) {
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
        switch (condition) {
            case (int)COMPARE::GREATERTHAN:
                if (*dependent > value) {
                    return true;
                }
                break;
            case (int)COMPARE::LESSTHAN:
                if (*dependent < value) {
                    return true;
                }
                break;
            case (int)COMPARE::NOTEQUAL:
                if (*dependent != value) {
                    return true;
                }
                break;
            case (int)COMPARE::BETWEEN:
                if (*dependent > value && *dependent < value2) {
                    return true;
                }
                return false;
            case (int)COMPARE::ELSE:
                if (this->passed == false) {
                    return true;
                }
                return false;
            case (int)COMPARE::NONE:
            default: return false;
        }
    }

    void Enemy::perform(Behaviour& behaviour) {
        switch (behaviour.action) {
            case (int)ACTION::MOVEX:
                this->posX += behaviour.value;
                break;
            case (int)ACTION::MOVEY:
                this->posY += behaviour.value;
                break;
            default: break;
        }
    }

}