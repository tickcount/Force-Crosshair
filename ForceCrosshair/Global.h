#pragma once

extern INT WINAPI HkPSE(INT region);

class CGlobals
{
public:
	HWND Hwnd = nullptr;
	HINSTANCE HModule = nullptr;

	DWORD m_iHealth, m_bIsScoped;

}; extern CGlobals* g_pGlobals;

class CInterfaces
{
public:
	IBaseClientDll * Client = nullptr;
	IClientModeShared* ClientMode = nullptr;

	IClientEntityList* EntityList = nullptr;
	IEngineClient* EngineClient = nullptr;
	IGlobalVarsBase* GlobalVars = nullptr;
	ICVar* Convar = nullptr;
}; extern CInterfaces* g_pInterfaces;

class CHooks
{
public:
	VFuncHook ClientModeHook;
	EXECUTE Attach();

	using DoPostScreenEffects = int(__thiscall*)(IClientModeShared*, INT);

}; extern CHooks* g_pHooks;

class CClient
{
public:
	EXECUTE IFactory();

	CNetVarManager* Netvars = new CNetVarManager;

	PEXECUTE FindFactory(std::string Module, std::string Name)
	{
		typedef void* (*Interface_t)(const char* name, int ret);
		Interface_t IFact(reinterpret_cast<Interface_t>(GetProcAddress(GetModuleHandleA(Module.c_str()), "CreateInterface")));

		return IFact(Name.c_str(), 0);
	}

	template< class T, class Y >
	T Clamp(T const &val, Y const &minVal, Y const &maxVal)
	{
		if (val < minVal)
			return minVal;
		else if (val > maxVal)
			return maxVal;
		else
			return val;
	}

	template<class T> inline T* makeptr(void* pObj, unsigned int offset)
	{
		return reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(pObj) + offset);
	}

	template <typename T>
	T GetVFunc(void *vTable, int iIndex) {
		return (*(T**)vTable)[iIndex];
	}

	DWORD FindPattern(std::string moduleName, std::string pattern)
	{
		const char* pat = pattern.c_str();
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
		MODULEINFO miModInfo;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
		{
			if (!*pat)
				return firstMatch;

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2; //one ?
			}
			else
			{
				pat = pattern.c_str();
				firstMatch = 0;
			}
		}
		return NULL;
	}


	DWORD WaitOnModuleHandle(std::string moduleName)
	{
		DWORD ModuleHandle = NULL;
		while (!ModuleHandle)
		{
			ModuleHandle = (DWORD)GetModuleHandle(moduleName.c_str());
			if (!ModuleHandle)
				Sleep(50);
		}
		return ModuleHandle;
	}

	bool bCompare(const BYTE* Data, const BYTE* Mask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++Mask, ++Data)
		{
			if (*szMask == 'x' && *Mask != *Data)
			{
				return false;
			}
		}
		return (*szMask) == 0;
	}

	DWORD FindPattern(std::string moduleName, BYTE* Mask, char* szMask)
	{
		DWORD Address = WaitOnModuleHandle(moduleName.c_str());
		MODULEINFO ModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)Address, &ModInfo, sizeof(MODULEINFO));
		DWORD Length = ModInfo.SizeOfImage;
		for (DWORD c = 0; c < Length; c += 1)
		{
			if (bCompare((BYTE*)(Address + c), Mask, szMask))
			{
				return (DWORD)(Address + c);
			}
		}
		return 0;
	}

	typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
	typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);

	inline CreateInterfaceFn modFactory(HMODULE module)
	{
		return reinterpret_cast<CreateInterfaceFn>(GetProcAddress(module, "CreateInterface"));
	}

}; extern CClient* g_pClientInfo;