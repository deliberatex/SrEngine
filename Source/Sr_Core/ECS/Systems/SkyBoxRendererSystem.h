#pragma once

#include "Objects/Shader.h"
#include "Resource/Resource.h"
#include "Objects/VertexArray.h"
#include "ECS/Base/BaseSystem.h"

using namespace SrEngine;

class SkyBoxRendererSystem : public ECS::BaseSystem
{
public:

	SkyBoxRendererSystem()
	{
		shader = Shader(Resource.Program("SKYBOX"));
		shader.Bind();
		shader.SetSampleCube("CubeMap", Resource.CubeMap("SKYBOX"));

		static Vertex vertices[] = {
			// positions
			Vertex(-1.0f, 1.0f, -1.0f),
			Vertex(-1.0f, -1.0f, -1.0f),
			Vertex(1.0f, -1.0f, -1.0f),
			Vertex(1.0f, -1.0f, -1.0f),
			Vertex(1.0f, 1.0f, -1.0f),
			Vertex(-1.0f, 1.0f, -1.0f),

			Vertex(-1.0f, -1.0f, 1.0f),
			Vertex(-1.0f, -1.0f, -1.0f),
			Vertex(-1.0f, 1.0f, -1.0f),
			Vertex(-1.0f, 1.0f, -1.0f),
			Vertex(-1.0f, 1.0f, 1.0f),
			Vertex(-1.0f, -1.0f, 1.0f),

			Vertex(1.0f, -1.0f, -1.0f),
			Vertex(1.0f, -1.0f, 1.0f),
			Vertex(1.0f, 1.0f, 1.0f),
			Vertex(1.0f, 1.0f, 1.0f),
			Vertex(1.0f, 1.0f, -1.0f),
			Vertex(1.0f, -1.0f, -1.0f),

			Vertex(-1.0f, -1.0f, 1.0f),
			Vertex(-1.0f, 1.0f, 1.0f),
			Vertex(1.0f, 1.0f, 1.0f),
			Vertex(1.0f, 1.0f, 1.0f),
			Vertex(1.0f, -1.0f, 1.0f),
			Vertex(-1.0f, -1.0f, 1.0f),

			Vertex(-1.0f, 1.0f, -1.0f),
			Vertex(1.0f, 1.0f, -1.0f),
			Vertex(1.0f, 1.0f, 1.0f),
			Vertex(1.0f, 1.0f, 1.0f),
			Vertex(-1.0f, 1.0f, 1.0f),
			Vertex(-1.0f, 1.0f, -1.0f),

			Vertex(-1.0f, -1.0f, -1.0f),
			Vertex(-1.0f, -1.0f, 1.0f),
			Vertex(1.0f, -1.0f, -1.0f),
			Vertex(1.0f, -1.0f, -1.0f),
			Vertex(-1.0f, -1.0f, 1.0f),
			Vertex(1.0f, -1.0f, 1.0f)
		};
		vao = VertexArray(vertices, sizeof(vertices));
	}

	void Render() override
	{
		GLCALL(glDepthMask(GL_FALSE));
		GLCALL(glDepthFunc(GL_LEQUAL));
		shader.Bind();
		vao.DrawArrays();
		GLCALL(glDepthMask(GL_TRUE));
		GLCALL(glDepthFunc(GL_LESS));
	}

private:
	Shader shader;
	VertexArray vao;
};