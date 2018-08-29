#include "SDK.h"
#include "SecurityHandler.h"

EXECUTE WINAPI Init()
{
	while (!(g_pGlobals->Hwnd = FindWindowA("Valve001", 0)))
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	while (!GetModuleHandleA("serverbrowser.dll"))
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	g_pClientInfo->IFactory();
}

BOOL WINAPI DllMain(HINSTANCE HModule, DWORD DWReason, LPVOID LPReversed)
{
	bool DisableTLC = DisableThreadLibraryCalls(HModule);

	if (DWReason == DLL_PROCESS_ATTACH)
		Threading->UniqueThread(Init, HModule, TRUE);

	return TRUE;
}