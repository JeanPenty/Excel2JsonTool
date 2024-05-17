#include "stdafx.h"
#include "CObjEdit.h"


#include "CJsonSubObject.h"

CObjEdit::CObjEdit()
{
	m_bChanged = false;

	m_nWid = 0;
	m_nHei = 0;

	m_evtSet.addEvent(EVENTID(EventObjEditEnChange));
}

CObjEdit::~CObjEdit()
{
}

void CObjEdit::SetHost(IEditHost* _ieditHost)
{
	m_pHost = _ieditHost;
}

BOOL CObjEdit::IsContainPoint(const POINT& pt, BOOL bClientOnly) const
{
	if (!m_pHost->canProcessMsg())
		return FALSE;
	return __super::IsContainPoint(pt, bClientOnly);
}

LRESULT CObjEdit::OnCreate(LPVOID)
{
	LRESULT bRet = __super::OnCreate(NULL);
	if (bRet == 0)
	{
		unsigned oldMask = SSendMessage(EM_GETEVENTMASK, 0, 0);
		SSendMessage(EM_SETEVENTMASK, 0, oldMask | ENM_REQUESTRESIZE | ENM_CHANGE);
		GetEventSet()->subscribeEvent(EVT_RE_NOTIFY, Subscriber(&CObjEdit::OnEditNotify, this));
		GetEventSet()->subscribeEvent(EVT_KILLFOCUS, Subscriber(&CObjEdit::OnKillFocus, this));
	}
	return bRet;
}

bool CObjEdit::OnKillFocus(EventArgs* e)
{
	GetEventSet()->setMutedState(true);
	__super::OnKillFocus(m_swnd);
	if (GetWindowText().IsEmpty())
	{
#ifndef _DEBUG
		GetParent()->DestroyChild(this);
#endif // !_DEBUG
	}
	GetEventSet()->setMutedState(false);
	return true;
}

bool CObjEdit::OnEditNotify(EventArgs* e)
{
	EventRENotify* pEvtNotify = sobj_cast<EventRENotify>(e);
	switch (pEvtNotify->iNotify)
	{
	case EN_CHANGE:
	{
		m_bChanged = true;
		SSendMessage(EM_SETTARGETDEVICE, 0, 1);
		SSendMessage(EM_REQUESTRESIZE, 0, 0);
	}
	break;
	case EN_REQUESTRESIZE:
		if (m_bChanged)
		{
			REQRESIZE* prqs = (REQRESIZE*)(pEvtNotify->pv);
			m_nHei = prqs->rc.bottom - prqs->rc.top;
			m_nWid = prqs->rc.right - prqs->rc.left;

			CRect Margin = GetStyle().GetMargin();
			m_nWid += Margin.left + Margin.right;
			m_nHei += Margin.top + Margin.bottom;
			UpdataSize();
			m_bChanged = false;

			SStringW sstrContent = GetWindowText();

			EventObjEditEnChange evt(this);
			evt.m_pWindow = GetParent();
			evt.m_sstrContent = sstrContent;
			evt.m_nWid = m_nWid;
			evt.m_nHei = m_nHei;
			FireEvent(evt);
		}
		UpdataSize();
		break;
	}
	return true;
}

BOOL CObjEdit::OnSetCursor(const CPoint& pt)
{
	if (!__super::OnSetCursor(pt))
	{
		SetCursor(GETRESPROVIDER->LoadCursor(IDC_SIZEALL));
	}
	return TRUE;
}

void CObjEdit::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	__super::OnNcLButtonDown(nHitTest, point);
	SetCapture();
// 	m_bDraging = TRUE;
// 	m_ptClick = point;
	BringWindowToTop();
}

void CObjEdit::OnNcMouseMove(UINT nHitTest, CPoint point)
{
// 	if (m_bDraging)
// 	{
// 		CRect rcWnd = GetWindowRect();
// 		CPoint pt = rcWnd.TopLeft() + (point - m_ptClick);
// 		//((SSnapshotCtrl*)GetParent())->GetEtMovePos(pt, rcWnd.Width(),rcWnd.Height());
// 		((SSnapshotCtrl*)GetParent())->GetEtMovePos(pt, 60, 60);
// 		//rcWnd.MoveToXY(pt);			
// 		//Move(rcWnd);
// 		SStringT pos;
// 		pos.Format(L"%d,%d", pt.x, pt.y);
// 		SetAttribute(L"pos", pos);
// 		int max_wid = ((SSnapshotCtrl*)GetParent())->GetEtMaxWid(pt.x);
// 		if (max_wid < rcWnd.Width())
// 		{
// 			SStringT width;
// 			width.Format(L"%d", max_wid);
// 			SetAttribute(L"width", width);
// 			//强制更新自己的m_rcWindow;
// 			GetLayout()->LayoutChildren(GetParent());
// 		}
// 		SSendMessage(EM_SETTARGETDEVICE, 0, 1);
// 		bChanged = true;
// 		SSendMessage(EM_REQUESTRESIZE, 0, 0);
// 
// 		m_ptClick = point;
// 		GetParent()->Invalidate();
// 	}
}

