#pragma once

#include "CGlobalUnits.h"

class CJsonSettingDlg : public SHostDialog
{
public:
	CJsonSettingDlg();
	~CJsonSettingDlg();

public:
	void OnBnClickOK();
	void OnBnClickClose();
protected:
	BOOL OnInitDialog(HWND wnd, LPARAM lInitParam);

protected:
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_ok", OnBnClickOK)
		EVENT_NAME_COMMAND(L"btn_close", OnBnClickClose)

		EVENT_MAP_END()

		BEGIN_MSG_MAP_EX(CJsonSettingDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		CHAIN_MSG_MAP(SHostDialog)
		END_MSG_MAP()

private:
	SStringW	m_sstrKey;
	SStringW	m_sstrValue;

public:
	void setKey(SStringW sstrKey);
	SStringW getKey();
	void setValue(SStringW sstrValue);
	SStringW getValue();
};

