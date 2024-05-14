// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
}

CMainDlg::~CMainDlg()
{
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	return 0;
}

void CMainDlg::OnLanguageBtnCN()
{
	OnLanguage(1);
}
void CMainDlg::OnLanguageBtnJP()
{
	OnLanguage(0);
}
void CMainDlg::OnLanguage(int nID)
{
	ITranslatorMgr *pTransMgr = SApplication::getSingletonPtr()->GetTranslator();
	SASSERT(pTransMgr);
	bool bCnLang = nID == 1;

	pugi::xml_document xmlLang;
	if (SApplication::getSingletonPtr()->LoadXmlDocment(xmlLang, bCnLang ? _T("translator:lang_cn") : _T("translator:lang_jp")))
	{
		CAutoRefPtr<ITranslator> lang;
		pTransMgr->CreateTranslator(&lang);
		lang->Load(&xmlLang.child(L"language"), 1);//1=LD_XML
		TCHAR lngName[TR_MAX_NAME_LEN] = {0};
		lang->GetName(lngName);
		pTransMgr->SetLanguage(lngName);
		pTransMgr->InstallTranslator(lang);
		SDispatchMessage(UM_SETLANGUAGE,0,0);
	}
}

//TODO:消息映射
void CMainDlg::OnClose()
{
	SNativeWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

void CMainDlg::OnBnClickRoot()
{
	CBoxContainer* pContainer = FindChildByName2<CBoxContainer>(L"containerbox");
	pContainer->SetAddType(JsonRoot);
}

void CMainDlg::OnBnClickArray()
{
	CBoxContainer* pContainer = FindChildByName2<CBoxContainer>(L"containerbox");
	pContainer->SetAddType(JsonArray);
}

void CMainDlg::OnBnClickObject()
{
	CBoxContainer* pContainer = FindChildByName2<CBoxContainer>(L"containerbox");
	pContainer->SetAddType(JsonObj);
}

void CMainDlg::OnBnClickSubObject()
{
	CBoxContainer* pContainer = FindChildByName2<CBoxContainer>(L"containerbox");
	pContainer->SetAddType(JsonSubObj);
}

void CMainDlg::OnBnClickSelected()
{
	SEdit* pPath = FindChildByName2<SEdit>(L"edit_path");
	CFileDialogEx openDlg(TRUE, _T("文件"), 0, 6,
		_T("Excel files(*.xls|*.xlsx|*.xlsm)\0*.xls;*.xlsx;*.xlsm\0All files (*.*)\0*.*\0\0"));
	if (openDlg.DoModal() == IDOK)
	{
		SStringW sstrFile = openDlg.m_szFileName;
		pPath->SetWindowTextW(sstrFile);
		//只支持xlsx文件
		Book* pBook = xlCreateXMLBook();
		if (pBook)
		{
			pBook->setKey(L"libxl", L"windows-28232b0208c4ee0369ba6e68abv6v5i3");
			SStringW sstrFilePath = S_CW2W(sstrFile, CP_UTF8);
			if (pBook->load(sstrFile))
			{
				Sheet* sheet = pBook->getSheet(0);
				if (sheet)
				{
					//获取表头  第一行为表头
					std::vector<SStringW> vecTitles;
					for (int i = 0; i < sheet->lastCol(); i++)
					{
						SStringW sstrTitle = sheet->readStr(0, i);
						vecTitles.push_back(sstrTitle);
					}

					//获取数据
					std::map<SStringW, std::vector<SStringW>> mapTitleDatas;
					for (int col = 0; col < sheet->lastCol(); col++)
					{
						std::vector<SStringW> vecDatas;
						for (int row = 1; row < sheet->lastRow(); row++)
						{
							SStringW sstrData = sheet->readStr(row, col);
							vecDatas.push_back(sstrData);
						}
						mapTitleDatas[vecTitles[col]] = vecDatas;
						CGlobalUnits::GetInstance()->m_mapTitleDatas[vecTitles[col]] = vecDatas;
					}
				}
			}
		}
	}
}

void CMainDlg::OnBnClickJsonView()
{
	CBoxContainer* pContainer = FindChildByName2<CBoxContainer>(L"containerbox");
	pContainer->GeneralJson();
}