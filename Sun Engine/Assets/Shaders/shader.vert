#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 fTexcoord;
out vec3 fNormal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	fNormal = aNormal * mat3(transpose(inverse(model)));
	FragPos = vec3(model * vec4(aPosition, 1.0));
	fTexcoord = aTexCoord;

	gl_Position = vec4(aPosition, 1) * model * view * proj;
}