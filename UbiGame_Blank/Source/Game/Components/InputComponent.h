#pragma once
#include "Game\Components\MovementComponent.h"

namespace Game
{
	class InputComponent : public MovementComponent
	{
		void Update() override;

	};
}

