#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include "Parse.hpp"
#include "State.hpp"
#include "Enemy.hpp"

namespace th {
    class DanmakuTest : public State {
        public:
        DanmakuTest(int width, int height);
        ~DanmakuTest();
        void render(ga::Window& window) override;
        void update(ga::Window& window) override;
        private:
        ga::ColorRect background;
        ga::ColorRect bar;
        std::map<std::string, ga::Texture*> textures;
        std::map<std::string, ga::Sprite*> sprites;
        std::map<int, std::vector<EnemySpawnInfo>> enemySpawns;
        std::map<int, EnemyParams> enemyParams;
        std::map<std::string, int> enemyToInt;
        std::vector<Enemy*> enemies;
        jsonObj spells;
        int frame;
    };
}