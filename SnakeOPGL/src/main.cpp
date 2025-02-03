#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.h"

void ProcessInput(GLFWwindow* window, Game& game);

const float SCREEN_WIDTH = 800;
const float SCREEN_HEIGHT = 600;

float lastFrame = 0.0f;
float curFrame = 0.0f;
float deltaTime = 0.0f;
int main() {
    //initialisation de GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    //cr�ation de la fen�tre
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SnakeOPGL", NULL, NULL);

    Game game(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //initialisation de GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    game.Init();
    while (!glfwWindowShouldClose(window)) 
    {
        curFrame = glfwGetTime();
        deltaTime = curFrame - lastFrame;
        lastFrame = curFrame;
        ProcessInput(window,game);
        game.ProcessInput();
        glClearColor(0.25f, 0.25f, 0.25f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Update(deltaTime);
        game.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window, Game& game) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        game.keys[GLFW_KEY_A] = true;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        game.keys[GLFW_KEY_D] = true;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        game.keys[GLFW_KEY_W] = true;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        game.keys[GLFW_KEY_S] = true;


    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
        game.keys[GLFW_KEY_A] = false;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
        game.keys[GLFW_KEY_D] = false;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
        game.keys[GLFW_KEY_W] = false;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
        game.keys[GLFW_KEY_S] = false;
}