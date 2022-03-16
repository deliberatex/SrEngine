#pragma once

#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "Resource/Resource.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/MeshRenderer.h"

using namespace SrEngine;

class MeshRendererSystem : public ECS::BaseSystem
{

public:
	MeshRendererSystem()
	{
		AddComponentSignature<Transform>();
		AddComponentSignature<MeshRenderer>();
		shaders[0] = Shader(Resource.Program("MESH"));
	}

	void Render() override
	{
		for (auto entity : entities)
		{
			for (auto shader : shaders)
			{
				ECS::Manager.GetComponent<Transform>(entity).SetModelUniform(shader);
				auto& renderer = ECS::Manager.GetComponent<MeshRenderer>(entity);

				if (renderer.Name == "SPHERE")
					renderer.Mesh.Render(shader);
				else
					renderer.Mesh.DrawArrays(shader);
			}
		}
	}

private:
	Shader shaders[1];
};