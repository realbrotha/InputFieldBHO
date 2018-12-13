#pragma once

#include "resource.h"
#include "EventObjectList.h"

#include <ExDispID.h>
#include <mshtml.h>
#include <exdisp.h>
#include <comdef.h>
#include <stdio.h>

extern InputFieldDlg g_InputLogdlg;

class ATL_NO_VTABLE CInputFieldBHO2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInputFieldBHO2, &CLSID_InputFieldBHO2>,
	public IObjectWithSiteImpl<CInputFieldBHO2>,
	public IDispatchImpl<IInputFieldBHO2, &IID_IInputFieldBHO2, &LIBID_InputFieldBHOLib>
{

public:
	CInputFieldBHO2();
	~CInputFieldBHO2();

	DECLARE_REGISTRY_RESOURCEID(IDR_InputFieldBHO2)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CInputFieldBHO2)
		COM_INTERFACE_ENTRY(IInputFieldBHO2)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

public:
	STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pvarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
	STDMETHOD(OnQuit)();
	STDMETHOD(Connect)();
	STDMETHOD(SetSite)(IUnknown *pUnkSite);
	STDMETHOD(SetIEHook)(void);
	STDMETHOD(OnDocumentComplete)(IDispatch * pdisp);
	STDMETHOD(OnBeforNavigate2)(void);
	STDMETHOD(OnDownloadComplete)(void);

    static LRESULT CALLBACK IEKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

private:
    __int32 refCount_;  // todo : refCount 를 이용하여 Browser Process 에서 Detach 되는것을 제어 할것.

	CEventObjectList * eventObjList_;
    CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> web2_;
    CComQIPtr<IConnectionPointContainer, &IID_IConnectionPointContainer> cpc_;
	CComPtr<IHTMLDocument2> doc2_;
	
	DWORD cookies;
	BOOL docComplete;
};
