/*
 * PerspectiveCamera.h
 * Author: Caleb Geyer
 * Description: Perspective 3D Camera
 */
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLCall.h"

namespace ga {
    enum MovementMode { WALK, FLY };

    /*
     * PerspectiveCamera Class: 3D Perspective Camera.
     * Type: Standalone.
     */
    class PerspectiveCamera {
        public:
            PerspectiveCamera(const int cameraMode);
            ~PerspectiveCamera();
            void mouseCallback(GLFWwindow* window, double xpos, double ypos);
            void updateCamera(GLFWwindow* window, float deltaTime);
            glm::mat4 getLookAtMatrix();
            void setPosition(const glm::vec3& position);
        private:
            glm::vec3 cameraPos, cameraFront, cameraUp;
            float yaw, pitch;
            float lastX, lastY;
            float deltaTime, lastFrame;
            bool firstMouse;
            int mode;
            bool wireframe;
            bool mouseLock;
            bool spacePressed;
        public:
            static float sensitivity;
            static float mouseXPos;
            static float mouseYPos;
    };
};
