#include "stdafx.h"
#include "CJsonSubObject.h"

CJsonSubObject::CJsonSubObject()
{
	m_bDrawBorder = false;
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
	
	//���Ʋ���border
	if (m_bDrawBorder)
	{
		CAutoRefPtr<IPen> pen, oldpen;
		pRT->CreatePen(PS_SOLID, RGBA(0, 0, 255, 255), 2, &pen);
		pRT->SelectObject(pen, (IRenderObj**)&oldpen);

		CRect rcBorder(rc);
		pRT->DrawRectangle(rcBorder);
		pRT->SelectObject(oldpen, NULL);
	}

	SStringW sstrContent = L"JSON�Ӷ���";
	pRT->DrawText(sstrContent, -1, (LPRECT)rcReal, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE);
}