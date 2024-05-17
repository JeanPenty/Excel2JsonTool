#include "stdafx.h"
#include "CJsonRoot.h"

CJsonRoot::CJsonRoot()
{
	m_bSelected = false;
	m_bHover = false;
	m_bLBDown = false;

	m_hCursorSelect = LoadCursor(NULL, IDC_SIZEALL);
	m_hCursorTopRight = LoadCursor(NULL, IDC_SIZENESW);
	m_hCursorBottomRight = LoadCursor(NULL, IDC_SIZENWSE);
	m_hCursorTop = LoadCursor(NULL, IDC_SIZENS);
	m_hCursorBottom = LoadCursor(NULL, IDC_SIZENS);
	m_hCursorLeft = LoadCursor(NULL, IDC_SIZEWE);
	m_hCursorRight = LoadCursor(NULL, IDC_SIZEWE);
	m_hCursorTopLeft = LoadCursor(NULL, IDC_SIZENWSE);
	m_hCursorBottomLeft = LoadCursor(NULL, IDC_SIZENESW);
	m_hCursorHand = LoadCursor(NULL, IDC_HAND);
	m_hCursorArrow = LoadCursor(NULL, IDC_ARROW);

	m_evtSet.addEvent(EVENTID(EventJsonRootLButtonDown));
	m_evtSet.addEvent(EVENTID(EventJsonRootLButtonUp));
	m_evtSet.addEvent(EVENTID(EventJsonRootMouseMoveing));

	m_pObjParent = NULL;

	m_sstrKey = L"JSON根对象";
}

CJsonRoot::~CJsonRoot()
{
	//
}

LRESULT CJsonRoot::OnCreate(LPVOID)
{
	return __super::OnCreate(NULL);
}

void CJsonRoot::OnPaint(IRenderTarget* pRT)
{
	pRT->SetAntiAlias(TRUE);
	CRect rc;
	GetWindowRect(&rc);

	CRect rcReal(rc);
	//rcReal.DeflateRect(2, 2, 2, 2);

	CAutoRefPtr<IBrush> brush, oldbrush;
	pRT->CreateSolidColorBrush(RGBA(246, 160, 77, 100), &brush);
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

	//绘制操作点
	if (m_bSelected)
	{
		CAutoRefPtr<IPen> pen, oldpen;
		CAutoRefPtr<IBrush> brush, oldbrush;
		pRT->CreatePen(PS_SOLID, RGBA(0, 0, 255, 20), 1, &pen);
		pRT->CreateSolidColorBrush(RGBA(255, 0, 0, 255), &brush);
		pRT->SelectObject(pen, (IRenderObj**)&oldpen);
		pRT->SelectObject(brush, (IRenderObj**)&oldbrush);


		SOUI::CPoint center = rc.CenterPoint();
		// 上左 方块
		m_rcPos[(int)EcPosType::TopLeft].SetRect(rc.left, rc.top, rc.left + 8, rc.top + 8);
		// 上中 方块
		m_rcPos[(int)EcPosType::TopCenter].SetRect(center.x - 4, rc.top, center.x + 4, rc.top + 8);
		// 上右 方块
		m_rcPos[(int)EcPosType::TopRight].SetRect(rc.right - 8, rc.top, rc.right, rc.top + 8);
		// 右中 方块
		m_rcPos[(int)EcPosType::RightCenter].SetRect(rc.right - 8, center.y - 4, rc.right, center.y + 4);
		// 下右 方块
		m_rcPos[(int)EcPosType::BottomRight].SetRect(rc.right - 8, rc.bottom - 8, rc.right, rc.bottom);
		// 下中 方块
		m_rcPos[(int)EcPosType::BottomCenter].SetRect(center.x - 4, rc.bottom - 8, center.x + 4, rc.bottom);
		// 下左 方块
		m_rcPos[(int)EcPosType::BottomLeft].SetRect(rc.left, rc.bottom - 8, rc.left + 8, rc.bottom);
		// 左中 方块
		m_rcPos[(int)EcPosType::LeftCenter].SetRect(rc.left, center.y - 4, rc.left + 8, center.y + 4);

		for (int i = 0; i < 8; ++i)
		{
			CRect rcDot(m_rcPos[i]);
			//pRT->FillRectangle(rcDot);
		}

		pRT->SelectObject(oldpen, NULL);
		pRT->SelectObject(oldbrush, NULL);
	}


	//绘制hover边框
	if (m_bHover && !m_bSelected)
	{
		CAutoRefPtr<IPen> pen, oldpen;
		pRT->CreatePen(PS_SOLID, RGBA(100, 100, 100, 255), 2, &pen);
		pRT->SelectObject(pen, (IRenderObj**)&oldpen);

		CRect rcBorder(rc);
		pRT->DrawRectangle(rcBorder);
		pRT->SelectObject(oldpen, NULL);
	}

	//绘制文本
	{
		//HDC hDC = pRT->GetDC();
		CPoint ptCenter = rcReal.CenterPoint();
		CRect rcKey(rcReal);
		rcKey.bottom = ptCenter.y;
		rcKey.DeflateRect(1, 1, 1, 1);

		CRect rcValue(rcReal);
		rcValue.top = ptCenter.y;
		rcValue.DeflateRect(1, 1, 1, 1);

		//绘制key
		SStringW sstrKeyContent;
		sstrKeyContent.Format(L"key:%s", m_sstrKey);
		//pRT->DrawText(sstrKeyContent, -1, (LPRECT)rcKey, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

		//绘制Value
		SStringW sstrValueContent;
		sstrValueContent.Format(L"value:%s", m_sstrValue);
		//pRT->DrawText(sstrValueContent, -1, (LPRECT)rcValue, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

// 		int nKeyCnt = sstrKeyContent.GetLength();
// 		int nRcKeyWidth = rcKey.Width();
// 
// 		LOGFONT lf;
// 		GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(lf), &lf);
// 		lf.lfHeight = 0;
// 		lf.lfWidth = 0;
// 		_tcscpy(lf.lfFaceName, _T("宋体"));
// 		HFONT m_font = CreateFontIndirect(&lf);
// 		HFONT oldFont = (HFONT)SelectObject(hDC, m_font);
// 
// 		::DrawText(hDC, sstrKeyContent, -1, &rcKey, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);


		DrawText(pRT, m_sstrKey, -1, &rcReal, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

// 		DrawText(pRT, sstrKeyContent, -1, &rcKey, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
// 		DrawText(pRT, sstrValueContent, -1, &rcValue, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);

// 		SelectObject(hDC, oldFont);
// 		::ReleaseDC(NULL, hDC);
	}
}

void CJsonRoot::OnLButtonDown(UINT nFlags, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);

	m_ptDown = point;

	m_bSelected = true;

	EventJsonRootLButtonDown evt(this);
	FireEvent(evt);
}

