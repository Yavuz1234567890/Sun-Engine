#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>
#include <glad/glad.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

void RenderScene3D();
void InitRendering();
void ClearRendering();

struct Mesh
{
	unsigned int vaoID;
	unsigned int vboID; // < for disposing or if we recreate vertex it can be useful
	unsigned int eboID;
	unsigned int numVertices;
	unsigned int numIndices;
	void* vertexData;
	void* indexData;
};

struct Mesh* CreateMesh(const char* path);
unsigned int CreateShader(const char* vertexPath, const char* fragmentPath);

#endif // !RENDERING_H
