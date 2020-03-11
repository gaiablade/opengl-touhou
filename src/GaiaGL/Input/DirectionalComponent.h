/*
 * DirectionalComponent.h
 * Author: Caleb Geyer
 * Description: Callback interface for directional input.
 */
#pragma once
#include <iostream>
#include <functional>

namespace ga {
    /*
     * DirectionalComponent Class: Callback interface for directional input.
     * Type: Standalone.
     */
    class DirectionalComponent {
        private:
        public:
            DirectionalComponent();
            ~DirectionalComponent();
            void update();
            std::function<void(uint32_t)> callback;
    };
};
