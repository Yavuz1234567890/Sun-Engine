#pragma once
#ifndef RENDERING_H
#define RENDERING_H

#include <stdio.h>
#include <glad/glad.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#ifndef vertexSize
#	define vertexSize sizeof(float) * 8 // texcoords 2 + normals 3 + positions 3
#endif 

extern void RenderScene3D(void);
extern void InitRendering(void);

typedef struct Mesh
{
	unsigned int vaoID;
	unsigned int vboID;
	unsigned int uvID;
	unsigned int normalID;
	unsigned int eboID;
	size_t numIndices;
	size_t* indexData;
};

static void disposeMesh(const struct Mesh* mesh)
{
	glDeleteVertexArrays(1, &mesh->vaoID);
	glDeleteBuffers(1, &mesh->vboID);
	glDeleteBuffers(1, &mesh->uvID);
	glDeleteBuffers(1, &mesh->normalID);
	glDeleteBuffers(1, &mesh->eboID);
}

struct Mesh* CreateMesh(const char* path);
unsigned int CreateShader(const char* vertexPath, const char* fragmentPath);

#endif // !RENDERING_H
