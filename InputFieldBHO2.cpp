#include "stdafx.h"
#include "InputFieldBHO.h"
#include "InputFieldBHO2.h"
#include "FunctionObject.h"

static HHOOK g_hook;
InputFieldDlg g_Inputdlg;

CInputFieldBHO2::CInputFieldBHO2()
{
	eventObjList_ = new CEventObjectList;
	docComplete = FALSE;
}

CInputFieldBHO2::~CInputFieldBHO2()
{
}

HRESULT CInputFieldBHO2::SetSite(IUnknown *pUnkSite)
{
	pUnkSite->QueryInterface(IID_IWebBrowser2, reinterpret_cast<void**>(&web2_));	//�������� ������
	
    if(!web2_)
        return E_INVALIDARG;
	
    cpc_ = web2_;

    if(!cpc_)
        return E_POINTER;

	return Connect();
}

HRESULT CInputFieldBHO2::Connect()
{
	HRESULT hr;
    CComPtr<IConnectionPoint> cp;

    hr = cpc_->FindConnectionPoint(DIID_DWebBrowserEvents2,&cp);
	if (FAILED(hr))
        return hr;

	hr = cp->Advise(reinterpret_cast<IDispatch*>(this),&cookies);
	
	SetIEHook();
	if( hr == S_OK )
		refCount_++;

    return hr;

}

HRESULT CInputFieldBHO2::OnQuit()
{
    HRESULT hr;
    refCount_--;
    CComPtr<IConnectionPoint> cp;	

    OnBeforNavigate2();

    hr = cpc_->FindConnectionPoint(DIID_DWebBrowserEvents2,&cp);

    if (FAILED(hr))
        return hr;

    hr = cp->Unadvise(cookies);
    g_Inputdlg.DestroyWindow();
    UnhookWindowsHookEx(g_hook); // ����

    delete eventObjList_;
    eventObjList_ = NULL;

    return hr;
}

HRESULT CInputFieldBHO2::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pvarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    switch(dispidMember)
    {

    case DISPID_DOCUMENTCOMPLETE :
	    OnDocumentComplete(pDispParams->rgvarg[1].pdispVal);
	    break;
    case DISPID_BEFORENAVIGATE2 : 
	    if (!docComplete)
		    break;
		    
	    OnBeforNavigate2();
	    delete eventObjList_; //form����Ʈ �޸� ����
	    eventObjList_ = NULL;
	    eventObjList_ =  new CEventObjectList;	//�� ����Ʈ
		    
	    docComplete = FALSE;
	    break;

    case DISPID_ONQUIT:
	    OnQuit();
    case DISPID_NAVIGATECOMPLETE2:	// �̻��
    default:
	    break;

    }
    return S_OK;
}

HRESULT CInputFieldBHO2::SetIEHook(void)
{
    g_hook = SetWindowsHookEx( WH_KEYBOARD, reinterpret_cast<HOOKPROC>(IEKeyboardProc), NULL,GetCurrentThreadId());
    return S_OK;
}

