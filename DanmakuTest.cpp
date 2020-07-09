#include "DanmakuTest.hpp"

using namespace std::string_literals;

struct textureRectangle {
    int left = 0, top = 0, width = 0, height = 0;
};

int toInt(const std::string& str) {
    std::stringstream ss(str);
    int result;
    ss >> result;
    if (ss.fail()) {
        ss.clear();
        return -1;
    }
    return result;
}

namespace th {
    DanmakuTest::DanmakuTest(int width, int height, ga::Window* window)
        : background(ga::Color(0.2588f, 0.4706f, 0.9608f, 1.0f), width, height),
          bar(ga::Color(1.0f, 0.0f, 0.0f, 1.0f), width / 5, height), window(window)
    {
        this->soundEngine = ik::createIrrKlangDevice();
        //soundEngine->play2D("assets/music/bucket.ogg", true);
        this->status = 0;
        this->frame = 0;
        background.setPosition(ga::Position2D<float>(width/2, height/2));
        bar.setPosition(ga::Position2D<float>(width - bar.getWidth()/2, height/2));

        compileSpells();
        compileEnemies();
        compileLevel();
    }

    DanmakuTest::~DanmakuTest() {
        for (auto& e: enemies) {
            delete e;
        }
        this->enemies.clear();
        for (auto& s : sprites) {
            delete s.second;
        }
        for (auto& p : this->textures) {
            delete p.second;
        }
        soundEngine->drop();
    }

    void DanmakuTest::render(ga::Window& window) {
        window.getRenderer().Draw(background);
        for (auto& e : this->enemies) {
            e->render(window);
        }
        for (auto& s : this->spells) {
            s.render(window);
        }
        window.getRenderer().Draw(bar);
    }

    void DanmakuTest::update(ga::Window& window) {
        const auto it = enemySpawns.find(frame);
        if (it != enemySpawns.end()) {
            for (auto e : it->second) {
                this->enemies.push_back(new Enemy(&this->enemyParams[e.index]));
                this->enemies.back()->position.x = e.x;
                this->enemies.back()->position.y = e.y;
            }
        }
        for (auto& e : enemies) {
            e->loop();
            if (e->polledSpell != -1) {
                this->spells.emplace_back(Spell(this->spellLibrary[e->polledSpell], e->position));
                e->polledSpell = -1;
            }
        }
        for (auto& s : spells) {
            s.update();
        }
        frame++;
    }

