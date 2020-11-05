#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders/ShaderClass.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int initialTime = time(NULL), finalTime, fps = 0;

const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 480;

void FPS();

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Grid", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW::FAIL" << std::endl;

    Shader FirstShader("C:/Users/nahue/Desktop/OpenGL-Grid/Template/src/shaders/shader.vs", "C:/Users/nahue/Desktop/OpenGL-Grid/Template/src/shaders/shader.fs");

    glEnable(GL_DEPTH_TEST);
    
    float vertices[] = {
        -0.875f, -0.875f,
         0.875f, -0.875f,

        -0.875f, -0.750f,
         0.875f, -0.750f,

        -0.875f, -0.625f,
         0.875f, -0.625f,

        -0.875f, -0.625f,
         0.875f, -0.625f,

        -0.875f, -0.500f,
         0.875f, -0.500f,

        -0.875f, -0.375f,
         0.875f, -0.375f,

        -0.875f, -0.250f,
         0.875f, -0.250f,

        -0.875f, -0.125f,
         0.875f, -0.125f,

        -0.875f, 0.0f,
         0.875f, 0.0f,

         -0.875f, 0.875f,
         0.875f, 0.875f,

        -0.875f, 0.750f,
         0.875f, 0.750f,

        -0.875f, 0.625f,
         0.875f, 0.625f,

        -0.875f, 0.625f,
         0.875f, 0.625f,

        -0.875f, 0.500f,
         0.875f, 0.500f,

        -0.875f, 0.375f,
         0.875f, 0.375f,

        -0.875f, 0.250f,
         0.875f, 0.250f,

        -0.875f, 0.125f,
         0.875f, 0.125f,

        -0.875f, 0.0f,
         0.875f, 0.0f,

        -0.875f, -0.875f,
        -0.875f,  0.875f,

        -0.750f, -0.875f,
        -0.750f,  0.875f,

        -0.625f, -0.875f,
        -0.625f,  0.875f,

        -0.500f, -0.875f,
        -0.500f,  0.875f,

        -0.375f, -0.875f,
        -0.375f,  0.875f,

        -0.250f, -0.875f,
        -0.250f,  0.875f,

        -0.125f, -0.875f,
        -0.125f,  0.875f,

         0.0f, -0.875f,
         0.0f,  0.875f,

         0.875f, -0.875f,
         0.875f,  0.875f,

         0.750f, -0.875f,
         0.750f,  0.875f,

         0.625f, -0.875f,
         0.625f,  0.875f,

         0.500f, -0.875f,
         0.500f,  0.875f,

         0.375f, -0.875f,
         0.375f,  0.875f,

         0.250f, -0.875f,
         0.250f,  0.875f,

         0.125f, -0.875f,
         0.125f,  0.875f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glfwSwapInterval(0);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 pene = glm::mat4(10.f);
        pene = glm::rotate(pene, glm::radians(-70.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        pene = glm::rotate(pene, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        pene = glm::rotate(pene, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 view = glm::mat4(1.0f); 
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        FirstShader.setMat4("projection", projection); 
        FirstShader.setMat4("view", view);

        FirstShader.use();
        unsigned int salchicha = glGetUniformLocation(FirstShader.ID, "pene");
        glUniformMatrix4fv(salchicha, 1, GL_FALSE, glm::value_ptr(pene));
 
        glDrawArrays(GL_LINES, 0, 66);

        FPS();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void FPS()
{
    fps++;
    finalTime = time(NULL);
    if (finalTime - initialTime > 0)
    {
        std::cout << "FPS: " << fps << std::endl;
        fps = 0;
        initialTime = finalTime;
    }
}