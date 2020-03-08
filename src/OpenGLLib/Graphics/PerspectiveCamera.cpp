#include "PerspectiveCamera.h"

namespace ga {
    float PerspectiveCamera::sensitivity = 0.05f;
    float PerspectiveCamera::mouseXPos = 0.0f;
    float PerspectiveCamera::mouseYPos = 0.0f;

    PerspectiveCamera::PerspectiveCamera(const int cameraMode) 
        : cameraPos(0.0f, 0.0f, 3.0f),
        cameraFront(0.0f, 0.0f, -1.0f),
        cameraUp(0.0f, 1.0f, 0.0f),
        firstMouse(true), mouseLock(true), wireframe(false), spacePressed(false), yaw(-90.0f)
    {
        mode = cameraMode;
    }

    PerspectiveCamera::~PerspectiveCamera() {
    }

    void PerspectiveCamera::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates rance from bottom to top
        lastX = xpos;
        lastY = ypos;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }

    void PerspectiveCamera::updateCamera(GLFWwindow* window, float deltaTime) {
        // Keyboard input:
        float cameraSpeed = 7.5f * deltaTime;
        if (mode == MovementMode::WALK) {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                cameraPos += cameraSpeed * glm::vec3(cameraFront.x, 0.0f, cameraFront.z);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                cameraPos -= cameraSpeed * glm::vec3(cameraFront.x, 0.0f, cameraFront.z);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
                spacePressed = true;
                if (!wireframe) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    wireframe = true;
                }
                else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    wireframe = false;
                }
            }
            else {
                spacePressed = false;
            }
            if (firstMouse) {
                lastX = mouseXPos;
                lastY = mouseYPos;
                firstMouse = false;
            }
        }
        else {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                cameraPos += cameraSpeed * cameraFront;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                cameraPos -= cameraSpeed * cameraFront;
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
                spacePressed = true;
                if (!wireframe) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    wireframe = true;
                }
                else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    wireframe = false;
                }
            }
            else if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS) {
                spacePressed = false;
            }
            if (firstMouse) {
                lastX = mouseXPos;
                lastY = mouseYPos;
                firstMouse = false;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            if (mouseLock) {
                mouseLock = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else {
                mouseLock = true;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        }

        float xoffset = mouseXPos - lastX;
        float yoffset = lastY - mouseYPos; // reversed since y-coordinates rance from bottom to top
        lastX = mouseXPos;
        lastY = mouseYPos;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }

    glm::mat4 PerspectiveCamera::getLookAtMatrix() {
        return glm::lookAt(cameraPos, cameraPos + this->cameraFront, cameraUp);
    }

    void PerspectiveCamera::setPosition(const glm::vec3& position) {
        cameraPos = position;
    }
};
