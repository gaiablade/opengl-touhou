#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <GaiaGL/Graphics.h>
#include "Parse.hpp"
#include "Spell.hpp"

namespace th {

    enum class ACTION {
        NONE = 0, MOVEX, MOVEY, FIRE
    };
    
    enum class OPERATOR {
        NONE = 0, EQUAL, NOTEQUAL, LESSTHAN, GREATERTHAN, BETWEEN
    };

    enum class CONDITIONAL {
        NONE = 0, IF, ELSE, ELSEIF
    };

    enum class DEPEND {
        NONE = 0, FRAME
    };

    struct Behaviour {
        int action, value;
    };

    struct Conditional {
        int dependence, conditional, op, value, value2;
        std::vector<Behaviour> behaviours;
    };

    struct AnimationParams {
        std::vector<int> sequence;
        int framesPerStep;
    };

    struct EnemyParams {
        std::vector<Conditional> conditionalBehaviours;
        std::vector<Behaviour> staticBehaviours;
        ga::Sprite* sprite;
        std::vector<AnimationParams> ap;
        int defaultAnimation;
        int x, y;
        //int left, top, width, height;
    };

    struct EnemySpawnInfo {
        int index, x, y;
    };

    class Enemy {
        public:
        Enemy(jsonObj& obj, std::map<std::string, ga::Texture*>& textures, ga::Size2D windowSize);
        Enemy(EnemyParams* params);
        Enemy(const Enemy& old_obj);
        ~Enemy();
        void compileBehaviours(jsonObj& obj);
        void loop();
        void render(ga::Window& window);
        bool isTrue(int dependence, int condition, int op, int value, int value2 = 0);
        void perform(Behaviour& behaviour);

        ga::Sprite* sprite;
        uint64_t frame;
        std::vector<Conditional> conditionalBehvaiours;
        std::vector<Behaviour> staticBehaviours;
        ga::Position2D<float> position;
        int polledSpell = -1;
        int passed = 0;
        int currentAnimation = 0;
        std::vector<AnimationParams> ap;
        int currentFrame = 0;
    };

}