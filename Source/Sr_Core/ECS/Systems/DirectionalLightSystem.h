#pragma once

#include "ECS/Base/BaseSystem.h"
#include "ECS/Base/EntityManager.h"

#include "Engine/Engine.h"
#include "Resource/Resource.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/DirectionalLight.h"

using namespace SrEngine;

class DirectionalLightSystem : public ECS::BaseSystem
{

public:
	DirectionalLightSystem()
	{
		AddComponentSignature<Transform>();
		AddComponentSignature<DirectionalLight>();

		depthBuffer = Core.ShadowBuffer();

		shadow = Shader(Resource.Program("SHADOW"));

// 		shadow.Bind();
// 		shadow.Set1i("ShadowMap", 0);
// 		shadow.Set1i("DiffuseMap", 1);
// 		shadow.UnBind();

		shaders[0] = Shader(Resource.Program("MESH"));
		shaders[1] = Shader(Resource.Program("SKYBOX"));
	}

	void Update()
	{

		for (auto& shader : shaders)
		{
			shader.Bind();
			shader.Set1i("directLightCount", entities.size());
			
		}

		int index = 0;

		for (auto entity : entities)
		{

			auto& transform = ECS::Manager.GetComponent<Transform>(entity);
			auto& light = ECS::Manager.GetComponent<DirectionalLight>(entity);

			// Shadow Mapping

			glm::mat4 view = glm::lookAt(transform.Position, glm::vec3(0), glm::vec3(1));
			glm::mat4 proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
			space = proj * view;

			shadow.Bind();
			shadow.SetMatrix4f("LightViewProj", glm::value_ptr(space)); // simpleDepthShader

			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			depthBuffer->Bind();
			depthBuffer->Clear();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 1);
			std::cout << "depthBuffer->GetMapID()::" << depthBuffer->GetMapID() << std::endl;

			for (auto entity : entities)
			{
				for (auto shader : shaders)
				{
					ECS::Manager.GetComponent<Transform>(entity).SetModelUniform(shadow);
					auto& renderer = ECS::Manager.GetComponent<MeshRenderer>(entity);

					if (renderer.Name == "SPHERE" || renderer.Name == "CUBE")
						renderer.Mesh.Render(shadow);
					else
						renderer.Mesh.DrawArrays(shadow);

					//RenderScene();

				}
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Other Shaders

			for (GLuint i = 0; i < 2; i++)
			{
				shaders[i].Bind();
				shaders[i].SetV3f(GetAttr("Color", index).c_str(), light.Color);
				shaders[i].Set1f(GetAttr("Intensity", index).c_str(), light.Intensity);
				shaders[i].SetV3f(GetAttr("Direction", index).c_str(), light.Direction);
				shaders[i].SetV3f(GetAttr("Position", index).c_str(), transform.Position);
			}

			index++;
		}
	}

	void Render()
	{
		

		
		
	}

private:
	std::string GetAttr(std::string attr, int index)
	{
		std::string uName("directLights[");
		uName.append(std::to_string(index));
		uName.append("].");
		uName.append(attr);
		return uName;
	}

private:
	Shader shadow;
	Shader shaders[2];
	glm::mat4 space;
	DepthBuffer* depthBuffer;
};

