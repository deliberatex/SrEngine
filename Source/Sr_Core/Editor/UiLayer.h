#pragma once

#include "CompUIs/CompUI.h"
#include "Vendor/IMGUI/imgui.h"
#include "Vendor/GUIZMO/ImGuizmo.h"

struct Transform;

namespace SrEngine
{

	struct ViewPortRect
	{
		float X, Y, W, H = 0;
	};

	struct Gizmo
	{
		bool UseSnap = false;
		glm::mat4 View, Proj, Model;
		glm::vec3 Snap = glm::vec3(0);
		Transform* cTransform = nullptr;
		ImGuizmo::MODE Mode = ImGuizmo::LOCAL;
		ImGuizmo::OPERATION Operation = ImGuizmo::TRANSLATE;
	};

	using EntityField = std::tuple<size_t, std::string, ImTextureID>;

	class UiLayer
	{

	public:
		~UiLayer() = default;
		UiLayer(const UiLayer&) = delete;
		UiLayer& operator=(const UiLayer&) = delete;
		static UiLayer& Ref()
		{
			static UiLayer ref;
			return ref;
		}

		void Display();
		void Initialiaze();
		void AddExistingEntity(const size_t entity);
		void SetGizmoViewProjection(glm::mat4 view, glm::mat4 proj)
		{
			gizmo.View = view;
			gizmo.Proj = proj;
		}

		inline const ViewPortRect ViewportRect() const { return viewRect; }
		inline const bool IsUsingGizmo() const { return ImGuizmo::IsUsing(); }
		inline const glm::vec2 ViewSize() const { return glm::vec2(viewRect.W, viewRect.H); }

	private:
		UiLayer();
		void LoadIcons();
		void SetGuiStyle();

		// PANELS

		void MenuBar();
		void Viewport();
		void Components();
		void Console();
		void Entities();
		void Resources();
		void Dockspace();

		// ACTIONS

		void MoveEntityUp();
		void MoveEntityDown();

		void AddNewEntity();
		void RemoveEntity();

		void AddComponent(const char* typeName);
		void RemoveComponent(const char* typeName);

		void InitCompUI();
		void TransformGizmo();
		void OnImGui(std::string directoryPath);
		std::pair<bool, uint32_t> DirectoryTreeViewRecursive(const std::filesystem::path& path, uint32_t* count, int* selection_mask);

	private:
		int selectedEntity;
		int lastSelectedEntity;
		bool hasSaved = false;
		ImGuiWindowFlags window_flags;

		Gizmo gizmo;
		ViewPortRect viewRect;
		ImTextureID sceneFrameTexture;
		std::vector<EntityField> entities;

		std::map<std::string, ImTextureID> icons;
		std::vector<std::shared_ptr<CompUI>> compUIs;
		std::vector<std::shared_ptr<CompUI>> activeCompUIs;
	};

	static UiLayer& UI = UiLayer::Ref();
}