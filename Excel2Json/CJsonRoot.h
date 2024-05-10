#pragma once
class CJsonRoot : public SWindow
{
	SOUI_CLASS_NAME(CJsonRoot, L"json_root")
public:
	CJsonRoot(void);
	~CJsonRoot(void);

protected:
	LRESULT OnCreate(LPVOID);
	void OnPaint(IRenderTarget* pRT);
protected:
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_CREATE(OnCreate)
		MSG_WM_PAINT_EX(OnPaint)
		SOUI_MSG_MAP_END()

private:
	bool m_bDrawBorder;
};