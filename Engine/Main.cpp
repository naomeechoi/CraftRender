#include "Core/Engine.h"
using namespace Craft;

void LaunchEngineStartUp(HINSTANCE instance)
{
	Engine engine;
	engine.Initialize(instance);
	engine.Run();
}

#ifdef _CONSOLE
int main()
{
    LaunchEngineStartUp(GetModuleHandle(nullptr));
}
#else
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    LaunchEngineStartUp(hInstance);
    return 0;
}
#endif