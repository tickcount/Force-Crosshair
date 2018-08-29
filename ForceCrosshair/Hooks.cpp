#include "SDK.h"

INT WINAPI HkPSE(INT region)
{
	auto oPostScreenEffects = g_pHooks->ClientModeHook.COriginal<CHooks::DoPostScreenEffects>(44);
	auto m_iCrosshairData = g_pInterfaces->Convar->FindVar("weapon_debug_spread_show");

	CBasePlayer* g_LocalPlayer = g_pInterfaces->EntityList->GetClientEntity(g_pInterfaces->EngineClient->GetLocalPlayer());

	if (g_pInterfaces->EngineClient->IsConnected() && g_pInterfaces->EngineClient->IsInGame())
	{
		if (g_LocalPlayer && g_LocalPlayer->getHealth())
			m_iCrosshairData->m_nValue(!g_LocalPlayer->isScoped() ? 3 : 0);
	}

	return oPostScreenEffects(g_pInterfaces->ClientMode, region);
}