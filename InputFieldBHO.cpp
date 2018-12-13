#include "StdAfx.h"
#include "resource.h"

#include "InputFieldBHO.h"
#include "InputFieldBHO_i.c"
#include "InputFieldBHO2.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_InputFieldBHO2, CInputFieldBHO2)
END_OBJECT_MAP()

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
		TCHAR pszLoader[MAX_PATH];
		GetModuleFileName(NULL,pszLoader,MAX_PATH);
		_tcslwr_s(pszLoader);
		
		if(_tcsstr(pszLoader,_T("explorer.exe")))
			return FALSE;
		
		_Module.Init(ObjectMap, hInstance, &LIBID_InputFieldBHOLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
   
	return TRUE;    // ok	
}

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
	
}

STDAPI DllRegisterServer(void)
{
    return _Module.RegisterServer(TRUE);
}

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}