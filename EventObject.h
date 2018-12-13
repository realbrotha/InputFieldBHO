#pragma once

#include <mshtml.h>
#include "InputFieldDlg.h"

class CEventObject
{

public:
	CEventObject();
	virtual ~CEventObject();

	void fnCallBackOnSubmit(DISPID id, VARIANT *pvtResult);		
	void fnCallBackOnKeyPress(DISPID id, VARIANT *pvtResult);		
	int EventPut_Submit(IHTMLFormElement *pIHTMLFormElement);
	int EventPut_KeyCode();

	BOOL * m_pbOnSubmit;
	InputFieldDlg * m_pInputLogDlg;
	CComPtr<IDispatch> m_spOnSubmitEventDispatch;	
	CComPtr<IDispatch> m_spKeyDownEventDispatch;	
	CComPtr<IDispatch> m_spFocusEventDispatch;	
	CComQIPtr<IHTMLFormElement> m_spFormElement;
	CComQIPtr<IHTMLDocument2> m_spHTMLDocument2;

};
