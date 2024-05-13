#pragma once

#include <vector>

class EventJsonArrayLButtonDown : public TplEventArgs<EventJsonArrayLButtonDown>
{
	SOUI_CLASS_NAME(EventJsonArrayLButtonDown, L"json_array_lbtdown")
public:
	EventJsonArrayLButtonDown(SObject* pSender)
		: TplEventArgs<EventJsonArrayLButtonDown>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 61 };
};

class EventJsonArrayLButtonUp : public TplEventArgs<EventJsonArrayLButtonUp>
{
	SOUI_CLASS_NAME(EventJsonArrayLButtonUp, L"json_array_lbtup")
public:
	EventJsonArrayLButtonUp(SObject* pSender)
		: TplEventArgs<EventJsonArrayLButtonUp>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 62 };

	SOUI::CPoint ptDown;
	SOUI::CPoint ptMove;
	EcPosType m_ecPosType;
};

class EventJsonArrayMouseMoveing : public TplEventArgs<EventJsonArrayMouseMoveing>
{
	SOUI_CLASS_NAME(EventJsonArrayMouseMoveing, L"json_array_mousemoving")
public:
	EventJsonArrayMouseMoveing(SObject* pSender)
		: TplEventArgs<EventJsonArrayMouseMoveing>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 63 };

	SOUI::CPoint ptDown;
	SOUI::CPoint ptMove;
	EcPosType m_ecPosType;
};

class EventJsonArrayLBDbClk : public TplEventArgs<EventJsonArrayLBDbClk>
{
	SOUI_CLASS_NAME(EventJsonArrayLBDbClk, L"json_array_lbdbclk")
public:
	EventJsonArrayLBDbClk(SObject* pSender)
		: TplEventArgs<EventJsonArrayLBDbClk>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 64 };
};

class CJsonArray : public SWindow
{
	SOUI_CLASS_NAME(CJsonArray, L"json_array")
public:
	CJsonArray(void);
	~CJsonArray(void);

protected:
	LRESULT OnCreate(LPVOID);
	void OnPaint(IRenderTarget* pRT);

	void OnLButtonDown(UINT nFlags, SOUI::CPoint point);
	void OnLButtonUp(UINT nFlags, SOUI::CPoint point);
	void OnMouseMove(UINT nFlags, SOUI::CPoint point);
	void OnMouseHover(WPARAM wParam, CPoint ptPos);
	void OnMouseLeave();
	void OnLButtonDblClk(UINT nFlags, SOUI::CPoint point);

protected:
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_CREATE(OnCreate)
		MSG_WM_PAINT_EX(OnPaint)

		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)

		SOUI_MSG_MAP_END()

private:
	SOUI::CPoint	m_ptDown;
	bool	m_bSelected;
	bool	m_bHover;

	SOUI::CRect	m_rcPos[8];
	HCURSOR	m_hCursorLeft, m_hCursorRight, m_hCursorTop, m_hCursorBottom,
		m_hCursorTopLeft, m_hCursorTopRight, m_hCursorBottomLeft, m_hCursorBottomRight,
		m_hCursorHand, m_hCursorArrow, m_hCursorSelect;

	int		m_nX;
	int		m_nY;

	std::vector<SWindow*> m_vecChild;

	SStringW	m_sstrKey;		//json key
	SStringW	m_sstrValue;	//json value 对应的excel表头
public:
	EcPosType HitPos(SOUI::CPoint& pt);
	void ShowCursor(EcPosType ePos);

	void setSelect(bool bSelect);

	void setPosX(int nX);
	int getPosX();
	void setPosY(int nY);
	int getPosY();

	void setKey(SStringW sstrKey);
	SStringW getKey();

	void setValue(SStringW sstrValue);
	SStringW getValue();

	void addRootChild(SWindow* pWindow);
	std::vector<SWindow*> getRootChildren();
};
