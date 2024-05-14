#include "stdafx.h"
#include "CJsonArray.h"

CJsonArray::CJsonArray()
{
	m_bSelected = false;
	m_bHover = false;

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

	m_evtSet.addEvent(EVENTID(EventJsonArrayLButtonDown));
	m_evtSet.addEvent(EVENTID(EventJsonArrayLButtonUp));
	m_evtSet.addEvent(EVENTID(EventJsonArrayMouseMoveing));
	m_evtSet.addEvent(EVENTID(EventJsonArrayLBDbClk));

	m_sstrKey = L"JSON数组";

	m_pObjParent = NULL;
}

CJsonArray::~CJsonArray()
{
	//
}

LRESULT CJsonArray::OnCreate(LPVOID)
{
	return __super::OnCreate(NULL);
}

void CJsonArray::OnPaint(IRenderTarget* pRT)
{
	pRT->SetAntiAlias(TRUE);
	CRect rc;
	GetClientRect(&rc);

	CRect rcReal(rc);
	//rcReal.DeflateRect(2, 2, 2, 2);

	CAutoRefPtr<IBrush> brush, oldbrush;
	pRT->CreateSolidColorBrush(RGBA(180, 180, 180, 100), &brush);
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

	pRT->DrawText(m_sstrKey, -1, (LPRECT)rcReal, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
}

void CJsonArray::OnLButtonDown(UINT nFlags, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);

	m_ptDown = point;
	m_bSelected = true;

	EventJsonArrayLButtonDown evt(this);
	FireEvent(evt);
}

void CJsonArray::OnLButtonUp(UINT nFlags, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);

	EventJsonArrayLButtonUp evt(this);
	EcPosType posType = HitPos(point);
	evt.ptDown = m_ptDown;
	evt.ptMove = point;
	evt.m_ecPosType = posType;
	FireEvent(evt);
}

void CJsonArray::OnMouseMove(UINT nFlags, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);

	EcPosType posType = HitPos(point);
	ShowCursor(posType);

	if ((nFlags & MK_LBUTTON))
	{
		//fire event
		EventJsonArrayMouseMoveing evt(this);
		evt.ptDown = m_ptDown;
		evt.ptMove = point;
		evt.m_ecPosType = posType;
		FireEvent(evt);
	}

	Invalidate();
}

void CJsonArray::OnMouseHover(WPARAM wParam, CPoint ptPos)
{
	SetMsgHandled(FALSE);

	m_bHover = true;

	Invalidate();
}

void CJsonArray::OnMouseLeave()
{
	SetMsgHandled(FALSE);

	m_bHover = false;

	Invalidate();
}

void CJsonArray::OnLButtonDblClk(UINT nFlags, SOUI::CPoint point)
{
	SetMsgHandled(FALSE);

	EventJsonArrayLBDbClk evt(this);
	FireEvent(evt);
}

EcPosType CJsonArray::HitPos(SOUI::CPoint& pt)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_rcPos[i].PtInRect(pt))
			return EcPosType(i);
	}

	return EcPosType::Null;
}

void CJsonArray::ShowCursor(EcPosType ePos)
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

void CJsonArray::setSelect(bool bSelect)
{
	m_bSelected = bSelect;
	Invalidate();
}


void CJsonArray::setPosX(int nX)
{
	m_nX = nX;
}

int CJsonArray::getPosX()
{
	return m_nX;
}

void CJsonArray::setPosY(int nY)
{
	m_nY = nY;
}

int CJsonArray::getPosY()
{
	return m_nY;
}

void CJsonArray::setKey(SStringW sstrKey)
{
	m_sstrKey = sstrKey;
	Invalidate();
}

SStringW CJsonArray::getKey()
{
	return m_sstrKey;
}

void CJsonArray::setValue(SStringW sstrValue)
{
	m_sstrValue = sstrValue;
	Invalidate();
}

SStringW CJsonArray::getValue()
{
	return m_sstrValue;
}

void CJsonArray::setObjParent(SWindow* pParent)
{
	m_pObjParent = pParent;
}

SWindow* CJsonArray::getObjParent()
{
	return m_pObjParent;
}

void CJsonArray::addRootChild(SWindow* pWindow)
{
	m_vecChild.push_back(pWindow);
}

std::vector<SWindow*> CJsonArray::getRootChildren()
{
	return m_vecChild;
}