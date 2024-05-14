#pragma once

#include "CJsonRoot.h"
#include "CJsonArray.h"
#include "CJsonObject.h"
#include "CJsonSubObject.h"

#include <vector>
#include <sstream>
#include <fstream>
#include <shellapi.h>

#include "CJsonSettingDlg.h"

class CBoxContainer : public SWindow
{
	SOUI_CLASS_NAME(CBoxContainer, L"containerbox")
public:
	CBoxContainer(void);
	~CBoxContainer(void);

	struct Point {
		float x, y;
		Point(float x = 0, float y = 0) :x(x), y(y) {}
	};

protected:
	void OnPaint(IRenderTarget* pRT);

	void OnLButtonDown(UINT nFlags, SOUI::CPoint point);
	void OnLButtonUp(UINT nFlags, SOUI::CPoint point);
 	void OnLButtonDblClk(UINT nFlags, SOUI::CPoint point);
// 	void OnRButtonUp(UINT nFlags, CPoint point);

	void OnMouseMove(UINT nFlags, SOUI::CPoint point);

	//LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
	SOUI_MSG_MAP_BEGIN()
		MSG_WM_PAINT_EX(OnPaint)
 		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
 		MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
// 		MSG_WM_RBUTTONUP(OnRButtonUp)
 		MSG_WM_MOUSEMOVE(OnMouseMove)

		//MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseEvent)
		SOUI_MSG_MAP_END()

		SOUI_ATTRS_BEGIN()

		SOUI_ATTRS_END()

public:
	void SetAddType(EcObjType type);
	void GeneralJson();

private:
	SOUI::CPoint	m_ptDown;				//鼠标按下的位置
	//SOUI::CPoint	m_ptObjLT;


	SOUI::CRect	m_rcDrawArea;			//鼠标移动区域
	EcObjType	m_curEcObjType;


	std::vector<SWindow*> m_vecSelectObjs;


	SWindow*	m_curObject;

	std::vector<std::vector<Point>>	m_vecBezierPaths;

	bool	m_bContainerLBDown;

	int	m_nObjWidth;
	int	m_nObjHeight;
	int	m_nObjGap;

	int	m_nRootCut;
	int m_nArrCnt;
	int m_nObjCnt;
protected:
	bool OnEventJsonRootLButtonDown(EventJsonRootLButtonDown* pEvt);
	bool OnEventJsonRootLButtonUp(EventJsonRootLButtonUp* pEvt);
	bool OnEventJsonRootMouseMoveing(EventJsonRootMouseMoveing* pEvt);

	bool OnEventJsonArrayLButtonDown(EventJsonArrayLButtonDown* pEvt);
	bool OnEventJsonArrayLButtonUp(EventJsonArrayLButtonUp* pEvt);
	bool OnEventJsonArrayMouseMoveing(EventJsonArrayMouseMoveing* pEvt); 
	bool OnEventJsonArrayLBDbClk(EventJsonArrayLBDbClk* pEvt);

	bool OnEventJsonObjectLButtonDown(EventJsonObjectLButtonDown* pEvt);
	bool OnEventJsonObjectLButtonUp(EventJsonObjectLButtonUp* pEvt);
	bool OnEventJsonObjectMouseMoveing(EventJsonObjectMouseMoveing* pEvt);
	bool OnEventJsonObjectLButtonDblClk(EventJsonObjectLButtonDblClk* pEvt);

private:
	int binomial(int n, int i);
	Point bezier_curve(const std::vector<Point>& points, float t);

	std::string praseJsonFormat(SWindow* pSWindow);
};