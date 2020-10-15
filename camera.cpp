#include "graphics.h"
#include <iostream>
#include "fpsCamera.h"

void graphics::camera::update()
{
    currentCamera.cameraUp = glm::normalize(graphics::rotateVector(glm::radians(currentCamera.cameraRoll), currentCamera.cameraUp, currentCamera.cameraFront));
    graphics::currentCamera.cameraRoll = 0.0f;
    currentCamera.cameraView = glm::lookAt(currentCamera.cameraPos, currentCamera.cameraPos + currentCamera.cameraFront, currentCamera.cameraUp);
    viewMatrix = currentCamera.cameraView;
    //std::cout << currentCamera.cameraFront.x << currentCamera.cameraFront.y << currentCamera.cameraFront.z << std::endl;
}
