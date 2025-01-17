#include <iostream>              
#include <glad/glad.h>
#include <glfw3.h>  
#include "Input/Input.h"

#include "Scene/TestScene.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(800, 800, "Graal on Graal", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // control fps
    glfwSwapInterval(0);

    float last_frame_time = 0;
    float delta_time = 0;

    bool is_scene_running = false;


    Input::set_window(window);
    TestScene scene(window);
    scene.init();

    glEnable(GL_DEPTH_TEST); 

    while (!glfwWindowShouldClose(window)) {

        delta_time = (float)glfwGetTime() - last_frame_time;
        last_frame_time = (float)glfwGetTime();

        if (scene.is_running == false) {
            scene.ready();
        }
        scene.update(delta_time);    

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
