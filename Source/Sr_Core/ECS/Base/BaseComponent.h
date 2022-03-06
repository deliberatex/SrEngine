#pragma once

#include "Types.h"

namespace ECS
{
	struct BaseComponent
	{
		BaseComponent() = default;
		~BaseComponent() = default;

		inline const EntityID GetID() const { return entityID; }

	private:
		friend class EntityManager;
		EntityID entityID = -1;
	};
}