void CObjEdit::UpdataSize()
{
	CRect rcWnd = GetWindowRect();
	SWindow* pParent = GetParent();
	SStringW sstrClassName = pParent->GetObjectClass();
	if (sstrClassName == L"json_subobject")
	{
		CJsonSubObject* pObj = sobj_cast<CJsonSubObject>(pParent);
		CRect rcObj = pObj->GetWindowRect();
		rcObj.DeflateRect(15, 15, 15, 15);

		//obj长宽
		int nObjWidth = rcObj.Width();
		int nObjHeight = rcObj.Height();

		int nMax;
		nMax = max(m_nHei + 30, 60);
		nMax = min(nObjWidth, nMax);

		SStringW sstrHeight;
		sstrHeight.Format(L"%d", nMax);
		SetAttribute(L"height", sstrHeight);

		GetLayout()->LayoutChildren(GetParent());
	}

	if (rcWnd.Height() < m_nHei + 30)
	{
		//计算edit可用的最大宽高


// 		int max_wid = ((SWindow*)GetParent())->GetEtMaxHei(rcWnd);
// 		int iMax;
// 		SStringT height;
// 		iMax = max(m_iHei + 30, 60);
// 		iMax = min(max_wid, iMax);
// 		height.Format(L"%d", iMax);
// 		SetAttribute(L"height", height);
	}
	else
	{
// 		SStringT height;
// 		int iMax;
// 		iMax = max(m_iHei + 30, 60);
// 		height.Format(L"%d", iMax);
// 		SetAttribute(L"height", height);
	}
	//增大
	if (rcWnd.Width() < m_nWid + 30)
	{
// 		int max_wid = ((SSnapshotCtrl*)GetParent())->GetEtMaxWid(rcWnd);
// 		int iMax;
// 		SStringT width;
// 		iMax = max(m_iWid + 30, 60);
// 		iMax = min(max_wid, iMax);
// 		width.Format(L"%d", iMax);
// 		SetAttribute(L"width", width);
// 		if (iMax == max_wid)
// 		{
// 			//强制更新自己的m_rcWindow;
// 			GetLayout()->LayoutChildren(GetParent());
// 			SSendMessage(EM_SETTARGETDEVICE, 0, 0);
// 		}
	}
	else
	{
// 		SStringT width;
// 		int iMax;
// 		iMax = max(m_iWid + 30, 60);
// 		width.Format(L"%d", iMax);
// 		SetAttribute(L"width", width);
// 		SSendMessage(EM_SETTARGETDEVICE, 0, 1);
	}
}

void CObjEdit::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	//m_bDraging = FALSE;
	ReleaseCapture();
	CRect parentRc = GetParent()->GetClientRect();
	CRect rcWnd = GetWindowRect();
	CPoint relpos = rcWnd.TopLeft() - parentRc.TopLeft();
	SStringT pos;
	pos.Format(L"%d,%d", relpos.x, relpos.y);
	SetAttribute(L"pos", pos);

	//Move(NULL);
	SSendMessage(EM_SETTARGETDEVICE, 0, 1);

	//bChanged = true;
	SSendMessage(EM_REQUESTRESIZE, 0, 0);
}

void CObjEdit::OnNcPaint(IRenderTarget* pRT)
{
	if (!IsVisible(TRUE)) return;
	if (!m_style.GetMargin().IsRectNull() && IsFocused())
	{
		CAutoRefPtr<IPen> pen, oldpen;
		pRT->CreatePen(PS_DASHDOT, RGBA(0, 0, 0, 255), 1, &pen);
		pRT->SelectObject(pen, (IRenderObj**)&oldpen);
		CRect rcWindow = GetWindowRect();
		//CRect rcClient = GetClientRect();
		rcWindow.InflateRect(0, 0, 1, 1);
		pRT->DrawRectangle(rcWindow);
		pRT->SelectObject(oldpen, NULL);
	}
}

BOOL CObjEdit::OnEraseBkgnd(IRenderTarget* pRT)
{
	return TRUE;
}

void CObjEdit::OnMouseHover(WPARAM wParam, CPoint ptPos)
{
	SetFocus();
}

void CObjEdit::OnMouseLeave()
{
// 	if (!m_bDraging)
// 		KillFocus();
}

int CObjEdit::getWid()
{
	return m_nWid;
}

int CObjEdit::getHei()
{
	return m_nHei;
}

void CObjEdit::insertBreak()
{
	SSendMessage(WM_KEYDOWN, VK_RETURN, 0);
	SSendMessage(WM_KEYUP, VK_RETURN, 0);
}