#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fpsCamera
{
    extern float lastX;
    extern float lastY;
    extern bool firstMouse;

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void processInput(GLFWwindow* window);
}
