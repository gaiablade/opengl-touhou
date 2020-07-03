#include <iostream>
#include <functional>

int main() {
    int value = 50;
    int frame = 60;
    auto greaterthan = [&](){ if (frame > value) return true; return false; };
    std::function<bool()> ptr = greaterthan;
    if (ptr()) {
        std::cout << "True!\n";
        return 0;
    }
    std::cout << "False\n";
    return 1;
}