#include "stdafx.h"
#include "CJsonSettingDlg.h"

CJsonSettingDlg::CJsonSettingDlg()
	: SHostDialog(UIRES.LAYOUT.XML_SETTING)
{
}

CJsonSettingDlg::~CJsonSettingDlg(void)
{
}

BOOL CJsonSettingDlg::OnInitDialog(HWND wnd, LPARAM lInitParam)
{
	SetMsgHandled(FALSE);

	SComboBox* pCbx = FindChildByName2<SComboBox>(L"cbx_value");
	auto iter = CGlobalUnits::GetInstance()->m_mapTitleDatas.begin();
	for (; iter != CGlobalUnits::GetInstance()->m_mapTitleDatas.end(); iter++)
	{
		pCbx->InsertItem(0, iter->first, -1, 0);
	}

	SEdit* pEdit = FindChildByName2<SEdit>(L"edit_key");
	pEdit->SetWindowTextW(m_sstrKey);

	pCbx->GetCount();
	for (int i = 0; i < pCbx->GetCount(); i++)
	{
		if (m_sstrValue == pCbx->GetLBText(i))
		{
			pCbx->SetCurSel(i);
			break;
		}
	}

	return TRUE;
}

void CJsonSettingDlg::OnBnClickOK()
{
	SComboBox* pCbx = FindChildByName2<SComboBox>(L"cbx_value");
	SStringW sstrValue = pCbx->GetWindowTextW();

	SEdit* pEdit = FindChildByName2<SEdit>(L"edit_key");
	SStringW sstrKey = pEdit->GetWindowTextW();

	m_sstrKey = sstrKey;
	m_sstrValue = sstrValue;
	EndDialog(IDOK);
}

void CJsonSettingDlg::OnBnClickClose()
{
	EndDialog(IDCANCEL);
}

void CJsonSettingDlg::setKey(SStringW sstrKey)
{
	m_sstrKey = sstrKey;
}

SStringW CJsonSettingDlg::getKey()
{
	return m_sstrKey;
}

void CJsonSettingDlg::setValue(SStringW sstrValue)
{
	m_sstrValue = sstrValue;
}

SStringW CJsonSettingDlg::getValue()
{
	return m_sstrValue;
}