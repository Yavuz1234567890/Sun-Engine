
#include <scene_camera.h>

static float yaw, pitch = 45;
static vec3 center;

static void MoveInput(void);

extern 
void InitializeCamera(void)
{

}

extern 
void CameraTick(void)
{	
	camFront[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
	camFront[1] = sin(glm_rad(pitch));
	camFront[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));

	MoveInput();

	glm_normalize(camFront);
	glm_vec3_cross(&camFront[0], &worldUP[0], &camRight[0]);
	glm_vec3_cross(&camRight[0], &camFront[0], &camUp[0]);

	glm_vec3_normalize(camFront);
	glm_vec3_normalize(camUp);
	
	glm_perspective(glm_rad(fov), Width / Height, 0.1f, 500, proj);
	glm_vec3_add(camPosition, camFront, center);
	
	glm_lookat(camPosition, center, camUp, view);
}

static
void MoveInput(void)
{
	yaw   += MousePos[0] * MouseSensitivity;
	pitch += glm_clamp(MousePos[1] * MouseSensitivity, -90, 90);
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		glm_vec3_mulf(camFront, MovementSpeed, dummy3);
		glm_vec3_add(camPosition, dummy3, camPosition);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		glm_vec3_mulf(camFront, MovementSpeed, dummy3);
		glm_vec3_sub(camPosition, dummy3, camPosition);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		glm_vec3_mulf(camRight, MovementSpeed, dummy3);
		glm_vec3_add(camPosition, dummy3, camPosition);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		glm_vec3_mulf(camRight, MovementSpeed, dummy3);
		glm_vec3_sub(camPosition, dummy3, camPosition);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		glm_vec3_mulf(camRight, MovementSpeed, dummy3);
		glm_vec3_add(camPosition, dummy3, camPosition);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		glm_vec3_mulf(camRight, MovementSpeed, dummy3);
		glm_vec3_sub(camPosition, dummy3, camPosition);
	}
}