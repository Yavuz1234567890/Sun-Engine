#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <main.h>
#include <rendering.h>
#include <scene_camera.h>

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void window_size_callback(GLFWwindow* window, int width, int height);
void OnClose(void);
void Update(void);
void InitializeEngine(void);
void InitializeGLFW(void);

int main()
{
	printf("hello world!");
	
    InitializeEngine();

    // loading Glad opengl
    if (!gladLoadGL()) {
        printf("glad loading failed");
        return -1;
    }
    
    float lastTime = glfwGetTime();

    /* main Loop */
    while (!glfwWindowShouldClose(window))
    {
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(.5, .5, .5, 1);
    
        RenderScene3D();
        Update();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

	return 0;
}

static void InitializeEngine(void)
{
    InitializeGLFW();
    InitializeCamera();
    InitRendering();
}

static void InitializeGLFW(void)
{
    /* Initialize the library */
    if (!glfwInit()) return -1;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    window = glfwCreateWindow(500, 300, "Sun Engine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //callbacks
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

static void Update(void)
{
    CameraTick();
    RenderScene3D();
}

// CALLBACKS
static void window_size_callback(GLFWwindow* window, int width, int height)
{
    Width = width; Height = height;
    glViewport(0, 0, width, height);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    MousePos[0] = (float)xpos;
    MousePos[1] = (float)xpos;
    glm_vec2_normalize(MousePos);
}

static void OnClose(void)
{
    glfwTerminate();
    glfwDestroyWindow(window);
}
