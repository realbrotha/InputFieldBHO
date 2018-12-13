#include "stdafx.h"
#include "InputFieldDlg.h"

LRESULT InputFieldDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 1L;
}

LRESULT InputFieldDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0L;
}

LRESULT InputFieldDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);

	return 0L;
}
LRESULT InputFieldDlg::OnClickedButton1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// dlg 내용 삭제
	SetDlgItemText(IDC_EDIT_Key, "");
	SetDlgItemText(IDC_EDIT_putdown, "");
	SetDlgItemText(IDC_EDIT_GetText, "");
	SetDlgItemText(IDC_EDIT_Value, "");
	return 0L;
}