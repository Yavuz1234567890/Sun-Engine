#version 330 core

layout (location = 0) out vec4 out_color;

in vec2 fTexcoord;
in vec3 fNormal;
in vec3 FragPos;

// these will be uniforms
const vec3 color = vec3(1);
const float sunAngle = 2.2;
const float sunIntensity = 1;
const vec3 sunColor = vec3(1.0, 1.0, 0.80);

void main()
{
	vec3 sunDirection = vec3(sin(sunAngle),cos(sunAngle), 0); // calculation of sun direction

	float NdotL = dot(fNormal, sunDirection); // dot product

	// difuse lighting
	vec3 difuseTerm = sunColor * NdotL * sunIntensity; 
	// in future ambient lighting and specular lighting can be added

	out_color = vec4(difuseTerm * color, 1);
}
