#ifndef MAIN_H
#define MAIN_H

#include <GLFW/glfw3.h>
#include <cglm.h>

GLFWwindow* window;
float deltaTime;
int Width, Height;

vec2 MousePos;
vec3 dummy3;

static bool getMouseDown(const int* button)
{
    return glfwGetMouseButton(window, button) == GLFW_KEY_DOWN;
}

static bool getMouseUp(const int* button)
{
    return glfwGetMouseButton(window, button) == GLFW_KEY_UP;
}

static bool getKeyUp(const int* key)
{
    return glfwGetKey(window, key) == GLFW_KEY_UP;
}

static bool getKeyDown(const int* key)
{
    return glfwGetKey(window, key) == GLFW_KEY_DOWN;
}

#endif // !MAIN_H
