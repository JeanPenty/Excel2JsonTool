#pragma once
#include <vector>

class EventJsonObjectLButtonDown : public TplEventArgs<EventJsonObjectLButtonDown>
{
	SOUI_CLASS_NAME(EventJsonObjectLButtonDown, L"json_obecjt_lbtdown")
public:
	EventJsonObjectLButtonDown(SObject* pSender)
		: TplEventArgs<EventJsonObjectLButtonDown>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 71 };
};

class EventJsonObjectLButtonUp : public TplEventArgs<EventJsonObjectLButtonUp>
{
	SOUI_CLASS_NAME(EventJsonObjectLButtonUp, L"json_obecjt_lbtup")
public:
	EventJsonObjectLButtonUp(SObject* pSender)
		: TplEventArgs<EventJsonObjectLButtonUp>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 72 };

	SOUI::CPoint ptDown;
	SOUI::CPoint ptMove;
	EcPosType m_ecPosType;
};

class EventJsonObjectMouseMoveing : public TplEventArgs<EventJsonObjectMouseMoveing>
{
	SOUI_CLASS_NAME(EventJsonObjectMouseMoveing, L"json_obecjt_mousemoving")
public:
	EventJsonObjectMouseMoveing(SObject* pSender)
		: TplEventArgs<EventJsonObjectMouseMoveing>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 73 };

	SOUI::CPoint ptDown;
	SOUI::CPoint ptMove;
	EcPosType m_ecPosType;
};

class CJsonObject : public SWindow
{
	SOUI_CLASS_NAME(CJsonObject, L"json_object")
public:
	CJsonObject(void);
	~CJsonObject(void);

protected:
	LRESULT OnCreate(LPVOID);
	void OnPaint(IRenderTarget* pRT);

	void OnLButtonDown(UINT nFlags, SOUI::CPoint point);
	void OnLButtonUp(UINT nFlags, SOUI::CPoint point);
	void OnMouseMove(UINT nFlags, SOUI::CPoint point);
	void OnMouseHover(WPARAM wParam, CPoint ptPos);
	void OnMouseLeave();
protected:
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_CREATE(OnCreate)
		MSG_WM_PAINT_EX(OnPaint)

		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
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
public:
	EcPosType HitPos(SOUI::CPoint& pt);
	void ShowCursor(EcPosType ePos);

	void setSelect(bool bSelect);

	void setPosX(int nX);
	int getPosX();
	void setPosY(int nY);
	int getPosY();

	void addRootChild(SWindow* pWindow);
	std::vector<SWindow*> getRootChildren();
};