void CJsonRoot::OnLButtonUp(UINT nFlags, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);
	
	EventJsonRootLButtonUp evt(this);

	EcPosType posType = HitPos(point);

	evt.ptDown = m_ptDown;
	evt.ptMove = point;
	evt.m_ecPosType = posType;

	FireEvent(evt);
}

void CJsonRoot::OnMouseMove(UINT nFlags, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);

	EcPosType posType = HitPos(point);
	ShowCursor(posType);

	if ((nFlags & MK_LBUTTON))
	{
		//fire event
		EventJsonRootMouseMoveing evt(this);
		evt.ptDown = m_ptDown;
		evt.ptMove = point;
		evt.m_ecPosType = posType;

		FireEvent(evt);
	}

	Invalidate();
}

void CJsonRoot::OnMouseHover(WPARAM wParam, CPoint ptPos)
{
	SetMsgHandled(FALSE);

	m_bHover = true;

	Invalidate();
}

void CJsonRoot::OnMouseLeave()
{
	SetMsgHandled(FALSE);

	m_bHover = false;

	Invalidate();
}

EcPosType CJsonRoot::HitPos(SOUI::CPoint& pt)
{
	// 	CPoint pt2(pt);
	// 	TransformPoint(pt2);
	// 
	// 	for (int i = 0; i < 8; ++i)
	// 	{
	// 		if (m_rcPos[i].PtInRect(pt2))
	// 			return EcPosType(i);
	// 	}

	for (int i = 0; i < 8; ++i)
	{
		if (m_rcPos[i].PtInRect(pt))
			return EcPosType(i);
	}

	return EcPosType::Null;
}

void CJsonRoot::ShowCursor(EcPosType ePos)
{
	switch (ePos)
	{
	case EcPosType::TopLeft:
	case EcPosType::BottomRight:
		::SetCursor(m_hCursorTopLeft);
		break;
	case EcPosType::TopCenter:
	case EcPosType::BottomCenter:
		::SetCursor(m_hCursorTop);
		break;
	case EcPosType::TopRight:
	case EcPosType::BottomLeft:
		::SetCursor(m_hCursorTopRight);
		break;
	case EcPosType::LeftCenter:
	case EcPosType::RightCenter:
		::SetCursor(m_hCursorLeft);
		break;
	case EcPosType::SelectRect:
		::SetCursor(m_hCursorSelect);
		break;
	case EcPosType::Null:
	default:
		break;
	}
}

void CJsonRoot::setSelect(bool bSelect)
{
	m_bSelected = bSelect;
	Invalidate();
}

void CJsonRoot::setPosX(int nX)
{
	m_nX = nX;
}

int CJsonRoot::getPosX()
{
	return m_nX;
}

void CJsonRoot::setPosY(int nY)
{
	m_nY = nY;
}

int CJsonRoot::getPosY()
{
	return m_nY;
}

void CJsonRoot::setObjParent(SWindow* pParent)
{
	m_pObjParent = pParent;
}

SWindow* CJsonRoot::getObjParent()
{
	return m_pObjParent;
}

void CJsonRoot::addRootChild(SWindow* pWindow)
{
	m_vecChild.push_back(pWindow);
}

std::vector<SWindow*> CJsonRoot::getRootChildren()
{
	return m_vecChild;
}

void CJsonRoot::setKey(SStringW sstrKey)
{
	m_sstrKey = sstrKey;
	Invalidate();
}