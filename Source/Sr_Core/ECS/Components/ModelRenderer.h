#pragma once

#include "Resource/Resource.h"
#include "ECS/Base/BaseComponent.h"

struct ModelRenderer : public ECS::BaseComponent
{
	~ModelRenderer() = default;

	ModelRenderer() : Name("PACK")
	{
		Renderer = SrEngine::Resource.GetModel(Name);
	}

	ModelRenderer(std::string name) : Name(name)
	{
		Renderer = SrEngine::Resource.GetModel(Name);
	}

	std::string Name;
	std::shared_ptr<Model3D> Renderer;
};