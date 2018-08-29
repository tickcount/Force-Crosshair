#pragma once

class ConVar
{
public:
	void m_nValue(const char* value);
	void m_nValue(float value);
	void m_nValue(int value);
	void m_nValue(char value);
	void InternalSetString(const char* str);
	char* GetName();
	char* GetDefault();

	char pad_0x0000[0x4]; //0x0000
	ConVar* pNext; //0x0004 
	__int32 bRegistered; //0x0008 
	char* pszName; //0x000C 
	char* pszHelpString; //0x0010 
	__int32 nFlags; //0x0014 
	char pad_0x0018[0x4]; //0x0018
	ConVar* pParent; //0x001C 
	char* pszDefaultValue; //0x0020 
	char* strString; //0x0024 
	__int32 StringLength; //0x0028 
	float fValue; //0x002C 
	__int32 nValue; //0x0030 
	__int32 bHasMin; //0x0034 
	float fMinVal; //0x0038 
	__int32 bHasMax; //0x003C 
	float fMaxVal; //0x0040 
	void* fnChangeCallback; //0x0044 
};//Size=0x0048

class SpoofedConvar
{
public:
	SpoofedConvar();
	SpoofedConvar(const char* szCVar);
	SpoofedConvar(ConVar* pCVar);

	~SpoofedConvar();

	bool IsSpoofed();
	void Spoof();

	void SetFlags(int flags);
	int GetFlags();

	void SetBool(bool bValue);
	void SetInt(int iValue);
	void SetFloat(float flValue);
	void SetString(const char* szValue);

private:
	ConVar * m_pOriginalCVar = nullptr;
	ConVar* m_pDummyCVar = nullptr;

	char m_szDummyName[128];
	char m_szDummyValue[128];
	char m_szOriginalName[128];
	char m_szOriginalValue[128];
	int m_iOriginalFlags;
};

class IAppSystem
{
public:
	virtual void func0() = 0;
	virtual void func1() = 0;
	virtual void func2() = 0;
	virtual void func3() = 0;
	virtual void func4() = 0;
	virtual void func5() = 0;
	virtual void func6() = 0;
	virtual void func7() = 0;
	virtual void func8() = 0;
	virtual void func9() = 0;
};

struct CVarDLLIdentifier_t;

class ICVar : public IAppSystem
{
public:
	virtual void func10() = 0;
	virtual void RegisterConCommand(ConVar* pCommandBase) = 0;
	virtual void UnregisterConCommand(ConVar* pCommandBase) = 0;
	virtual void func13() = 0;
	virtual ConVar* FindVar(const char* var_name) = 0;
	virtual void func15() = 0;
	virtual void func16() = 0;
	virtual void func17() = 0;
	virtual void func18() = 0;
	virtual void func19() = 0;
	virtual void func20() = 0;
};