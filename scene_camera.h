#ifndef SCENE_CAMERA_H
#define SCENE_CAMERA_H

#include <cglm.h>
#include <main.h>

vec3 camPosition = { 0,0,0 }, camRight = { 0,0,0 }, camFront = { 0,0,0 }, camUp = {0,0,0};
mat4 view, proj = { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };

static const vec3 worldUP = { 0,1,0 };

static float MovementSpeed = 2;
static float MouseSensitivity = 15;
static float fov = 90;

static void InitializeCamera()

#endif // !SCENE_CAMERA_H
