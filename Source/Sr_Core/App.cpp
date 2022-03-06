#include "Pch/pch.h"
#include "Timer/Timer.h"
#include "Engine/Engine.h"
#include "Resource/Resource.h"
#include "Events/EventSystem.h"

using namespace SrEngine;

int main(int argc, char** argv)
{
	std::string enginePath = PathHelper::GetEnginePath(std::filesystem::current_path().string());
	PathHelper::SetEngineDirectory(enginePath);


	Resource.Initialize();
	Core.Initialize();
	Timer.Initialize();

	while (Core.Run())
	{
		Timer.Tick();
		Events.Poll();
		Core.Update();
		Core.Render();
	}

	return EXIT_SUCCESS;
}