#include "Engine.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "Scene/Scene.h"
#include "Input/Input.h"

Engine::Engine() : scene(nullptr), window(nullptr), frame_time(1.0f/60), last_frame_time(0), delta_time(0) {

}

Engine::~Engine() {

}

bool Engine::init() {
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 800, "Graal on Graal", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // control fps
    glfwSwapInterval(0);


    Input::set_window(window);

    glEnable(GL_DEPTH_TEST);

    return true;
}

void Engine::load_scene(Scene* _scene) {
	this->scene = _scene;

    this->scene->set_window(this->window);

    this->scene->init();
}

void Engine::run() {
    while (!glfwWindowShouldClose(window)) {

        float current_time = (float)glfwGetTime();
        if (current_time - last_frame_time >= frame_time) {

            glfwPollEvents();

            delta_time = current_time - last_frame_time;
            last_frame_time = current_time;

            if (scene->is_running == false) {
                scene->ready();
            }

            scene->update(delta_time);

            glfwSwapBuffers(window);
        }
    }

    glfwTerminate();
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Engine::set_max_fps(int fps) {
    this->frame_time = 1.0f / fps;
}