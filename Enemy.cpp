#include "Enemy.hpp"

using namespace std::string_literals;

namespace th {

    Enemy::Enemy(ga::jsonObj& obj, std::map<std::string, ga::Texture*>& textures, ga::Size2D windowSize)
        : sprite(nullptr), frame(0)
    {
        if (obj.has("init") && obj["init"].has("appearance") && obj["init"]["appearance"].has("sprite")) {
            std::string spritePath = obj["init"]["appearance"]["sprite"].val;
            if (textures.find(spritePath) == textures.end()) {
                textures[spritePath] = new ga::Texture("assets/images/"s + spritePath);
            }
            if (obj["init"]["appearance"].has("textureRectangle")) {
                auto& r = obj["init"]["appearance"]["textureRectangle"];
                int textureWidth  = textures[spritePath]->getWidth();
                int textureHeight = textures[spritePath]->getHeight();
                int width         = r["width"].toInt();
                int height        = r["height"].toInt();
                int nRows         = textureHeight / height;
                int nColumns      = textureWidth  / width;
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

    void Enemy::compileBehaviours(ga::jsonObj& obj) {
        const static std::unordered_map<std::string, int> enums = {
            { "none",        (int)DEPEND::NONE          },
            { "frame",       (int)DEPEND::FRAME         },
            { "if",          (int)CONDITIONAL::IF       },
            { "else",        (int)CONDITIONAL::ELSE     },
            { "elseif",      (int)CONDITIONAL::ELSEIF   },
            { "moveX",       (int)ACTION::MOVEX         },
            { "moveY",       (int)ACTION::MOVEY         },
            { "fire",        (int)ACTION::FIRE          },
            { "greaterthan", (int)OPERATOR::GREATERTHAN },
            { "lessthan",    (int)OPERATOR::LESSTHAN    },
            { "between",     (int)OPERATOR::BETWEEN     },
            { "equal",       (int)OPERATOR::EQUAL       },
            { "notequal",    (int)OPERATOR::NOTEQUAL    }
        };
        // Compile loop behaviour
        if (obj.has("loop")) {
            // Conditional Behaviour
            if (obj["loop"].has("conditionals")) {
                for (auto& c : obj["loop"]["conditionals"].objs) {
                    int dependence, conditional, op, value, value2;
                    std::vector<Behaviour> behaviours;
                    if (c.second.has("dependence")) {
                        auto it = enums.find(c.second["dependence"].val);
                        if (it != enums.end()) {
                            dependence = it->second;
                        }
                        else dependence = (int)DEPEND::FRAME;
                    }
                    else {
                        dependence = (int)DEPEND::FRAME;
                    }
                    if (c.second.has("op")) {
                        auto it = enums.find(c.second["op"].val);
                        if (it != enums.end()) {
                            op = it->second;
                        }
                        else op = (int)OPERATOR::EQUAL;
                    }
                    else {
                        op = (int)OPERATOR::EQUAL;
                    }
                    if (c.second.has("value")) {
                        value = c.second["value"].toInt();
                    }
                    else {
                        value = 0;
                    }
                    if (c.second.has("value2")) {
                        value2 = c.second["value2"].toInt();
                    }
                    else {
                        value2 = 0;
                    }
                    if (c.second.has("behaviour")) {
                        auto it = enums.find(c.second["behaviour"].val);
                        if (it != enums.end()) {
                            switch (it->second) {
                                case ((int)ACTION::MOVEX):
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::MOVEX, c.second["behaviour"]["x"].toInt() });
                                    break;
                                case ((int)ACTION::MOVEY):
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::MOVEY, c.second["behaviour"]["y"].toInt() });
                                    break;
                                case ((int)ACTION::FIRE):
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::FIRE, 0 });
                                    break;
                            }
                        }
                    }
                    if (c.second.has("conditional")) {
                        auto it = enums.find(c.second["conditional"].val);
                        if (it != enums.end()) {
                            conditional = it->second;
                        }
                        else {
                            conditional = (int)CONDITIONAL::IF;
                        }
                    }
                    else {
                        conditional = (int)CONDITIONAL::IF;
                    }
                    this->conditionalBehvaiours.emplace_back(Conditional{ .dependence = dependence, .conditional = conditional,
                        .op = op, .value = value, .value2 = value2, .behaviours = behaviours });
                }
            }
        }
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
                this->position.x += (float)behaviour.value;
                break;
            case (int)ACTION::MOVEY:
                this->position.y += (float)behaviour.value;
                break;
            case (int)ACTION::FIRE:
                this->polledSpell = behaviour.value;
                break;
            default: break;
        }
    }

}