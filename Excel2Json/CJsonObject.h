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

class EventJsonObjectLButtonDblClk : public TplEventArgs<EventJsonObjectLButtonDblClk>
{
	SOUI_CLASS_NAME(EventJsonObjectLButtonDblClk, L"json_obecjt_lbdbclk")
public:
	EventJsonObjectLButtonDblClk(SObject* pSender)
		: TplEventArgs<EventJsonObjectLButtonDblClk>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 74 };
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
	SWindow* m_pObjParent;

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

	void setObjParent(SWindow* pParent);
	SWindow* getObjParent();

	void setValue(SStringW sstrValue);
	SStringW getValue();

	void addRootChild(SWindow* pWindow);
	std::vector<SWindow*> getRootChildren();
};
