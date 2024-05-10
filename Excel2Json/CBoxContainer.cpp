#include "stdafx.h"
#include "CBoxContainer.h"

CBoxContainer::CBoxContainer(void)
{
}

CBoxContainer::~CBoxContainer(void)
{
}

void CBoxContainer::OnPaint(IRenderTarget* pRT)
{
	pRT->SetAntiAlias(FALSE);

	//ªÊ÷∆—°‘Ò«¯”Ú
	if (!m_rcDrawArea.IsRectEmpty())
	{
		COLORREF crDrawAreaBorder = RGBA(22, 119, 189, 100);
		CAutoRefPtr<IPen> pen, oldpen;
		pRT->CreatePen(PS_SOLID, crDrawAreaBorder, 1, &pen);
		pRT->SelectObject(pen, (IRenderObj**)&oldpen);
		pRT->DrawRectangle(m_rcDrawArea);
		pRT->SelectObject(oldpen, NULL);
	}
}

void CBoxContainer::OnLButtonDown(UINT nFlags, SOUI::CPoint point)
{
	m_ptDown = point;

	switch (m_curEcObjType)
	{
	case Null:
		break;
	case JsonRoot:
		break;
	case JsonArray:
		break;
	case JsonObj:
		break;
	case JsonSubObj:
		break;
	default:
		break;
	}
}

void CBoxContainer::OnLButtonUp(UINT nFlags, SOUI::CPoint point)
{
	//m_curEcObjType = Null;
	m_rcDrawArea.SetRectEmpty();
}

void CBoxContainer::OnMouseMove(UINT nFlags, SOUI::CPoint point)
{
	if (m_curEcObjType == Null)
	{
		if ((nFlags & MK_LBUTTON))
		{
			m_rcDrawArea.SetRect(m_ptDown, point);
			m_rcDrawArea.NormalizeRect();
		}
	}

	Invalidate();
}

void CBoxContainer::OnLButtonDblClk(UINT nFlags, SOUI::CPoint point)
{
	CRect rcClient;
	this->GetClientRect(&rcClient);
	SOUI::CPoint pt;
	pt.x = point.x - rcClient.left;
	pt.y = point.y - rcClient.top;

	switch (m_curEcObjType)
	{
	case Null:
		break;
	case JsonRoot:
	{
		CJsonRoot* pRoot = (CJsonRoot*)SApplication::getSingleton().CreateWindowByName(L"json_root");
		SASSERT(pRoot);
		SApplication::getSingleton().SetSwndDefAttr(pRoot);
		this->InsertChild(pRoot);
		pRoot->SSendMessage(WM_CREATE);

		SStringT sstrPos;
		sstrPos.Format(L"%d,%d,@120,@60", pt.x, pt.y);
		pRoot->SetAttribute(L"pos", sstrPos);
	}
	break;
	case JsonArray:
	{
		CJsonArray* pArray = (CJsonArray*)SApplication::getSingleton().CreateWindowByName(L"json_array");
		SASSERT(pArray);
		SApplication::getSingleton().SetSwndDefAttr(pArray);
		this->InsertChild(pArray);
		pArray->SSendMessage(WM_CREATE);

		SStringT sstrPos;
		sstrPos.Format(L"%d,%d,@120,@60", pt.x, pt.y);
		pArray->SetAttribute(L"pos", sstrPos);
	}
	break;
	case JsonObj:
	{
		CJsonObject* pObject = (CJsonObject*)SApplication::getSingleton().CreateWindowByName(L"json_object");
		SASSERT(pObject);
		SApplication::getSingleton().SetSwndDefAttr(pObject);
		this->InsertChild(pObject);
		pObject->SSendMessage(WM_CREATE);

		SStringT sstrPos;
		sstrPos.Format(L"%d,%d,@120,@60", pt.x, pt.y);
		pObject->SetAttribute(L"pos", sstrPos);
	}
	break;
	case JsonSubObj:
	{
		CJsonSubObject* pSubObj = (CJsonSubObject*)SApplication::getSingleton().CreateWindowByName(L"json_subobject");
		SASSERT(pSubObj);
		SApplication::getSingleton().SetSwndDefAttr(pSubObj);
		this->InsertChild(pSubObj);
		pSubObj->SSendMessage(WM_CREATE);

		SStringT sstrPos;
		sstrPos.Format(L"%d,%d,@120,@60", pt.x, pt.y);
		pSubObj->SetAttribute(L"pos", sstrPos);
	}
	break;
	default:
		break;
	}

	m_curEcObjType = Null;
}

void CBoxContainer::SetAddType(EcObjType type)
{
	m_curEcObjType = type;
}