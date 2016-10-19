#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "camera.hpp"

Camera::Camera()
{
	Position = vec3(40,10,5);
	AimVect = normalize(vec3(5,-1,5));
	Up = vec3(0,1,0);
	// TODO
	ProjectionMatrix = perspective(radians(45.0f), 1280.0f/720.0f, 0.1f, 1000.0f);

	mouseSensivity = 0.008f;
	speed = 3.0f;
}

mat4 Camera::GetLookAtMatrix()
{
	return lookAt(Position, Position + AimVect, Up);
}

mat4 Camera::GetProjectionMatrix()
{
	return Camera::ProjectionMatrix;
}

glm::vec3 Camera::GetPosition()
{
	return Position;
}

void Camera::UpdateAimVect(vec2 delta)
{
	vec2 angle = mouseSensivity * delta;

	// Rotate along ortho axis
	vec3 rotationAxis = normalize(cross(AimVect, Up));
	mat4 orthoRotationMatrix = mat4();
	orthoRotationMatrix = rotate(orthoRotationMatrix, angle.y, rotationAxis);

	// Rotate along Y axis
	mat4 rotationY = mat4();
	rotationY = rotate(rotationY, angle.x, Up);

	// Update AimVect
	AimVect = vec3(orthoRotationMatrix * vec4(AimVect, 0));
	AimVect = vec3(rotationY * vec4(AimVect, 0));
	AimVect = normalize(AimVect);
}

void Camera::Rotate(float YAngle, float orthoAngle)
{
	// Rotate along ortho axis

	vec3 rotationAxis = normalize(cross(Camera::AimVect, Camera::Up));
	mat4 rotationOrtho = rotate(mat4(), orthoAngle, rotationAxis);

	// Rotate along Y axis
	mat4 rotationY = rotate(mat4(), YAngle, Camera::Up);

	// Update AimVect
	Camera::AimVect = vec3(normalize(rotationY * rotationOrtho * vec4(Camera::AimVect, 1.0)));
}

void Camera::Walk(float stepFront, float stepSide, float stepJump)
{
	vec3 frontDirection = vec3(Camera::AimVect[0], 0, Camera::AimVect[2]);
	vec3 sideDir  = normalize(cross(frontDirection, Camera::Up));

	Camera::Position += stepFront * frontDirection +
		stepSide * sideDir +
		stepJump * Up;
}
