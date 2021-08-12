#pragma once
#ifndef SCENE_CAMERA_H
#define SCENE_CAMERA_H

#include <main.h>

static vec3 camPosition = { 0,0,0 };
static vec3 camRight = { 0,0,0 };
static vec3 camFront = { 0,0,0 };
static vec3 camUp = { 0,0,0 };

static mat4 view = GLM_MAT4_IDENTITY_INIT;
static mat4 proj = GLM_MAT4_IDENTITY_INIT;

static const vec3 worldUP = { 0,1,0 };

static float MovementSpeed = 2;
static float MouseSensitivity = 15;
static float fov = 90;

extern void InitializeCamera(void);
extern void CameraTick(void);

#endif // !SCENE_CAMERA_H
