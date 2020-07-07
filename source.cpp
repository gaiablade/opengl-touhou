#include <iostream>
#include <sstream>
#include "Touhou.hpp"
#include "Parse.hpp"

int main() {
    // Parse config file
    auto r = th::Parser::ParseJSON("config.json");
    if (!r.success) {
        std::cout << "Failed to parse config file..." << std::endl;
        return 1;
    }

    // Extract important parameters
    int width, height;
    const std::string& title = r.obj["title"].val;
    auto dimensions = r.obj["dimensions"];
    std::stringstream ss[2] = {
        std::stringstream(dimensions["width"].val),
        std::stringstream(dimensions["height"].val)
    };
    ss[0] >> width;
    ss[1] >> height;
    if (ss[0].fail() || ss[1].fail()) {
        std::cout << "Syntax Error in config.json: width and height must be integer numbers!\n";
        return 1;
    }

    // Start Game
    th::Game g(width, height, title);
    g.Run();
    return 0;
}