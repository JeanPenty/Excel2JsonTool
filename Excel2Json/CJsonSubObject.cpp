#include "stdafx.h"
#include "CJsonSubObject.h"

CJsonSubObject::CJsonSubObject()
{
	m_bDrawBorder = false;

	m_pEdit = NULL;

	m_bSelected = false;

	m_evtSet.addEvent(EVENTID(EventJsonSubObjectResize));
}

CJsonSubObject::~CJsonSubObject()
{
	//
}


LRESULT CJsonSubObject::OnCreate(LPVOID)
{
	return __super::OnCreate(NULL);
}

void CJsonSubObject::OnPaint(IRenderTarget* pRT)
{
	pRT->SetAntiAlias(TRUE);
	CRect rc;
	GetClientRect(&rc);

	CRect rcReal(rc);
	rcReal.DeflateRect(2, 2, 2, 2);

	CAutoRefPtr<IBrush> brush, oldbrush;
	pRT->CreateSolidColorBrush(RGBA(60, 60, 60, 100), &brush);
	pRT->SelectObject(brush, (IRenderObj**)&oldbrush);
	pRT->FillRectangle(&rcReal);
	pRT->SelectObject(oldbrush, NULL);
	
	//绘制操作border
	if (m_bSelected)
	{
		CAutoRefPtr<IPen> pen, oldpen;
		pRT->CreatePen(PS_SOLID, RGBA(0, 0, 255, 255), 2, &pen);
		pRT->SelectObject(pen, (IRenderObj**)&oldpen);

		CRect rcBorder(rc);
		pRT->DrawRectangle(rcBorder);
		pRT->SelectObject(oldpen, NULL);
	}

	SStringW sstrContent = L"JSON子对象";
	//pRT->DrawText(sstrContent, -1, (LPRECT)rcReal, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
}

bool CJsonSubObject::OnEventObjEditEnChange(EventObjEditEnChange* pEvt)
{
	SStringW sstrContent = m_pEdit->GetWindowTextW();
	int nEditWid = pEvt->m_nWid;
	int nEditHei = pEvt->m_nHei;

	EventJsonSubObjectResize evt(this);
	evt.m_nNewWidth = nEditWid;
	evt.m_nNewHeight = nEditHei;
	FireEvent(evt);

	return true;
}


void CJsonSubObject::OnLButtonDblClk(UINT nFlags, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);

	CRect rcClient = GetClientRect();

	if (!m_pEdit)
	{
		m_pEdit = (CObjEdit*)SApplication::getSingleton().CreateWindowByName(L"objedit");
		SASSERT(m_pEdit);
		m_pEdit->SetHost(this);
		SApplication::getSingleton().SetSwndDefAttr(m_pEdit);
		this->InsertChild(m_pEdit);
		m_pEdit->SSendMessage(WM_CREATE);
		this->InsertChild(m_pEdit);
		SStringT etPos;
		etPos.Format(_T("15,15,@%d, @%d"), rcClient.Width() - 30, rcClient.Height() - 30);

// 		SStringW sstrEditXML;
// 		sstrEditXML.Format(L"<objedit pos=\"%s\" multiLines=\"1\" wordWrap=\"1\"></objedit>", etPos);
// 		CObjEdit* pEdit = (CObjEdit*)CreateChildren(sstrEditXML);
// 		this->InsertChild(pEdit);
// 		m_pEdit = pEdit;
// 		m_pEdit->SetHost(this);

// 		m_pEdit->SetAttribute(L"pos", L"|0,|0");
// 		m_pEdit->SetAttribute(L"offset", L"0.5,-0.5");
		m_pEdit->SetAttribute(L"pos", etPos);
		m_pEdit->SetAttribute(L"multiLines", L"1");
		m_pEdit->SetAttribute(L"transparent", L"1");
		m_pEdit->SetAttribute(L"wordWrap", L"1");
//  		m_pEdit->SetAttribute(L"hscrollBar", L"0");

//		m_pEdit->SetAttribute(L"inset", L"15,15,15,15");
// 		m_pEdit->SetAttribute(L"wantReturn", L"1");
		m_pEdit->SetAttribute(L"colorBkgnd", L"#FF00FF");
 		

		m_pEdit->GetEventSet()->subscribeEvent(&CJsonSubObject::OnEventObjEditEnChange, this);
	}
	m_pEdit->BringWindowToTop();
	m_pEdit->EnableWindow(TRUE);
	m_pEdit->SetFocus();
}

void CJsonSubObject::OnLButtonDown(UINT nFlags, SOUI::CPoint point)
{
	SetCapture();
	if (m_pEdit)
	{
		m_pEdit->KillFocus();
		m_pEdit->EnableWindow(FALSE);
		m_bSelected = true;
	}
}

void CJsonSubObject::setSelect(bool bSelect)
{
	m_bSelected = bSelect;

	if (!bSelect)
	{
		if (m_pEdit)
		{
			m_pEdit->EnableWindow(FALSE);
		}
	}

	Invalidate();
}

void CJsonSubObject::editInsertBreak()
{
	m_pEdit->insertBreak();
}

void CJsonSubObject::setEditSize()
{
	CRect rcClient = GetClientRect();

	//设置edit的size
	SStringW sstrSize;
	sstrSize.Format(L"15,15, @%d,@%d", rcClient.Width() - 30, rcClient.Height() - 30);
	m_pEdit->SetAttribute(L"pos", sstrSize);
}

void CJsonSubObject::setWidth(int nWid)
{
	m_nWidth = nWid;
}

void CJsonSubObject::setHeight(int nHei)
{
	m_nHeight = nHei;
}