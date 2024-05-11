#pragma once

#include "CJsonRoot.h"
#include "CJsonArray.h"
#include "CJsonObject.h"
#include "CJsonSubObject.h"

#include <vector>

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

private:
	SOUI::CPoint	m_ptDown;				//鼠标按下的位置
	//SOUI::CPoint	m_ptObjLT;


	SOUI::CRect		m_rcDrawArea;			//鼠标移动区域
	EcObjType		m_curEcObjType;


	std::vector<SWindow*> m_vecSelectObjs;


	SWindow*		m_curObject;

	std::vector<std::vector<Point>> m_vecBezierPaths;

	bool			m_bContainerLBDown;
protected:
	bool OnEventJsonRootLButtonDown(EventJsonRootLButtonDown* pEvt);
	bool OnEventJsonRootLButtonUp(EventJsonRootLButtonUp* pEvt);
	bool OnEventJsonRootMouseMoveing(EventJsonRootMouseMoveing* pEvt);

private:
	int binomial(int n, int i);
	Point bezier_curve(const std::vector<Point>& points, float t);
};