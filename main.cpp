
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "graphics.h"
#include "fpsCamera.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //setup shaders
    glEnable(GL_DEPTH_TEST);
    int shaderProgram = graphics::renderer::buildShaderProgram("Shaders\\shaderA_vertex.shader", "Shaders\\shaderA_frag.shader");

    //setup game objects
    graphics::file_object obj("Buffer_Data\\vertices.txt", "Buffer_Data\\indices.txt", "Buffer_Data\\brick.jpg");
    obj.load();
    graphics::file_object obj2("Buffer_Data\\vertices.txt", "Buffer_Data\\indices.txt", "Buffer_Data\\brick.jpg");
    obj2.load();
    obj.modelMatrix = glm::rotate(obj.modelMatrix, glm::radians(-55.0f), glm::vec3(0.3f, 0.25f, 0.7f));
    obj.modelMatrix = glm::scale(obj.modelMatrix, glm::vec3(2.0f, 1.0f, 0.5f));
    obj2.modelMatrix = glm::rotate(obj2.modelMatrix, glm::radians(-22.0f), glm::vec3(0.1f, 0.15f, 0.9f));
    obj2.modelMatrix = glm::translate(obj2.modelMatrix, glm::vec3(2.0f, 0.5f, -3.0f));

    graphics::shape quad1;
    quad1.width = 1.5f;
    quad1.height = 0.5f;
    quad1.reload(graphics::shape::quad);
    graphics::shape_object obj3(&quad1, "Buffer_Data\\brick.jpg");
    obj3.loadTexture();
    obj3.reloadShape();
    obj3.modelMatrix = glm::translate(obj3.modelMatrix, glm::vec3(-2.0f, -0.5f, 3.0f));

    graphics::shape circle1;
    circle1.detail = 150;
    circle1.reload(graphics::shape::circle);
    graphics::shape_object obj4(&circle1, "Buffer_Data\\brick.jpg");
    obj4.loadTexture();
    obj4.reloadShape();
    obj4.modelMatrix = glm::translate(obj3.modelMatrix, glm::vec3(5.0f, 0.5f, 1.0f));

    graphics::shape sphere1;
    sphere1.detail = 3;
    sphere1.reload(graphics::shape::sphere);
    graphics::shape_object obj5(&sphere1, "Buffer_Data\\brick.jpg");
    obj5.loadTexture();
    obj5.reloadShape();
    obj5.modelMatrix = glm::translate(obj3.modelMatrix, glm::vec3(2.0f, 1.5f, 3.0f));

    graphics::shape sphere2;
    sphere2.geoSphereImageLoc = "Buffer_data\\world_elevation.jpg";
    sphere2.reload(graphics::shape::geoSphere);
    graphics::shape_object obj6(&sphere2, "Buffer_Data\\world_map_source.jpg");
    obj6.loadTexture();
    obj6.reloadShape();
    obj6.modelMatrix = glm::translate(obj3.modelMatrix, glm::vec3(5.0f, 2.0f, -3.0f));

    //setup camera
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, fpsCamera::mouse_callback);
    graphics::camera myCam;
    graphics::currentCamera = myCam;

    float xyz = 1.0f;
    float dir = -0.05f;

    float hag = 3;
    float hagB = 0.1;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        xyz += dir;
        if (xyz >= 3.0f || xyz <= 0.0f)
        {
            dir = -dir;
        }

        hag += hagB;
        if (hag > 50 || hag <=3)
        {
            hagB = -hagB;
        }

        // input and camera
        fpsCamera::processInput(window);
        graphics::currentCamera.update();

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        graphics::projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        graphics::renderer::render(obj, shaderProgram);
        graphics::renderer::render(obj2, shaderProgram);

        quad1.width = xyz;
        quad1.height = 3.0f-xyz;
        quad1.reload(graphics::shape::quad);
        obj3.reloadShape();
        graphics::renderer::render(obj3, shaderProgram);

        circle1.detail = (int)hag;
        circle1.reload(graphics::shape::circle);
        obj4.reloadShape();
        graphics::renderer::render(obj4, shaderProgram);

        sphere1.detail = (int)hag;
        sphere1.reload(graphics::shape::sphere);
        obj5.reloadShape();
        graphics::renderer::render(obj5, shaderProgram);

        graphics::renderer::render(obj6, shaderProgram);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------





