#pragma once

#include "ECS/Base/BaseComponent.h"


struct Particle :public ECS::BaseComponent
{
	Particle() = default;
	~Particle() = default;

	glm::vec2 Velocity = glm::vec3(0.0f);
	glm::vec2 Position = glm::vec3(0.0f);
	glm::vec4 color = glm::vec4(1.0f);
	GLfloat Life = 1.0f;

};