LRESULT CALLBACK CInputFieldBHO2::IEKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)  // KeyProc Hook
{
	if (IsWindowVisible(g_Inputdlg.m_hWnd))
	{
		if (lParam > 0) 
		{		
			//todo : Virtual Key Code �� Range üũ �ؼ� ������ ����Ұ� crash�� �߻��ϴ°����� ����
			unsigned int scanCode = MapVirtualKeyW(wParam, MAPVK_VK_TO_VSC);

			long lParamValue = (scanCode << 16);
			char inputKey[10] = { 0, };

			if (GetKeyNameText(lParamValue, inputKey, 1024))
			{
                char outBuffer[1024] = { 0, };

                g_Inputdlg.GetDlgItemText(IDC_EDIT_Key, outBuffer, 1024);
                sprintf_s(outBuffer, 1024, "%s (%s) ", outBuffer, inputKey);
                g_Inputdlg.SetDlgItemText(IDC_EDIT_Key, outBuffer);
			}
		}
	}
	
    if (VK_F9 == wParam)
    {
        if (!IsWindowVisible(g_Inputdlg.m_hWnd))
        {
            g_Inputdlg.Create(GetDesktopWindow());
            g_Inputdlg.ShowWindow(SW_SHOW);
        }
        return 0L;
    }
	return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

HRESULT CInputFieldBHO2::OnDocumentComplete(IDispatch * pDisp)
{
    HRESULT hr;
    long lFormLen = 0;

    CComQIPtr<IWebBrowser2, &IID_IWebBrowser2> web2;
    hr = pDisp->QueryInterface(IID_IWebBrowser2, reinterpret_cast<void **>(&web2)); // web2
    if (FAILED(hr))
	    return S_OK;

    CComPtr<IDispatch> disp;
    CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> doc2;

    web2->get_Document(&disp);
    doc2 = disp;

    if (!doc2)
	    return S_OK;

    CComPtr<IHTMLElementCollection> eleColl;
    hr = doc2->get_forms(&eleColl);

    if (FAILED(hr))
	    return  S_OK;

    hr = eleColl->get_length(&lFormLen);

    if (FAILED(hr))
	    return  S_OK;
		    
    CComQIPtr<IHTMLFormElement> formEle;
    CEventObject * pEventObject; // �̺�Ʈ ���� 

    doc2_ = doc2;	

    pEventObject = new CEventObject;
    pEventObject->m_spHTMLDocument2 = doc2_;
    pEventObject->m_pbOnSubmit  = & docComplete;
    pEventObject->m_pInputLogDlg = &g_Inputdlg;
    pEventObject->m_spFormElement = formEle;
    pEventObject->EventPut_KeyCode();

    eventObjList_->Add(pEventObject);

    for (int i = 0; i < lFormLen ; ++i)
    {
	    CComPtr<IDispatch> disp;
	    hr = eleColl->item(CComVariant(i),CComVariant(i),&disp);
	    if (FAILED(hr))
		    continue;
	    
	    formEle = disp;
	    if (!formEle)
		    continue;

	    pEventObject = new CEventObject;

	    pEventObject->m_spHTMLDocument2 = doc2_;
	    pEventObject->m_pbOnSubmit  = & docComplete;
	    pEventObject->m_pInputLogDlg = &g_Inputdlg;
	    pEventObject->m_spFormElement = formEle;

        eventObjList_->Add(pEventObject);

	    docComplete = TRUE;
    }

    return S_OK;
}
HRESULT CInputFieldBHO2::OnBeforNavigate2(void)
{
    HRESULT hr;
    IHTMLFormElement *formEle = NULL;

    if (eventObjList_->ObjectList == NULL)
	    return S_OK;

    for (CEventObject_Node * CurrentNode = eventObjList_->ObjectList->pstrHead; CurrentNode != NULL ; CurrentNode = CurrentNode->pstrNext )
    {
  	    formEle = CurrentNode->pCEventObject->m_spFormElement; //����Ʈ���� FormElement ��������
	    if (!formEle)
		    continue;

        long len = 0;
	    hr = formEle->get_length(&len); //form���� element ���� ��������

	    if (FAILED(hr))
		    continue;
		    
	    for (int i = 0 ; i < len ; ++i)
	    {
		    CComQIPtr<IDispatch> disp;
		    CComQIPtr<IHTMLInputElement,&IID_IHTMLInputElement> inputEle;
		    BSTR fieldName;
		    BSTR fieldType;
		    BSTR fieldValue;

		    hr = formEle->item(CComVariant(i),CComVariant(i),&disp);

		    if (FAILED(hr))
			    continue;

		    inputEle = disp;

		    if (!inputEle)
			    continue;

		    inputEle->get_type(&fieldType);
		    inputEle->get_name(&fieldName);
		    inputEle->get_value(&fieldValue);
			    
		    if (!(_bstr_t(fieldValue).operator char*()))  //��������� �������� �ʴ´�
			    continue;
	    
		    if (IsWindowVisible(g_Inputdlg.m_hWnd))	 //���̾�αװ� ���������� ���̾�α׿� Input Value �����ֱ�
		    {			
                const char typeString[] = "text";
                const char typeString2[] = "password";

                if (0 == strcmp((_bstr_t(fieldType).operator char*()), typeString) || 
                    0 == strcmp((_bstr_t(fieldType).operator char*()), typeString2))
                {
                    char outBuffer[1024] = { 0, };

                    g_Inputdlg.GetDlgItemText(IDC_EDIT_GetText, outBuffer, sizeof(outBuffer));

                    if (strcmp((_bstr_t(fieldType).operator char*()), typeString) == 0)
                    {
                        sprintf_s(outBuffer, "%s Value:[%-10s]\r\n", outBuffer, (_bstr_t(fieldValue).operator char*()));
                        g_Inputdlg.SetDlgItemText(IDC_EDIT_GetText, outBuffer);
                    }

                    if (strcmp((_bstr_t(fieldType).operator char*()), typeString2) == 0)
                    {
                        sprintf_s(outBuffer, "%s PassWord:[%-10s]\r\n", outBuffer, (_bstr_t(fieldValue).operator char*()));
                        g_Inputdlg.SetDlgItemText(IDC_EDIT_GetText, outBuffer);
                    }
                }
		    }
		    
		    if (IsWindowVisible(g_Inputdlg.m_hWnd))	//���̾�αװ� ���������� ���̾�α׿� Input Value �����ֱ�
		    {
                BSTR bstrlocationName;
                web2_->get_LocationName(&bstrlocationName);

                BSTR bstrlocationURL;
                web2_->get_LocationURL(&bstrlocationURL);

                char outBuffer[1024] = { 0, };

			    sprintf_s(outBuffer,"Title : %s\r\nURL : %s \n",	(_bstr_t(bstrlocationName).operator char*()), (_bstr_t(bstrlocationURL).operator char*()));
			    g_Inputdlg.SetDlgItemText(IDC_EDIT_Value, outBuffer);
		    }

	    }
    }
    return S_OK;
}

HRESULT CInputFieldBHO2::OnDownloadComplete(void)
{
    if (!eventObjList_->ObjectList)
        return S_OK;

    CComQIPtr<IDispatch> Disp;
    web2_->get_Document(&Disp);

    return S_OK;
}