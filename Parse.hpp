#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

namespace th {

    enum class JSTYPE { Val = 0, Obj = 1, Arr = 2 };

    struct jsonObj {
        JSTYPE type;
        std::string val;
        //std::vector<std::pair<std::string, jsonObj>> objs;
        std::map<std::string, jsonObj> objs;
        jsonObj& operator[] (const std::string& key) {
            return this->objs[key];
        }
        bool has(const std::string& key) {
            return this->objs.find(key) != this->objs.end();
        }
        int toInt() {
            std::stringstream ss(this->val);
            int result;
            ss >> result;
            if (ss.fail()) {
                ss.clear();
                return 0;
            }
            return result;
        }
        float toFloat() {
            std::stringstream ss(this->val);
            float result;
            ss >> result;
            if (ss.fail()) {
                ss.clear();
                return -1.0f;
            }
            return result;
        }
    };

    struct ParseResults {
        bool success;
        std::string errorMessage;
        jsonObj obj;
    };

    class Parser {
        public:
        static ParseResults ParseJSON(const std::string& filename);
        static void PrintJSON(jsonObj& obj, int indentation = 0);

        private:
        static void ParseObject(std::ifstream& in, jsonObj& obj);
        static void ParseArray(std::ifstream& in, jsonObj& obj, int index = 0);
        static bool removeChar(char character, std::string& str);
        static bool removeChars(const std::string& chars, std::string& str);
    };

}