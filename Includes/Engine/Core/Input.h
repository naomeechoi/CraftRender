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

		// 편의 함수.
		// keyCode -> 버튼 값 (예: 'A').
		bool IsKeyDown(unsigned int keyCode);
		bool IsKeyUp(unsigned int keyCode);
		bool IsKey(unsigned int keyCode);

		// 마우스 입력 관련 함수.
		bool IsButtonDown(unsigned int button);
		bool IsButtonUp(unsigned int button);
		bool IsButton(unsigned int button);

		// 입력 정리 함수.
		void ResetInputs();

		Vector2 GetMousePosition();
		float GetMouseDeltaX();		// 이전 프레임 대비 이동한 거리(X).
		float GetMouseDeltaY();		// 이전 프레임 대비 이동한 거리(Y).

		// 설정 함수.
		void SetKeyUpDown(unsigned int keyCode, bool isKeyUp, bool isKeyDown);
		void SetButtonUpDown(unsigned int button, bool isButtonUp, bool isButtonDown);
		void SetMousePosition(int x, int y);

		// 싱글톤 접근 함수.
		static Input& Get();

		static bool IsValid();

	private:
		KeyState keyStates[256] = {};
		MouseState mouseStates[3] = {};

		Vector2 mousePosition;
		Vector2 mousePreviousPosition;

		static Input* instance;
	};
}

