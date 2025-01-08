#include <iostream>
#include "GameObject.h"	 
#include "CharacterController.h"
#include "MyMath.h"	 	
#include "Transform.h"
#include "TestScene.h"
                
#include <glad/glad.h>
#include <glfw3.h>  
#include "Shader.h"	

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

    // control fps
    glfwSwapInterval(0);

    float last_frame_time = 0;
    float delta_time = 0;

    bool is_scene_running = false;

    float vertices[] = { 
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  -0.5f,
         0.5f,  0.5f,  -0.5f,
         0.5f, -0.5f,  -0.5f,
        -0.5f, -0.5f,  -0.5f,
    };


    unsigned int indices[] = {
        //FRONT
        0,1,2,
        0,2,3,

        //BACK
        4,7,6,
        6,5,4,

        //TOP  
        0,4,5,
        0,5,1,

        //BOTTOM
        3,6,7,
        3,2,6,

        //RIGHT
        1,5,6,
        1,6,2,

        //LEFT
        4,0,3,
        4,3,7,
    };

    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    Shader shader("Ressources/Shaders/default.shader");

    TestScene scene;
    scene.init();

    const double pi = 3.14159265358979323846;

    //glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        // GAME LOGIC
        if (scene.is_running == false) {
            scene.ready();
        }

        delta_time = (float)glfwGetTime() - last_frame_time;
        last_frame_time = (float)glfwGetTime();

        scene.update(delta_time);    

        Mat4f scale(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

        float angle = (float)glfwGetTime() * 60;
        float angle_rad = angle * (float)pi / 180.0f;
        Mat4f rotation (
            std::cos(angle_rad), 0.0f, -std::sin(angle_rad), 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            std::sin(angle_rad), 0.0f, std::cos(angle_rad), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

        Mat4f translation (
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

        Mat4f model = translation * rotation * scale;

        float l = -1, r = 1;
        float t = -1, b = 1;

        float deg_fov = 90.0f;

        float rad_fov = ((deg_fov * 0.5f) * (float)pi) / 180.0f;
        float tan_fov = std::tanf(rad_fov);
        float d = 1.0f / tan_fov;

        Mat4f perspective(
            d   , 0.0f, 0.0f, 0.0f,
            0.0f, d   , 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f);

        Mat4f orthographic(
            2.0f / (r - l), 0.0f, 0.0f, -(r + l) / (r - l),
            0.0f, 2.0f / (t - b), 0.0f, -(t + b) / (t - b),
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);


        Mat4f mvp = translation;// perspective* model;

        // RENDER
        shader.use();
        shader.set_mat4("mvp", mvp.m);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}