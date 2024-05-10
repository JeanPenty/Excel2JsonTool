#include "stdafx.h"
#include "CJsonRoot.h"

CJsonRoot::CJsonRoot()
{
	m_bDrawBorder = true;
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
	GetClientRect(&rc);

	CRect rcReal(rc);
	rcReal.DeflateRect(2, 2, 2, 2);

	CAutoRefPtr<IBrush> brush, oldbrush;
	pRT->CreateSolidColorBrush(RGBA(246, 160, 77, 100), &brush);
	pRT->SelectObject(brush, (IRenderObj**)&oldbrush);
	pRT->FillRectangle(&rcReal);
	pRT->SelectObject(oldbrush, NULL);

	//绘制操作border
	if (m_bDrawBorder)
	{
		CAutoRefPtr<IPen> pen, oldpen;
		pRT->CreatePen(PS_SOLID, RGBA(0, 0, 255, 255), 2, &pen);
		pRT->SelectObject(pen, (IRenderObj**)&oldpen);

		CRect rcBorder(rc);
		pRT->DrawRectangle(rcBorder);
		pRT->SelectObject(oldpen, NULL);
	}

	SStringW sstrContent = L"JSON根对象";
	pRT->DrawText(sstrContent, -1, (LPRECT)rcReal, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
}