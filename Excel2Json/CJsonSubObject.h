#pragma once

#include "CObjEdit.h"

class EventJsonSubObjectResize : public TplEventArgs<EventJsonSubObjectResize>
{
	SOUI_CLASS_NAME(EventJsonSubObjectResize, L"json_subobj_resize")
public:
	EventJsonSubObjectResize(SObject* pSender)
		: TplEventArgs<EventJsonSubObjectResize>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 201 };

	int m_nNewWidth;
	int m_nNewHeight;
};

class CJsonSubObject : public SWindow
	, public IEditHost
{
	SOUI_CLASS_NAME(CJsonSubObject, L"json_subobject")
public:
	CJsonSubObject(void);
	~CJsonSubObject(void);

	virtual bool canProcessMsg() {
		return true;
	}

protected:
	bool OnEventObjEditEnChange(EventObjEditEnChange* pEvt);

protected:
	LRESULT OnCreate(LPVOID);
	void OnPaint(IRenderTarget* pRT);

	void OnLButtonDown(UINT nFlags, SOUI::CPoint point);
	void OnLButtonDblClk(UINT nFlags, SOUI::CPoint point);
protected:
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_CREATE(OnCreate)
		MSG_WM_PAINT_EX(OnPaint)

		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
		SOUI_MSG_MAP_END()

private:
	bool m_bDrawBorder;

	CObjEdit* m_pEdit;
	bool	m_bSelected;

	int		m_nWidth;
	int		m_nHeight;
public:
	void setSelect(bool bSelect);

	void editInsertBreak();
	void setEditSize();

	void setWidth(int nWid);
	void setHeight(int nHei);
};

