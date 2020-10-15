#include "fpsCamera.h"

#include "graphics.h"
#include <iostream>

namespace fpsCamera
{
    float lastX = 400;
    float lastY = 300;
    bool firstMouse = true;

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        
        graphics::currentCamera.cameraYaw += xoffset;
        graphics::currentCamera.cameraPitch += yoffset;

        if (graphics::currentCamera.cameraPitch > 89.0f)
            graphics::currentCamera.cameraPitch = 89.0f;
        if (graphics::currentCamera.cameraPitch < -89.0f)
            graphics::currentCamera.cameraPitch = -89.0f;

        /*
        glm::vec3 direction;
        direction.x = cos(glm::radians(graphics::currentCamera.cameraYaw)) * cos(glm::radians(graphics::currentCamera.cameraPitch));
        direction.y = sin(glm::radians(graphics::currentCamera.cameraPitch));
        direction.z = sin(glm::radians(graphics::currentCamera.cameraYaw)) * cos(glm::radians(graphics::currentCamera.cameraPitch));
        graphics::currentCamera.cameraFront = glm::normalize(direction);
        */
        

        glm::vec3 front = graphics::currentCamera.cameraFront;
        glm::vec3 up = graphics::currentCamera.cameraUp;
        front = graphics::rotateVector(glm::radians(1.0f * -xoffset), front, up);
        glm::vec3 right = glm::normalize(glm::cross(front, up));
        front = graphics::rotateVector(glm::radians(1.0f * yoffset), front, right);
        graphics::currentCamera.cameraFront = glm::normalize(front);
        up = glm::normalize(glm::cross(right, front));
        graphics::currentCamera.cameraUp = glm::normalize(up);
    }

    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        const float cameraSpeed = 0.05f; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            graphics::currentCamera.cameraPos += cameraSpeed * graphics::currentCamera.cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            graphics::currentCamera.cameraPos -= cameraSpeed * graphics::currentCamera.cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            graphics::currentCamera.cameraPos -= glm::normalize(glm::cross(graphics::currentCamera.cameraFront, graphics::currentCamera.cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            graphics::currentCamera.cameraPos += glm::normalize(glm::cross(graphics::currentCamera.cameraFront, graphics::currentCamera.cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            graphics::currentCamera.cameraPos += glm::normalize(glm::cross(glm::cross(graphics::currentCamera.cameraFront, graphics::currentCamera.cameraUp), graphics::currentCamera.cameraFront)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
            graphics::currentCamera.cameraPos -= glm::normalize(glm::cross(glm::cross(graphics::currentCamera.cameraFront, graphics::currentCamera.cameraUp), graphics::currentCamera.cameraFront)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            graphics::currentCamera.cameraRoll += cameraSpeed * 25.0f;
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            graphics::currentCamera.cameraRoll -= cameraSpeed * 25.0f;
    }
}