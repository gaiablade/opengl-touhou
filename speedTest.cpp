#include "strippedEnemy.hpp"

int main() {
    auto p = th::Parser::ParseJSON("scripts/enemy1.json");
    th::Enemy e = th::Enemy(p.obj);
    while (true) {
        e.loop();
    }
    return 0;
}