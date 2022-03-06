#pragma once

#include "Objects/Shader.h"
#include "ECS/Base/BaseComponent.h"

struct Transform : public ECS::BaseComponent
{
public:
	Transform() = default;
	~Transform() = default;

	glm::fvec3 Position = glm::fvec3(0.0f);
	glm::fvec3 Rotation = glm::fvec3(0.0f);
	glm::fvec3 Scale = glm::fvec3(1.0f);

	Transform(const glm::vec3& translate, const glm::vec3& scale, const glm::vec3& rotation) :
		Position(translate), Scale(scale), Rotation(rotation)
	{
	}

	Transform(const glm::vec3& translate, const glm::vec3& scale) :
		Position(translate), Scale(scale)
	{
	}

	Transform(const glm::vec3& translate) :
		Position(translate)
	{
	}

	glm::mat4 Model()
	{
		//glm::toMat4(glm::quat(Rotation));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), Position);
		model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
		model = glm::scale(model, Scale);
		return model;
	}

	void SetModelUniform(Shader& shader)
	{
		shader.Bind();
		shader.SetMatrix4f("Model", glm::value_ptr(Model()));
	}
};



