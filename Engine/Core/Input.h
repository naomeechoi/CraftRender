#pragma once
#include "Core/Common.h"
#include "Math/Vector2.h"

namespace Craft
{
	struct KeyState
	{
		bool isKeyDown = false;
		bool isKeyUp = false;
		bool isKey = false;

		void SetKeyUpDown(bool isKeyUp, bool isKeyDown)
		{
			this->isKeyDown = isKeyDown;
			this->isKeyUp = isKeyUp;
			isKey = isKeyDown && !isKeyUp;
		}
	};

	struct MouseState
	{
		bool isButtonDown = false;
		bool isButtonUp = false;
		bool isButton = false;

		void SetButtonUpDown(bool isButtonUp, bool isButtonDown)
		{
			this->isButtonDown = isButtonDown;
			this->isButtonUp = isButtonUp;
			isButton = isButtonDown && !isButtonUp;
		}
	};

	class CRAFT_API Input
	{
	public:
		Input();
		~Input();

		static Input& Get();

	private:
		KeyState KeyStates[256] = {};
		MouseState mouseStates[3] = {};

		Vector2 mousePosition;
		Vector2 mousePreviousPosition;

		static Input* instance;
	};
}

