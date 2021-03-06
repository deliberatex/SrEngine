#pragma once
#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "Resource/Resource.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/ModelRenderer.h"

using namespace SrEngine;

class ModelRendererSystem : public ECS::BaseSystem
{

public:

	ModelRendererSystem()
	{
		AddComponentSignature<Transform>();
		AddComponentSignature<ModelRenderer>();

		shader[0] = Shader(Resource.Program("MESH"));
		shader[1] = Shader(Resource.Program("RENDERSHADOW"));
	}

	void Render() override
	{
		shader[0].Bind();
		for (auto entity : entities)
		{
			ECS::Manager.GetComponent<Transform>(entity).SetModelUniform(shader[0]);
			ECS::Manager.GetComponent<ModelRenderer>(entity).Renderer->Render(shader[0]);

			
		}
	}

private:
	Shader shader[2];
};