    void DanmakuTest::compileEnemies() {
        const static std::unordered_map<std::string, int> enums = {
            { "frame"s,       (int)DEPEND::FRAME         },
            { "none"s,        (int)DEPEND::NONE          },
            { "equal"s,       (int)OPERATOR::EQUAL       },
            { "between"s,     (int)OPERATOR::BETWEEN     },
            { "notequal"s,    (int)OPERATOR::NOTEQUAL    },
            { "lessthan"s,    (int)OPERATOR::LESSTHAN    },
            { "greaterthan"s, (int)OPERATOR::GREATERTHAN },
            { "if"s,          (int)CONDITIONAL::IF       },
            { "elseif"s,      (int)CONDITIONAL::ELSEIF   },
            { "else"s,        (int)CONDITIONAL::ELSE     }
        };

        auto r = ga::Parser::ParseJSON("scripts/enemy.json").obj;
        for (auto& obj : r.objs) {
            // Parse each enemy into a set of parameters
            int index = toInt(obj.first);
            std::string name = obj.second["name"].val;
            this->enemyToInt[name] = index;

            /**
             * EnemyParams {
             *      std::vector<Conditional> conditionalBehaviours;
             *      std::vector<Behaviour> staticBehaviours;
             *      ga::Sprite* sprite;
             *      std::vector<AnimationParams> ap;
             *      int defaultAnimation;
             *      int x, y;
             * };
             */
            EnemyParams ep;
            if (obj.second.has("init")) {
                auto& init = obj.second["init"];
                if (init.has("appearance")) {
                    auto& appearance = init["appearance"];
                    if (appearance.has("sprite")) {
                        if (appearance.has("textureRectangle")) {
                            auto& texCoords = appearance["textureRectangle"];
                            std::string spriteFile = appearance["sprite"].val;
                            if (textures.find(spriteFile) == textures.end()) {
                                textures[spriteFile] = new ga::Texture("assets/images/"s + spriteFile);
                            }
                            int textureWidth  = textures[spriteFile]->getWidth();
                            int textureHeight = textures[spriteFile]->getHeight();
                            int s_left        = texCoords["left"].toInt();
                            int s_top         = texCoords["top"].toInt();
                            int s_width       = texCoords["width"].toInt();
                            int s_height      = texCoords["height"].toInt();
                            int nRows         = textureHeight / s_height;
                            int nColumns      = textureWidth  / s_width;
                            ga::AnimationOptions opt {
                                .nFrames = nRows * nColumns, .nRows = nRows, .nColumns = nColumns,
                                .spriteWidth = s_width, .spriteHeight = s_height
                            };
                            if (this->sprites.find(spriteFile) == sprites.end()) {
                                sprites[spriteFile] = new ga::Sprite(textures[spriteFile], opt);
                                if (appearance.has("scale")) {
                                    auto& scale = appearance["scale"];
                                    sprites[spriteFile]->setScale(ga::Scale2D(scale["width"].toFloat(), scale["height"].toFloat()));
                                }
                            }

                            // SPRITE SET HERE
                            ep.sprite = sprites[spriteFile];
                        }
                    }
                }
                if (init.has("position")) {
                    // X, Y SET HERE
                    ep.x = init["position"]["x"].toInt();
                    ep.y = init["position"]["y"].toInt();
                }
                if (init.has("animations")) {
                    auto animations = init["animations"].objs;
                    std::vector<AnimationParams> ap;
                    for (auto& animation : animations) {
                        int framesPerStep = animation.second["framesPerStep"].toInt();
                        std::vector<int> sequence;
                        for (auto& step : animation.second["path"].objs) {
                            sequence.push_back(step.second.toInt());
                        }
                        ap.push_back(AnimationParams{
                            .sequence = sequence, .framesPerStep = framesPerStep
                        });
                    }
                    ep.ap = ap;
                    if (init.has("defaultAnimation")) {
                        ep.defaultAnimation = init["defaultAnimation"].toInt();
                    }
                    else {
                        ep.defaultAnimation = 0;
                    }
                }
                else {
                    std::vector<AnimationParams> ap = {
                        { .sequence = { 0 }, .framesPerStep = 1 }
                    };
                    ep.ap = ap;
                }
            }
            if (obj.second.has("loop")) {
                if (obj.second["loop"].has("conditionals")) {
                    for (auto& c : obj.second["loop"]["conditionals"].objs) {
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
                        if (c.second.has("operator")) {
                            auto it = enums.find(c.second["operator"].val);
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
                            for (auto& behaviour : c.second["behaviour"].objs) {
                                if (behaviour.first.find("moveX") != std::string::npos) {
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::MOVEX, behaviour.second["x"].toInt() });
                                }
                                else if (behaviour.first.find("moveY") != std::string::npos) {
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::MOVEY, behaviour.second["y"].toInt() });
                                }
                                else if (behaviour.first.find("fire") != std::string::npos) {
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::FIRE, spellToInt[behaviour.second["spell"].val] });
                                }
                            }
                            /*
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
                            */
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
                        // CONDITIONAL BEHAVIOURS SET HERE
                        ep.conditionalBehaviours.emplace_back(Conditional{
                            .dependence = dependence, .conditional = conditional, .op = op,
                            .value = value, .value2 = value2, .behaviours = behaviours,
                        });
                    }
                }
            }
            this->enemyParams[index] = ep;
        }
    }

    void DanmakuTest::compileLevel() {
        auto spawns = ga::Parser::ParseJSON("scripts/level.json").obj;
        if (spawns.has("enemy_spawns")) {
            auto& enemy_spawns = spawns["enemy_spawns"];
            for (auto& s : enemy_spawns.objs) {
                int f = toInt(s.first);
                std::vector<EnemySpawnInfo> v;
                for (auto& e : s.second.objs) {
                    v.push_back({
                        enemyToInt[e.second["enemy"].val], e.second["position"]["x"].toInt(), e.second["position"]["y"].toInt()
                    });
                }
                this->enemySpawns[f] = v;
            }
        }
    }

    void DanmakuTest::compileSpells() {
        const static std::unordered_map<std::string, int> enums = {
            { "none",   (int)POSITION::NONE    },
            { "owner",  (int)POSITION::OWNER   },
            { "radial", (int)FORMATION::RADIAL }
        };
        fs::path p = fs::current_path();
        auto spellsJSON = ga::Parser::ParseJSON(p.string() + "/scripts/spells.json"s).obj;
        for (auto& spell : spellsJSON.objs) {
            this->spellToInt[spell.second["name"].val] = toInt(spell.first);
            int numBullets    = spell.second["number"].toInt();
            float speed       = spell.second["speed"].toFloat();
            int formation     = enums.find(spell.second["formation"].val)->second;
            int startPosition = enums.find(spell.second["startPosition"].val)->second;
            if (spell.second.has("appearance")) {
                auto& appearance = spell.second["appearance"];
                if (appearance.has("sprite")) {
                    if (appearance.has("textureRectangle")) {
                        auto& texCoords = appearance["textureRectangle"];
                        std::string spriteFile = appearance["sprite"].val;
                        int s_left = texCoords["left"].toInt();
                        int s_top = texCoords["top"].toInt();
                        int s_width = texCoords["width"].toInt();
                        int s_height = texCoords["height"].toInt();
                        ga::AnimationOptions opt {
                            .nFrames = 1, .nRows = 1, .nColumns = 1, .spriteWidth = s_width, .spriteHeight = s_height
                        };
                        if (this->textures.find(spriteFile) == textures.end()) {
                            textures[spriteFile] = new ga::Texture("assets/images/"s + spriteFile);
                            sprites[spriteFile] = new ga::Sprite(textures[spriteFile], opt);
                            if (appearance.has("scale")) {
                                auto& scale = appearance["scale"];
                                sprites[spriteFile]->setScale(ga::Scale2D(scale["width"].toFloat(), scale["height"].toFloat()));
                            }
                        }
                    }
                }
            }
            this->spellLibrary[spellToInt[spell.second["name"].val]] = SpellInfo{
                .name = spell.second["name"].val, .startingPosition = startPosition,
                .position = ga::Position2D<int>{ 0, 0 }, .formation = formation, .numBullets = numBullets,
                .speed = speed, .sprite = this->sprites[spell.second["appearance"]["sprite"].val], 
            };
        }
    }
}