#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

static GLFWwindow* window;
static float deltaTime;
static int Width, Height;

static vec2 MousePos;
static vec3 dummy3;

#ifndef vec2size
#   define vec2size sizeof(float) * 2
#endif
#ifndef vec3size
#   define vec3size sizeof(float) * 3
#endif 
#ifndef vec4size
#   define vec4size sizeof(float) * 4
#endif

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
