#pragma once

#include <vector>

class EventJsonRootLButtonDown : public TplEventArgs<EventJsonRootLButtonDown>
{
	SOUI_CLASS_NAME(EventJsonRootLButtonDown, L"json_root_lbtdown")
public:
	EventJsonRootLButtonDown(SObject* pSender)
		: TplEventArgs<EventJsonRootLButtonDown>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 51 };
};

class EventJsonRootLButtonUp : public TplEventArgs<EventJsonRootLButtonUp>
{
	SOUI_CLASS_NAME(EventJsonRootLButtonUp, L"json_root_lbtup")
public:
	EventJsonRootLButtonUp(SObject* pSender)
		: TplEventArgs<EventJsonRootLButtonUp>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 52 };

	SOUI::CPoint ptDown;
	SOUI::CPoint ptMove;
	EcPosType m_ecPosType;
};

class EventJsonRootMouseMoveing : public TplEventArgs<EventJsonRootMouseMoveing>
{
	SOUI_CLASS_NAME(EventJsonRootMouseMoveing, L"json_root_mousemoving")
public:
	EventJsonRootMouseMoveing(SObject* pSender)
		: TplEventArgs<EventJsonRootMouseMoveing>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 53 };

	SOUI::CPoint ptDown;
	SOUI::CPoint ptMove;
	EcPosType m_ecPosType;
};

class CJsonRoot : public SWindow
{
	SOUI_CLASS_NAME(CJsonRoot, L"json_root")
public:
	CJsonRoot(void);
	~CJsonRoot(void);

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
	bool m_bSelected;
	bool m_bHover;
	bool m_bLBDown;

	SOUI::CPoint	m_ptDown;

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