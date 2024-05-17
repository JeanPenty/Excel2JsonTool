#pragma once


struct IEditHost
{
	virtual bool canProcessMsg() = NULL;

};

class EventObjEditEnChange : public TplEventArgs<EventObjEditEnChange>
{
	SOUI_CLASS_NAME(EventObjEditEnChange, L"objedit_enchange")
public:
	EventObjEditEnChange(SObject* pSender)
		: TplEventArgs<EventObjEditEnChange>(pSender) {}
	enum { EventID = EVT_EXTERNAL_BEGIN + 101 };

	SWindow* m_pWindow;
	SStringW m_sstrContent;
	int m_nWid;
	int m_nHei;
};

class CObjEdit : public SRichEdit
{
	SOUI_CLASS_NAME(CObjEdit, L"objedit")
public:
	CObjEdit();
	~CObjEdit();

	void SetHost(IEditHost* _ieditHost);

	virtual BOOL IsContainPoint(const POINT& pt, BOOL bClientOnly) const;

protected:
	LRESULT OnCreate(LPVOID);
	bool OnKillFocus(EventArgs* e);
	bool OnEditNotify(EventArgs* e);
	virtual BOOL OnSetCursor(const CPoint& pt);
	void OnNcLButtonDown(UINT nHitTest, CPoint point);
	void OnNcMouseMove(UINT nHitTest, CPoint point);
	void UpdataSize();
	void OnNcLButtonUp(UINT nHitTest, CPoint point);
	void OnNcPaint(IRenderTarget* pRT);
	BOOL OnEraseBkgnd(IRenderTarget* pRT);
	void OnMouseHover(WPARAM wParam, CPoint ptPos);
	void OnMouseLeave();

	SOUI_MSG_MAP_BEGIN()
		MSG_WM_CREATE(OnCreate)
		MSG_WM_NCMOUSEMOVE(OnNcMouseMove)
		MSG_WM_NCLBUTTONDOWN(OnNcLButtonDown)
		MSG_WM_NCLBUTTONUP(OnNcLButtonUp)
		MSG_WM_NCPAINT_EX(OnNcPaint)
		MSG_WM_ERASEBKGND_EX(OnEraseBkgnd)
		MSG_WM_MOUSEHOVER(OnMouseHover)
		//MSG_WM_MOUSELEAVE(OnMouseLeave)
		//MSG_WM_DESTROY(OnDestroy)
		SOUI_MSG_MAP_END()

private:
	IEditHost* m_pHost;

	bool m_bChanged;

	int m_nWid, m_nHei;

public:
	int getWid();
	int getHei();

	void insertBreak();
};

