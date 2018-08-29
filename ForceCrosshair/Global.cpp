#include "SDK.h"

CGlobals* g_pGlobals = new CGlobals();
CClient* g_pClientInfo = new CClient();
CInterfaces* g_pInterfaces = new CInterfaces(); 
CHooks* g_pHooks = new CHooks();

EXECUTE CHooks::Attach()
{
	ClientModeHook.Attach(g_pInterfaces->ClientMode);
	ClientModeHook.HIndex(44, HkPSE);
}

EXECUTE CClient::IFactory()
{
	auto g_EnginePointer = modFactory(GetModuleHandleW(L"engine.dll"));
	auto g_ClientPointer = modFactory(GetModuleHandleW(L"client_panorama.dll"));
	auto g_Vstdlib = modFactory(GetModuleHandleW(L"vstdlib.dll"));

	g_pInterfaces->Client = (IBaseClientDll*) g_ClientPointer("VClient018", nullptr);
	g_pInterfaces->ClientMode = **(IClientModeShared***)((*(DWORD**)g_pInterfaces->Client)[10] + 0x5);

	g_pInterfaces->EntityList = (IClientEntityList*) g_ClientPointer("VClientEntityList003", nullptr);
	g_pInterfaces->EngineClient = (IEngineClient*) g_EnginePointer("VEngineClient014", nullptr);
	g_pInterfaces->GlobalVars = **(IGlobalVarsBase***)((*(DWORD**)g_pInterfaces->Client)[0] + 0x1B);

	g_pInterfaces->Convar = (ICVar*) g_Vstdlib("VEngineCvar007", nullptr);
	g_pClientInfo->Netvars->Initialize();

	g_pGlobals->m_iHealth = g_pClientInfo->Netvars->GetOffset("DT_CSPlayer", "m_iHealth");
	g_pGlobals->m_bIsScoped = g_pClientInfo->Netvars->GetOffset("DT_CSPlayer", "m_bIsScoped");

	g_pHooks->Attach();
}

// Other Functions
ClientClass* IBaseClientDll::GetAllClasses()
{
	typedef ClientClass*(__thiscall* OriginalFn)(PVOID);
	return GetFunc<OriginalFn>(this, 8)(this);
}

int CBasePlayer::getHealth()
{
	return *g_pClientInfo->makeptr<bool>(this, g_pGlobals->m_iHealth);
}

bool CBasePlayer::isScoped()
{
	return *g_pClientInfo->makeptr<bool>(this, g_pGlobals->m_bIsScoped);
}