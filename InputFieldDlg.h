#include "resource.h"

#include <atlhost.h>
#include <stdio.h>
#include <comdef.h>

class InputFieldDlg : public CAxDialogImpl<InputFieldDlg>
{
public:

	CComQIPtr<IHTMLInputElement, &IID_IHTMLInputElement> inputEle;
	BEGIN_MSG_MAP(InputFieldDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(IDC_BUTTON1, BN_CLICKED, OnClickedButton1)
	END_MSG_MAP()
	

	enum { IDD = IDD_DLGOPEN };
	InputFieldDlg() {}
	~InputFieldDlg() {}

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClickedButton1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};
