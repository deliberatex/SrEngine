#pragma once

#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "Resource/Resource.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/PointLight.h"

using namespace SrEngine;

class PointLightSystem : public ECS::BaseSystem
{

public:
	PointLightSystem()
	{
		AddComponentSignature<Transform>();
		AddComponentSignature<PointLight>();
		shader = Shader(Resource.Program("MESH"));
	}

	void Update()
	{

		shader.Bind();
		shader.Set1i("pointLightCount", entities.size());

		int index = 0;

		for (auto entity : entities)
		{
			auto& light = ECS::Manager.GetComponent<PointLight>(entity);
			auto& transform = ECS::Manager.GetComponent<Transform>(entity);

			shader.Bind();
			shader.SetV3f(GetAttr("Color", index).c_str(), light.Color);
			shader.Set1f(GetAttr("Intensity", index).c_str(), light.Intensity);
			shader.SetV3f(GetAttr("Position", index).c_str(), transform.Position);

			index++;
		}
	}

private:
	std::string GetAttr(std::string attr, int index)
	{
		std::string uName("pointLights[");
		uName.append(std::to_string(index));
		uName.append("].");
		uName.append(attr);
		return uName;
	}

private:
	Shader shader;
};

