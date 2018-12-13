#include "StdAfx.h"
#include "resource.h"
#include "EventObject.h"
#include "FunctionObject.h"

#include <mshtmdid.h>
#include <comdef.h>
#include <stdio.h>

 #define _CRT_SECURE_NO_DEPRECATE

CEventObject::CEventObject()
{	
	m_spOnSubmitEventDispatch =	CFunctionObject<CEventObject>::CreateEventFunctionObject(this, &CEventObject::fnCallBackOnSubmit,DISPID_ONSUBMIT);
	m_spKeyDownEventDispatch = CFunctionObject<CEventObject>::CreateEventFunctionObject(this, &CEventObject::fnCallBackOnKeyPress,DISPID_KEYPRESS);

	m_pbOnSubmit = NULL;
}

CEventObject::~CEventObject()
{

}

void CEventObject::fnCallBackOnKeyPress(DISPID id, VARIANT *pvtResult) // IE Callback
{
	HRESULT hr;
	long lKeyCode = 0;

	CComPtr<IHTMLEventObj>		 eventObj;
	CComPtr<IHTMLElement>		 htmlEle;
	CComPtr<IHTMLInputElement>   inputEle;
	CComPtr<IHTMLWindow2>		 iWin2;
	
	hr = m_spHTMLDocument2->get_parentWindow(&iWin2);
	if (FAILED(hr) || iWin2 == NULL)
	{
		return;
	}
	
	hr = iWin2->get_event(&eventObj);
	if (FAILED(hr) || iWin2 == NULL)
	{
		return;
	}
	hr = eventObj->get_keyCode( &lKeyCode );
	if(FAILED(hr))
	{
		return;
	}
	
	if (IsWindowVisible(m_pInputLogDlg->m_hWnd))
	{
		//todo : Virtual Key Code 값 Range 체크 해서 별도로 출력할것
		unsigned int scanCode = MapVirtualKeyW(lKeyCode, MAPVK_VK_TO_VSC);
		long lParamValue = (scanCode << 16);
		char inputKey[10] = { 0, };

		int result = GetKeyNameText(lParamValue, inputKey, 1024);

		char bufferString[1024] = { 0, };
		char bufferString2[1024] = { 0, };

		m_pInputLogDlg->GetDlgItemText(IDC_EDIT_putdown, bufferString, 1024);

		sprintf_s(bufferString2, 1024, "%s (%s) ", bufferString, inputKey);

		m_pInputLogDlg->SetDlgItemText(IDC_EDIT_putdown, bufferString2);
	}

	hr = m_spHTMLDocument2->get_parentWindow(&iWin2);
	if (FAILED(hr) || iWin2 == NULL)
	{
		return;
	}
	
	hr = iWin2->get_event(&eventObj);
	if (FAILED(hr) || iWin2 == NULL)
	{
		return;
	}
	hr = eventObj->get_srcElement(&htmlEle);
	if(FAILED(hr))
	{
		return;
	}
	
	hr = htmlEle->QueryInterface(IID_IHTMLInputElement, (void**)&inputEle);
	if(FAILED(hr))
	{
		return;
	}
	
	if (IsWindowVisible(m_pInputLogDlg->m_hWnd))
	{
		m_pInputLogDlg->inputEle = inputEle;
	}	
}

void CEventObject::fnCallBackOnSubmit(DISPID id, VARIANT *pvtResult)
{
	HRESULT hr;

	BSTR bstrURL;
	m_spHTMLDocument2->get_URL(&bstrURL);

	BSTR bstrWebName;
	m_spHTMLDocument2->get_title(&bstrWebName); 

	long len = 0;
	m_spFormElement->get_length(&len);							//Form -> element get
	
	for (int j  = 0 ; j <len ; j++)
	{
	
		BSTR bstrName;
		BSTR bstrType;
		BSTR bstrValue;
		
		CComPtr<IDispatch> dispInput;
		CComQIPtr<IHTMLInputElement,&IID_IHTMLInputElement> spInputElement;
		
		hr = m_spFormElement->item(CComVariant(j),CComVariant(j),&dispInput);		//InputElement get
		if (FAILED(hr))
		{
			continue;
		}
		
		spInputElement = dispInput;									//dispatch를 InputElement로 변환
		if (!spInputElement)
		{
			continue;
		}
		spInputElement->get_type(&bstrType);
		spInputElement->get_name(&bstrName);
		spInputElement->get_value(&bstrValue);
	
		if (!(_bstr_t(bstrValue).operator char*()))			//Value 값이 없는 것들은 출력하지 않음.
		{
			continue;
		}
	}
	
	if (IsWindowVisible(m_pInputLogDlg->m_hWnd))
	{
		char bufferString[1024] = {0,};
		char bufferString2[1024] = {0,};
		
		sprintf_s(bufferString2,"<사이트이름> : %s <URL주소> : %s", (_bstr_t(bstrWebName).operator char*()), (_bstr_t(bstrURL).operator char*()));
		m_pInputLogDlg->SetDlgItemText(IDC_EDIT_Value,bufferString2);
		
	}
}

int CEventObject::EventPut_Submit(IHTMLFormElement *pIHTMLFormElement)
{
	VARIANT vtPutEvent;
	
	vtPutEvent.vt = VT_DISPATCH;
	vtPutEvent.pdispVal = m_spOnSubmitEventDispatch;
	
	m_spHTMLDocument2->put_onkeydown(vtPutEvent);
	pIHTMLFormElement->put_onsubmit(vtPutEvent); 
		
	return 1;
}

int CEventObject::EventPut_KeyCode()
{
	VARIANT vtPutEvent;

	vtPutEvent.vt = VT_DISPATCH;
	vtPutEvent.pdispVal = m_spKeyDownEventDispatch;
	m_spHTMLDocument2->put_onkeydown(vtPutEvent);
	
	return 1;
}
