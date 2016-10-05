#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera
{
public:
	glm::mat4 GetLookAtMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec3 GetPosition();
	void UpdateAimVect(glm::vec2 delta);
	void Rotate(float YAngle, float orthoAngle);
	void Walk(float stepFront, float stepSide, float stepJump);

	Camera();
private:
	glm::vec3 Position;
	glm::vec3 AimVect;
	glm::vec3 Up;
	glm::mat4 ProjectionMatrix;

	// Properties
	float mouseSensivity;
	float speed;
};

#endif
