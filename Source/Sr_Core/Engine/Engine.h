#pragma once

#include "Objects/DepthBuffer.h"
#include "Objects/SamplerBuffer.h"
#include "Events/Event.h"
#include "Events/Dispatcher.h"
#include "Events/AppEvents.h"

namespace SrEngine
{

	const int SCREEN_WIDTH(1920);
	const int SCREEN_HEIGHT(1080);

	const int SHADOW_WIDTH = 1024;
	const int SHADOW_HEIGHT = 1024;

	class Engine
	{

	public:
		~Engine();
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		static Engine& Ref()
		{
			static Engine reference;
			return reference;
		}

		void OnQuit(const Event& e)
		{
			isRuning = false;
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		void OnViewportResized(const Event& e)
		{
			auto event = Dispatcher.Cast<ViewportResizedEvent>(e);
			viewSize.x = event.Width();
			viewSize.y = event.Height();
			outputBuffer->SetSize(viewSize.x, viewSize.y);
			shadowBuffer->SetSize(SHADOW_WIDTH, SHADOW_HEIGHT);
			glViewport(0, 0, viewSize.x, viewSize.y);

			std::cout << "viewport resised! " << viewSize.x << "\n";
		}

		void SetViewport(glm::vec2 size)
		{
			viewSize = size;
			outputBuffer->SetSize(size.x, size.y);
			shadowBuffer->SetSize(SHADOW_WIDTH, SHADOW_HEIGHT);
			glViewport(0, 0, size.x, size.y);
		}

		void Update();
		void Render();
		void StopGame();
		void StartGame();
		void Initialize();

		inline glm::vec2 ViewSize() const { return viewSize; }
		inline DepthBuffer* ShadowBuffer() const { return shadowBuffer; }
		inline SamplerBuffer* GetSceneBufferID() const { return outputBuffer; }

		inline GLFWwindow& Window() { return *window; }
		inline const bool Run() const { return isRuning; }

	private:
		Engine();

	private:
		bool isRuning;
		bool isGameRunnig;
		GLFWwindow* window;

		glm::ivec2 viewSize;
		DepthBuffer* shadowBuffer;
		SamplerBuffer* outputBuffer;
	};

	static Engine& Core = Engine::Ref();
}
