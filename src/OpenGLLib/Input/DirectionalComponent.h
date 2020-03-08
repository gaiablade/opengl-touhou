#pragma once
#include <iostream>
#include <functional>

namespace ga {
    class DirectionalComponent {
        private:
        public:
            DirectionalComponent();
            ~DirectionalComponent();
            void update();
            std::function<void(uint32_t)> callback;
    };
};
