#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <filesystem>
#include <irrKlang.h>
#include "State.hpp"
#include "Enemy.hpp"
#include "Spell.hpp"
#include "Player.hpp"

namespace ik = irrklang;

namespace fs = std::filesystem;

namespace th {
    class DanmakuTest : public State {
        public:
        DanmakuTest(int width, int height, ga::Window* window);
        ~DanmakuTest();
        void render(ga::Window& window) override;
        void update(ga::Window& window) override;

        void compileEnemies();
        void compileLevel();
        void compileSpells();
        void compilePlayer();

        private:
        Player player;
        ga::ColorRect background;
        ga::ColorRect bar;
        std::map<std::string, ga::Texture*> textures;
        std::map<std::string, ga::Sprite*> sprites;
        std::map<int, std::vector<EnemySpawnInfo>> enemySpawns;
        std::map<int, EnemyParams> enemyParams;
        std::map<std::string, int> enemyToInt;
        std::map<int, SpellInfo> spellLibrary;
        std::vector<Spell> spells;
        std::map<std::string, int> spellToInt;
        std::vector<Enemy*> enemies;
        ga::jsonObj spellsJSON;
        int frame;
        ga::Window* window;
        ik::ISoundEngine* soundEngine;
    };
}