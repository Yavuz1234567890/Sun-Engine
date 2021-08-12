
#include <rendering.h>
#include <assert.h>
#include <scene_camera.h>

#pragma warning(disable : 6305)

static const C_STRUCT aiScene* scene = NULL;
static const struct Mesh* monkey = NULL;
static GLuint shader;

static GLuint modelLocation;
static GLuint viewLocation;
static GLuint projLocation;

static void InitRendering()
{
	monkey = CreateMesh("../SunEngine/Assets/Models/monkey.glb");
	shader = CreateShader("../SunEngine/Assets/Shaders/shader.vert", "../SunEngine/Assets/Shaders/shader.frag");

	glUseProgram(shader);
}

// we are combining mesh here it can be changed for future 
static struct Mesh* CreateMesh(const char* path)
{
	scene = aiImportFile(path, aiProcessPreset_TargetRealtime_Fast);
	
	if (scene == NULL)
	{
		char message[100] = "scene is null maybe path wrong";
		printf(strcat(message, path));
		return NULL;
	}

	int i = 0, j;
	const int vertexSize = sizeof(float) * 8; // texcoords 2 + normals 3 + positions 3

	struct Mesh* mesh = (struct Mesh*)malloc(sizeof(struct Mesh));

	for (; i < scene->mNumMeshes; i++)
	{
		mesh->numVertices += scene->mMeshes[i]->mNumVertices;
	}
	
	mesh->vertexData = malloc(vertexSize * mesh->numVertices);

	float* currentIndex;

	for (i = 0; i < scene->mNumMeshes; i++)
	{
		struct aiMesh* meshPtr = &scene->mMeshes[i];
		
		struct aiVector2D* texCoords = malloc(sizeof(struct aiVector2D) * meshPtr->mNumVertices);

		Vec3ToVec2(texCoords, meshPtr->mTextureCoords[0], meshPtr->mNumVertices);

		currentIndex = (float*)mesh->vertexData + vertexSize * i;

		memcpy((float*)currentIndex, &meshPtr->mVertices, sizeof(struct aiVector3D) * meshPtr->mNumVertices); // position array
		
		currentIndex = sizeof(struct aiVector3D) * meshPtr->mNumVertices;
		memcpy(currentIndex, &texCoords, sizeof(struct aiVector2D) * meshPtr->mNumVertices); // texCoord array
		
		currentIndex = sizeof(struct aiVector2D) * meshPtr->mNumVertices;
		memcpy(currentIndex , &meshPtr->mVertices, sizeof(struct aiVector2D) * meshPtr->mNumVertices); // normal array
		
		for (j = 0; j < meshPtr->mNumFaces; j++)
		{
			mesh->numIndices += 3;
		}
	}

	mesh->indexData = malloc(sizeof(int) * mesh->numIndices);

	unsigned int currentVertexIndex = 0;
	
	for (i = 0; i < scene->mNumMeshes; i++)
	{
		struct aiMesh* meshPtr = &scene->mMeshes[i];

		for (j = 0; j < meshPtr->mNumFaces; i++)
		{
			memcpy((int*)mesh->indexData + currentVertexIndex * sizeof(int), &meshPtr->mFaces[j], sizeof(int));
			currentVertexIndex ++;
		}
	}

	// create buffers
	glGenVertexArrays(1, &mesh->vaoID);
	glBindVertexArray(mesh->vaoID);

	glGenBuffers(1, &mesh->vboID);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vboID);
	glBufferData(GL_ARRAY_BUFFER, mesh->vboID, mesh->vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, mesh->vertexData); // position
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE , sizeof(float) * 2, mesh->vertexData); // texCoord
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, mesh->vertexData); // normal

	glEnableVertexAttribArray(0); // position
	glEnableVertexAttribArray(1); // texCoord
	glEnableVertexAttribArray(2); // normal

	glGenBuffers(1, &mesh->eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mesh->numIndices, mesh->indexData, GL_STATIC_DRAW);

	return mesh;
}

static inline void Vec3ToVec2(struct aiVector2D* texCoords, struct aiVector3D* vec3Ptr, const int* vertexSize)
{
	for (int i = 0; i < vertexSize; i++)
	{
		memcpy(texCoords + i * sizeof(struct aiVector2D), vec3Ptr + sizeof(struct aiVector3D) * i, sizeof(float) * 2);
	}
}

static unsigned int CreateShader(const char* vertexPath, const char* fragPath)
{
	char vertexBuffer[255];
	char fragmentBuffer[510];
	char ErrorString[100];

	FILE* vertexFile = fopen(vertexPath, 'r');
	int lenghth = fscanf(vertexFile, "%s", &vertexBuffer);
	printf("vertex shader: %s\n", vertexBuffer);

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

	return program;
}

static mat4 model;

static void RenderScene3D()
{
	const int monkeySize = 10;
	const float monkeyDistance = 1;

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

static void ClearRendering()
{
	glDeleteProgram(shader);
	glDeleteVertexArrays(1, &monkey->vaoID);
	glDeleteBuffers(1, &monkey->vboID);
	glDeleteBuffers(1, &monkey->eboID);
}