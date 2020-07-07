#include "Parse.hpp"

namespace th {
    ParseResults Parser::ParseJSON(const std::string& filename) {
        std::ifstream in = std::ifstream(filename);
        if (in.fail()) {
            return {
                .success = false, .errorMessage = "File Error: Could not open file!\n"
            };
        }
        std::string s;
        in >> s;
        if (s != "{") {
            return {
                .success = false, .errorMessage = "Syntax Error: Line 1 must start with '{'!\n"
            };
        }
        jsonObj rootObj = {
            .type = JSTYPE::Obj
        };
        ParseObject(in, rootObj);
        in.close();
        ParseResults res{ true, "", rootObj };
        return res;
    }

    void Parser::ParseObject(std::ifstream& in, jsonObj& obj) {
        std::string s;
        while (in >> s && removeChar(',', s) && s != "}") {
            removeChars("\":", s);
            std::string key = s;
            char c = ' ';
            while (c == ' ') {
                in.read(&c, 1);
            }
            if (c == '{') {
                obj.objs.insert(std::pair<std::string, jsonObj>(key, jsonObj{ .type = JSTYPE::Obj }));
                ParseObject(in, obj.objs[key]);
            }
            else if (c == '[') {
                obj.objs.insert(std::pair<std::string, jsonObj>(key, jsonObj{ .type = JSTYPE::Arr }));
                ParseArray(in, obj.objs[key]);
            }
            else { // value
                std::getline(in, s);
                removeChars("\",", s);
                std::string val = s;
                obj.objs.insert(std::pair<std::string, jsonObj>(key, jsonObj{ .type = JSTYPE::Val, .val = val }));
            }
        }
    }

    void Parser::ParseArray(std::ifstream& in, jsonObj& obj, int index) {
        std::string s;
        while (in >> s && removeChar(',', s) && s != "]") {
            removeChars("\":", s);
            /*
            std::string key = s;
            */
            std::stringstream ss;
            ss << index;
            std::string key = ss.str();
            /*
            char c = ' ';
            while (c == ' ') {
                in.read(&c, 1);
            }
            */
            //if (c == '{') {
            if (s == "{") {
                obj.objs.insert(std::pair<std::string, jsonObj>(key, jsonObj{ .type = JSTYPE::Obj }));
                ParseObject(in, obj.objs[key]);
            }
            //else if (c == '[') {
            else if (s == "[") {
                obj.objs.insert(std::pair<std::string, jsonObj>(key, jsonObj{ .type = JSTYPE::Arr }));
                ParseArray(in, obj.objs[key]);
            }
            else { // value
            /*
                std::getline(in, s);
                */
                removeChars("\",", s);
                std::string val = s;
                obj.objs.insert(std::pair<std::string, jsonObj>(key, jsonObj{ .type = JSTYPE::Val, .val = val }));
            }
            index++;
        }
    }

    bool Parser::removeChar(char character, std::string& str) {
        str.erase(std::remove(str.begin(), str.end(), character), str.end()); //remove A from string
        return true;
    }

    bool Parser::removeChars(const std::string& chars, std::string& str) {
        for (const auto& c : chars) {
            str.erase(std::remove(str.begin(), str.end(), c), str.end()); //remove A from string
        }
        return true;
    }

    void Parser::PrintJSON(jsonObj& obj, int indentation) {
        for (auto& r : obj.objs) {
            for (int i = 0; i < indentation; i++) {
                std::cout << "  ";
            }
            std::cout << r.first << ": ";
            if (r.second.type == JSTYPE::Val) {
                std::cout << r.second.val << '\n';
            }
            else if (r.second.type == JSTYPE::Arr) {
                std::cout << "[\n";
                PrintJSON(r.second, indentation + 1);
                for (int i = 0; i < indentation; i++) {
                    std::cout << "  ";
                }
                std::cout << "]\n";
            }
            else {
                std::cout << "{\n";
                PrintJSON(r.second, indentation + 1);
                for (int i = 0; i < indentation; i++) {
                    std::cout << "  ";
                }
                std::cout << "}\n";
            }
        }
    }

}