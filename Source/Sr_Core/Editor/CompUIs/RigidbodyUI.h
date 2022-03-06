#pragma once

#include "CompUI.h"
#include "ECS/Components/RigidBody.h"

class RigidBodyUI : public CompUI
{

public:
	RigidBodyUI() = default;


	void Init(ECS::EntityID entity) override
	{
		isVisible = false;
		if (ECS::Manager.HasComponent<RigidBody>(entity))
		{
			rigidbody = &ECS::Manager.GetComponent<RigidBody>(entity);
			isVisible = true;
		}
	}

	void Show() override
	{

		if (ImGui::CollapsingHeader("Rigidbody"))
		{
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[1]);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, FRAME_PADDING);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, DARK);

			ImGui::BeginChildFrame(ImGui::GetID("rigidbodyframe"), ImVec2(0, 55));
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			{
				ImGui::PushStyleColor(ImGuiCol_Button, GREEN);
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 3));

				if (ImGui::Button("Mass", ImVec2(50, 18))) { rigidbody->Mass = 1.0f; }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::DragFloat("##mass", &rigidbody->Mass, 0.01f, -5.0f, 5.0f, "%.1f");

				if (ImGui::Button("GravityScale", ImVec2(50, 18))) { rigidbody->GravityScale = 1.0f; }
				ImGui::SameLine();
				ImGui::SetNextItemWidth(-1);
				ImGui::DragFloat("##gravityscale", &rigidbody->GravityScale, 0.01f, -5.0f, 5.0f, "%.1f");

				ImGui::PopStyleVar();
				ImGui::PopStyleColor();
				
			}
			ImGui::EndChildFrame();
			ImGui::SetCurrentFont(ImGui::GetIO().Fonts->Fonts[0]);
		}
	}

private:
	RigidBody* rigidbody;

};