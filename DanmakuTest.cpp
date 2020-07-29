#include "DanmakuTest.hpp"

using namespace std::string_literals;

// Move elsewhere?
struct textureRectangle {
    int left = 0, top = 0, width = 0, height = 0;
};

// Move to GaiaGL??
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
        // TODO: Move soundengine generation elsewhere and pass pointer along
        this->soundEngine = ik::createIrrKlangDevice();
        //soundEngine->play2D("assets/music/bucket.ogg", true);

        // Reminder, status = 0 means not finished, status = 1 means finished
        this->status = 0;
        this->frame = 0;

        // Will eventually change when background is not just a colored rectangle
        background.setPosition(ga::Position2D<float>(width/2, height/2));
        bar.setPosition(ga::Position2D<float>(width - bar.getWidth()/2, height/2));

        compileSpells();
        compileEnemies();
        compileLevel();
        compilePlayer();
    }

    DanmakuTest::~DanmakuTest() {
        // Delete enemies first
        for (auto& e: enemies) {
            delete e;
        }
        this->enemies.clear();

        // Delete sprites second
        for (auto& s : sprites) {
            delete s.second;
        }

        // Delete textures last
        for (auto& p : this->textures) {
            delete p.second;
        }
        soundEngine->drop();
    }

    void DanmakuTest::render(ga::Window& window) {
        // Layer 1: Background
        window.getRenderer().Draw(background);

        // Layer 2: Enemies
        for (auto& e : this->enemies) {
            e->render(window);
        }

        // Layer 3: Player
        this->player.render(window);

        // Layer 4: Spells
        for (auto& s : this->spells) {
            s.render(window);
        }

        // Layer 5: Stat bar
        window.getRenderer().Draw(bar);
    }

    // This function is run every frame and updates all the components in the state
    void DanmakuTest::update(ga::Window& window) {
        // Check keyboard input
        updateInput();

        // Update player movement and other properties
        player.update();

        // Spawn enemies based on frame
        const auto it = enemySpawns.find(frame);
        if (it != enemySpawns.end()) {
            for (auto e : it->second) {
                this->enemies.push_back(new Enemy(&this->enemyParams[e.index]));
                this->enemies.back()->position.x = e.x;
                this->enemies.back()->position.y = e.y;
            }
        }

        // Cast spells based on enemies' frame
        for (auto& e : enemies) {
            e->loop();
            if (e->polledSpell.spell != -1) {
                this->spells.emplace_back(Spell(this->spellLibrary[e->polledSpell.spell], e->position, e->polledSpell.rotation));
                e->polledSpell.spell = -1;
            }
        }

        // Update spells
        spells.remove_if([&](Spell& spell) {
            spell.update();
            return spell.empty;
        });

        // Check collisions
        for (auto& spell : this->spells) {
            for (auto& bullet : spell.bullets) {
                if (player.coll.isColliding(bullet.coll)) {
                    // COLLISION DETECTED, DEFINE BEHAVIOUR HERE
                    player.sprite->setColor(ga::Color(0.0f, 1.0f, 1.0f, 1.0f));
                }
            }
        }

        frame++;
    }

    void DanmakuTest::updateInput() {
        bool keys[] = {
            ga::Input::IsKeyPressed(GA_KEY_LEFT, *this->window),
            ga::Input::IsKeyPressed(GA_KEY_RIGHT, *this->window),
            ga::Input::IsKeyPressed(GA_KEY_DOWN, *this->window),
            ga::Input::IsKeyPressed(GA_KEY_UP, *this->window)
        };
        if (keys[0]) {
            this->player.position.x -= 2;
        }
        if (keys[1]) {
            this->player.position.x += 2;
        }
        if (keys[2]) {
            this->player.position.y += 2;
        }
        if (keys[3]) {
            this->player.position.y -= 2;
        }
    }

    // Iterate through enemies in enemy script and add the defined parameters to
    // the list of all enemy parameters
    void DanmakuTest::compileEnemies() {
        // Use a hash-map to replicate functionality of a switch block with strings
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
        for (auto& [key, obj] : r.objs) {
            // Parse each enemy into a set of parameters
            // Get index of enemy
            int index = toInt(key);

            // Get enemy name (e.g. red-orb)
            std::string name = obj["name"].val;

            // Set index in name lookup table
            this->enemyToInt[name] = index;

            EnemyParams ep;
            // Enemy appearance (sprite and animations)
            if (obj.has("init") && obj["init"].has("appearance")) {
                auto& appearance = obj["init"]["appearance"];
                if (appearance.has("sprite")) {
                    std::string spriteFile = appearance["sprite"].val;
                    if (appearance.has("textureRectangle")) {
                        auto& texCoords = appearance["textureRectangle"];
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
                    else {
                        if (textures.find(spriteFile) == textures.end()) {
                            textures[spriteFile] = new ga::Texture("assets/images/"s + spriteFile);
                            sprites[spriteFile]  = new ga::Sprite(textures[spriteFile]);
                        }
                    }
                }
                else {
                    std::cout << "Enemy at index " << index << " has no defined texture/sprite!\n";
                    exit(1);
                }
            }
            if (obj.has("init") && obj["init"].has("position")) {
                // X, Y SET HERE
                ep.x = obj["init"]["position"]["x"].toInt();
                ep.y = obj["init"]["position"]["y"].toInt();
            }
            if (obj.has("init") && obj["init"].has("animations")) {
                auto animations = obj["init"]["animations"].objs;
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
                if (obj["init"].has("defaultAnimation")) {
                    ep.defaultAnimation = obj["init"]["defaultAnimation"].toInt();
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
            if (obj.has("loop") && obj["loop"].has("conditionals")) {
                for (auto& [key, condition] : obj["loop"]["conditionals"].objs) {
                    int dependence, conditional, op, value, value2;
                    std::vector<Behaviour> behaviours;
                    if (condition.has("dependence")) {
                        auto it = enums.find(condition["dependence"].val);
                        if (it != enums.end()) {
                            dependence = it->second;
                        }
                        else dependence = (int)DEPEND::FRAME;
                    }
                    else {
                        dependence = (int)DEPEND::FRAME;
                    }
                    if (condition.has("operator")) {
                        auto it = enums.find(condition["operator"].val);
                        if (it != enums.end()) {
                            op = it->second;
                        }
                        else op = (int)OPERATOR::EQUAL;
                    }
                    else {
                        op = (int)OPERATOR::EQUAL;
                    }
                    if (condition.has("value")) {
                        value = condition["value"].toInt();
                    }
                    else {
                        value = 0;
                    }
                    if (condition.has("value2")) {
                        value2 = condition["value2"].toInt();
                    }
                    else {
                        value2 = 0;
                    }
                    if (condition.has("behaviour")) {
                        for (auto& [key, behaviour] : condition["behaviour"].objs) {
                            if (key.find("moveX") != std::string::npos) {
                                behaviours.emplace_back(Behaviour{ (int)ACTION::MOVEX, { behaviour["x"].toInt() }});
                            }
                            else if (key.find("moveY") != std::string::npos) {
                                behaviours.emplace_back(Behaviour{ (int)ACTION::MOVEY, { behaviour["y"].toInt() }});
                            }
                            else if (key.find("fire") != std::string::npos) {
                                if (behaviour.has("rotate")) {
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::FIRE, { spellToInt[behaviour["spell"].val], behaviour["rotate"].toInt() }});
                                }
                                else {
                                    behaviours.emplace_back(Behaviour{ (int)ACTION::FIRE, { spellToInt[behaviour["spell"].val], 0 }});
                                }
                            }
                        }
                    }
                    if (condition.has("conditional")) {
                        auto it = enums.find(condition["conditional"].val);
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
            { "none",      (int)POSITION::NONE    },
            { "owner",     (int)POSITION::OWNER   },
            { "radial",    (int)FORMATION::RADIAL },
            { "whirlpool", (int)FORMATION::WHIRLPOOL }
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

    void DanmakuTest::compilePlayer() {
        auto playerObj = ga::Parser::ParseJSON("scripts/player.json").obj;
        if (playerObj.has("appearance")) {
            if (playerObj["appearance"].has("sprite")) {
                const std::string filepath = playerObj["appearance"]["sprite"].val;
                if (this->textures.find(filepath) == textures.end()) {
                    textures[filepath] = new ga::Texture("assets/images/"s + filepath);
                    sprites[filepath]  = new ga::Sprite(textures[filepath]);
                }
                this->player.sprite = sprites[filepath];
                if (playerObj["appearance"].has("scale")) {
                    this->player.sprite->setScale(ga::Scale2D(playerObj["appearance"]["scale"]["width"].toFloat(), playerObj["appearance"]["scale"]["height"].toFloat()));
                }
            }
        }
        this->player.position      = ga::Position2D<float>(400.0f, 400.0f);
        this->player.coll.position = player.position;
        this->player.coll.setRotation(ga::Rotation2D(0));
    }
}