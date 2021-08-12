#pragma once

#include <rendering.h>
#include <assert.h>
#include <scene_camera.h>
#include <cglm/cglm.h>

//#pragma warning(disable : 6305)

static void Vec3ToVec2(struct aiVector2D* texCoords, struct aiVector3D* vec3Ptr, const int* vertexLenght);

static const C_STRUCT aiScene* scene = NULL;
static const struct Mesh* monkey = NULL;
static GLuint shader;

static GLuint modelLocation;
static GLuint viewLocation;
static GLuint projLocation;

extern void InitRendering(void)
{
	monkey = CreateMesh("../Sun Engine/Assets/Models/monkey.glb");
	shader = CreateShader("../Sun Engine/Assets/Shaders/shader.vert", "../Sun Engine/Assets/Shaders/shader.frag");

	glUseProgram(shader);
}

// we are combining mesh here it can be changed for future 
static struct Mesh* CreateMesh(const char* path)
{
	scene = aiImportFile(path, aiProcessPreset_TargetRealtime_Fast);
	
	printf("\n mesh loading");
	
	if (scene == NULL)
	{
		char message[100] = "scene is null maybe path wrong";
		printf(strcat(message, path));
		return NULL;
	}

	printf("\n scene loaded");

	unsigned long long i = 0;
	
	struct Mesh* mesh = (struct Mesh*)malloc(sizeof(struct Mesh));
	struct aiMesh* meshPtr = &scene->mMeshes[i];
	struct aiVector2D* texCoords = (struct aiVector2D*)malloc(vec2size * meshPtr->mNumVertices);
	
	mesh->numIndices = meshPtr->mNumFaces * 3;
	mesh->indexData = malloc(sizeof(int) * mesh->numIndices);

	printf("\n %i ", mesh->numIndices);

	const unsigned int faceSize = sizeof(int) * 3;

	for (; i < mesh->numIndices; i ++)
	{
		struct aiFace* face = &meshPtr->mFaces[i];
		memcpy(mesh->indexData + i * faceSize, face->mIndices, faceSize);
	}

	printf("\n indices loaded");

	// create buffers
	glGenVertexArrays(1, &mesh->vaoID);
	glBindVertexArray(mesh->vaoID);

	glGenBuffers(1, &mesh->vboID);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vboID);
	glBufferData(GL_ARRAY_BUFFER, mesh->vboID, meshPtr->mVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vec3size, NULL); // position

	glGenBuffers(1, &mesh->uvID);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->uvID);
	glBufferData(GL_ARRAY_BUFFER, mesh->uvID, texCoords, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE , vec2size, NULL); // texCoord

	glGenBuffers(1, &mesh->normalID);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->normalID);
	glBufferData(GL_ARRAY_BUFFER, mesh->normalID, meshPtr->mNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, vec3size, NULL); // normal

	glEnableVertexAttribArray(0); // position
	glEnableVertexAttribArray(1); // texCoord
	glEnableVertexAttribArray(2); // normal

	glGenBuffers(1, &mesh->eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mesh->numIndices, mesh->indexData, GL_STATIC_DRAW);

	printf("mesh loaded");

	return mesh;
}


static void Vec3ToVec2(struct aiVector2D* texCoords, struct aiVector3D* vec3Ptr, const unsigned long long vertexLenght)
{
	for (unsigned int i = 0; i < vertexLenght; i++)
	{
		memcpy(texCoords + i * vec2size, vec3Ptr + vec3size * i, vec2size);
	}
}

static
unsigned int CreateShader(const char* vertexPath, const char* fragPath)
{
	printf("shaders loading");

	char vertexBuffer[255];
	char fragmentBuffer[255];
	char ErrorString[100];

	FILE* vertexFile = fopen(vertexPath, 'r');
	int lenghth = fscanf(vertexFile, "%s", &vertexBuffer);
	printf("vertex shader: %s \n", vertexBuffer);

	unsigned int vertexID = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexID, 1, &vertexBuffer[0], &lenghth);
	glCompileShader(vertexID);

	printf(glGetError());

	int log = 0;
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &log);

	if (log == 0)
	{
		glGetShaderInfoLog(vertexID, sizeof(char) * 100, NULL, &ErrorString);
		printf("vertex shader failed: ");
		printf(ErrorString);
		return 0;
	}

	FILE* fragmentFile = fopen(fragPath, 'r');
	lenghth = fscanf(fragPath, "%s", &fragmentBuffer);

	unsigned int fragmentID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragmentID, 1, &fragmentBuffer[0], &lenghth);
	glCompileShader(fragmentID);

	log = 0;
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &log);

	if (log == 0)
	{
		printf("fragment shader failed: ");
		glGetShaderInfoLog(vertexID, sizeof(char) * 100, NULL, &ErrorString);
		printf(ErrorString);
		return 0;
	}

	unsigned int program = glCreateProgram();

	glAttachShader(program, vertexID);
	glAttachShader(program, fragmentID);

	glLinkProgram(program);

	log = 0;
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &log);

	if (log == 0)
	{
		printf("shader linking failed: ");
		glGetShaderInfoLog(vertexID, sizeof(char) * 100, NULL, &ErrorString);
		printf(ErrorString);
		return 0;
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	const char modelName[] = "model";
	const char projName[]  = "proj";
	const char viewName[]  = "view";

	modelLocation = glGetUniformLocation(program, modelName);
	projLocation  = glGetUniformLocation(program, projName);
	viewLocation  = glGetUniformLocation(program, viewName);

	printf("shaders loaded");

	return program;
}


extern void RenderScene3D(void)
{
	const int monkeySize = 10;
	const float monkeyDistance = 1;
	
	mat4 model = GLM_MAT4_IDENTITY_INIT;

	glUniformMatrix4fv(viewLocation, 1, false, &model[0]);
	glUniformMatrix4fv(projLocation, 1, false, &proj[0]);

	for (int x = 0; x < monkeySize; x++)
	{
		for (int y = 0; y < monkeySize; y++)
		{
			vec3 dummy3 = { x, 0, y };
			glm_translate(model, dummy3);
			glUniformMatrix4fv(modelLocation, 1, false, &model[0]);
			glDrawElements(GL_TRIANGLES, monkey->numIndices, GL_UNSIGNED_INT, 0);
		}
	}
}

static void OnClose(void)
{
	glDeleteProgram(shader);
	disposeMesh(&monkey);
}
