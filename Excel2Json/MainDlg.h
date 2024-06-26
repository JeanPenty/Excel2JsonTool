// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>

#include "CBoxContainer.h"

#include "CGlobalUnits.h"

class CMainDlg : public SHostWnd
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose();
	void OnMaximize();
	void OnRestore();
	void OnMinimize();
	void OnSize(UINT nType, CSize size);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

	void OnBnClickRoot();
	void OnBnClickArray();
	void OnBnClickObject();
	void OnBnClickSubObject();

	void OnBnClickSelected();

	void OnBnClickJsonView();
protected:
	void OnLanguage(int nID);
	void OnLanguageBtnCN();
	void OnLanguageBtnJP();
	//soui消息
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_close", OnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
		EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
		EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
		EVENT_NAME_COMMAND(L"zh_cn", OnLanguageBtnCN)
		EVENT_NAME_COMMAND(L"jp", OnLanguageBtnJP)

		EVENT_NAME_COMMAND(L"btn_root", OnBnClickRoot)
		EVENT_NAME_COMMAND(L"btn_array", OnBnClickArray)
		EVENT_NAME_COMMAND(L"btn_obj", OnBnClickObject)
		EVENT_NAME_COMMAND(L"btn_subobj", OnBnClickSubObject)
		
		EVENT_NAME_COMMAND(L"btn_selected", OnBnClickSelected)

		EVENT_NAME_COMMAND(L"btn_jsonview", OnBnClickJsonView)
	EVENT_MAP_END()
		
	//HostWnd真实窗口消息处理
	BEGIN_MSG_MAP_EX(CMainDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
};
