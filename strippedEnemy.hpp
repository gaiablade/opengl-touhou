#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <GaiaGL/System.h>
#include "Parse.hpp"

namespace th {

    enum class ACTION {
        NONE = 0, MOVEX, MOVEY, FIRE
    };
    
    enum class COMPARE {
        NONE = 0, EQUAL, NOTEQUAL, LESSTHAN, GREATERTHAN, BETWEEN, ELSE
    };

    enum class DEPEND {
        NONE = 0, FRAME
    };

    struct Behaviour {
        int action, value;
    };

    struct Conditional {
        int dependence, condition, value, value2;
        std::vector<Behaviour> behaviours;
    };

    class Enemy {
        public:
        Enemy(jsonObj& obj);
        Enemy(const Enemy& old_obj);
        ~Enemy();
        void compileBehaviours(jsonObj& obj);
        void loop();
        bool isTrue(int dependence, int condition, int value, int value2 = 0);
        void perform(Behaviour& behaviour);

        uint64_t frame;
        std::vector<Conditional> conditionalBehvaiours;
        std::vector<Behaviour> staticBehaviours;
        bool passed = false;
        int posX, posY;
    };

}