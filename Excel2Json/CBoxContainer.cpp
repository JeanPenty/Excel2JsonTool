#include "stdafx.h"
#include "CBoxContainer.h"

CBoxContainer::CBoxContainer(void)
{
	m_curEcObjType = JsonNull;

	m_curObject = NULL;

	m_nObjWidth = 100;
	m_nObjHeight = 40;
	m_nObjGap = 30;

	m_nRootCut = 0;
	m_nArrCnt = 0;
	m_nObjCnt = 0;
}

CBoxContainer::~CBoxContainer(void)
{
}

void CBoxContainer::OnPaint(IRenderTarget* pRT)
{
	pRT->SetAntiAlias(TRUE);

	SAutoRefPtr<ICornerPathEffect> pathEffect;
	GETRENDERFACTORY->CreatePathEffect(__uuidof(ICornerPathEffect), (IPathEffect**)&pathEffect);
	if (pathEffect)
		pathEffect->Init(5.0);

	//绘制选择区域
	if (!m_rcDrawArea.IsRectEmpty())
	{
		COLORREF crDrawAreaBorder = RGBA(22, 119, 189, 100);
		CAutoRefPtr<IPen> pen, oldpen;
		pRT->CreatePen(PS_SOLID, crDrawAreaBorder, 1, &pen);
		pRT->SelectObject(pen, (IRenderObj**)&oldpen);
		pRT->DrawRectangle(m_rcDrawArea);
		pRT->SelectObject(oldpen, NULL);
	}

	{
		std::vector<std::vector<CPoint>> vecLines;
		CAutoRefPtr<IPen> pen, oldpen;
		pRT->CreatePen(PS_SOLID, RGBA(0, 0, 100, 255), 1, &pen);
		pRT->SelectObject(pen, (IRenderObj**)&oldpen);

		//计算元素之间的连接线
		for (int i = 0; i < GetChildrenCount(); i++)
		{
			SWindow* pChild = GetChild(i + 1);
			SStringW sstrClassName = pChild->GetObjectClass();
			if (sstrClassName == L"json_root")
			{
				CJsonRoot* pRoot = sobj_cast<CJsonRoot>(pChild);
				CRect rcParent = pRoot->GetWindowRect();
				CPoint ptParentCenter = rcParent.CenterPoint();

				int nParentX = pRoot->getPosX();
				int nParentY = pRoot->getPosY();
				//计算定位点
				CPoint pt1, pt2, pt3, pt4;
				pt1.x = rcParent.right + 30;
				pt1.y = ptParentCenter.y;

				std::vector<SWindow*> vecChildren = pRoot->getRootChildren();
				if (vecChildren.size() > 0) //有子控件
				{
					//绘制一条短直线
					CPoint ptStart;
					ptStart.x = rcParent.right;
					ptStart.y = pt1.y;

					std::vector<CPoint> line;
					line.push_back(ptStart);
					line.push_back(pt1);
					pRT->DrawLines(&line[0], 2);

					std::vector<CPoint> vecPoints;
					for (int j = 0; j < vecChildren.size(); j++)
					{
						SStringW sstrChildClassName = vecChildren[j]->GetObjectClass();
						if (sstrChildClassName == L"json_root")
						{
							CJsonRoot* pObj = sobj_cast<CJsonRoot>(vecChildren[j]);
							CRect rcObj = pObj->GetWindowRect();
							CPoint ptObjCenter = rcObj.CenterPoint();

							pt2.x = pt1.x;
							pt2.y = ptObjCenter.y;

							pt3.x = rcObj.left;
							pt3.y = pt2.y;

							pt4.x = pt3.x;
							pt4.y = pt1.y;

							//绘制成贝塞尔曲线测试
							std::vector<CPoint> vecPts;
							vecPts.push_back(pt1);
							//vecPts.push_back(pt4);
							vecPts.push_back(pt2);
							vecPts.push_back(pt3);
							std::vector<Point> points;
							for (int i = 0; i < vecPts.size(); i++)
							{
								Point pt(vecPts[i].x, vecPts[i].y);
								points.push_back(pt);
							}
							//计算曲线轨迹
							std::vector<Point> vecBezierPath;
							const float step = 0.02; // 步长
							for (float t = 0; t <= 1; t += step)
							{
								Point p = bezier_curve(points, t);
								vecBezierPath.push_back(p);
							}

							CAutoRefPtr<IPath> path;
							GETRENDERFACTORY->CreatePath(&path);

							std::vector<POINT> vecPoly;
							for (int i = 0; i < vecBezierPath.size(); i++)
							{
								POINT pt;
								pt.x = vecBezierPath[i].x;
								pt.y = vecBezierPath[i].y;
								vecPoly.push_back(pt);
							}
							if (vecPoly.size() > 0)
								path->addPoly(&vecPoly[0], vecPoly.size(), false);

							pRT->DrawPath(path, pathEffect);
						}
						else if (sstrChildClassName == L"json_array")
						{
							CJsonArray* pObj = sobj_cast<CJsonArray>(vecChildren[j]);
							CRect rcObj = pObj->GetWindowRect();
							CPoint ptObjCenter = rcObj.CenterPoint();
							pt2.x = pt1.x;
							pt2.y = ptObjCenter.y;

							pt3.x = rcObj.left;
							pt3.y = pt2.y;

							pt4.x = pt3.x;
							pt4.y = pt1.y;
							//绘制成贝塞尔曲线
							std::vector<CPoint> vecPts;
							vecPts.push_back(pt1);
							//vecPts.push_back(pt4);
							vecPts.push_back(pt2);
							vecPts.push_back(pt3);
							std::vector<Point> points;
							for (int i = 0; i < vecPts.size(); i++)
							{
								Point pt(vecPts[i].x, vecPts[i].y);
								points.push_back(pt);
							}
							//计算曲线轨迹
							std::vector<Point> vecBezierPath;
							const float step = 0.02; // 步长
							for (float t = 0; t <= 1; t += step)
							{
								Point p = bezier_curve(points, t);
								vecBezierPath.push_back(p);
							}

							CAutoRefPtr<IPath> path;
							GETRENDERFACTORY->CreatePath(&path);

							std::vector<POINT> vecPoly;
							for (int i = 0; i < vecBezierPath.size(); i++)
							{
								POINT pt;
								pt.x = vecBezierPath[i].x;
								pt.y = vecBezierPath[i].y;
								vecPoly.push_back(pt);
							}
							if (vecPoly.size() > 0)
								path->addPoly(&vecPoly[0], vecPoly.size(), false);

							pRT->DrawPath(path, pathEffect);
						}
						else if (sstrChildClassName == L"json_object")
						{
							CJsonObject* pObj = sobj_cast<CJsonObject>(vecChildren[j]);
							CRect rcObj = pObj->GetWindowRect();
							CPoint ptObjCenter = rcObj.CenterPoint();
							pt2.x = pt1.x;
							pt2.y = ptObjCenter.y;

							pt3.x = rcObj.left;
							pt3.y = pt2.y;

							pt4.x = pt3.x;
							pt4.y = pt1.y;
							//绘制成贝塞尔曲线
							std::vector<CPoint> vecPts;
							vecPts.push_back(pt1);
							//vecPts.push_back(pt4);
							vecPts.push_back(pt2);
							vecPts.push_back(pt3);
							std::vector<Point> points;
							for (int i = 0; i < vecPts.size(); i++)
							{
								Point pt(vecPts[i].x, vecPts[i].y);
								points.push_back(pt);
							}
							//计算曲线轨迹
							std::vector<Point> vecBezierPath;
							const float step = 0.02; // 步长
							for (float t = 0; t <= 1; t += step)
							{
								Point p = bezier_curve(points, t);
								vecBezierPath.push_back(p);
							}

							CAutoRefPtr<IPath> path;
							GETRENDERFACTORY->CreatePath(&path);

							std::vector<POINT> vecPoly;
							for (int i = 0; i < vecBezierPath.size(); i++)
							{
								POINT pt;
								pt.x = vecBezierPath[i].x;
								pt.y = vecBezierPath[i].y;
								vecPoly.push_back(pt);
							}
							if (vecPoly.size() > 0)
								path->addPoly(&vecPoly[0], vecPoly.size(), false);

							pRT->DrawPath(path, pathEffect);
						}
					}
				}
			}
			else if (sstrClassName == L"json_array")
			{
				CJsonArray* pRoot = sobj_cast<CJsonArray>(pChild);
				CRect rcParent = pRoot->GetWindowRect();
				CPoint ptParentCenter = rcParent.CenterPoint();

				int nParentX = pRoot->getPosX();
				int nParentY = pRoot->getPosY();
				//计算定位点
				CPoint pt1, pt2, pt3, pt4;
				pt1.x = rcParent.right + 30;
				pt1.y = ptParentCenter.y;

				std::vector<SWindow*> vecChildren = pRoot->getRootChildren();
				if (vecChildren.size() > 0) //有子控件
				{
					//绘制一条短直线
					CPoint ptStart;
					ptStart.x = rcParent.right;
					ptStart.y = pt1.y;

					std::vector<CPoint> line;
					line.push_back(ptStart);
					line.push_back(pt1);
					pRT->DrawLines(&line[0], 2);

					std::vector<CPoint> vecPoints;
					for (int j = 0; j < vecChildren.size(); j++)
					{
						SStringW sstrChildClassName = vecChildren[j]->GetObjectClass();
						if (sstrChildClassName == L"json_root")
						{
							CJsonRoot* pObj = sobj_cast<CJsonRoot>(vecChildren[j]);
							CRect rcObj = pObj->GetWindowRect();
							CPoint ptObjCenter = rcObj.CenterPoint();

							pt2.x = pt1.x;
							pt2.y = ptObjCenter.y;

							pt3.x = rcObj.left;
							pt3.y = pt2.y;

							pt4.x = pt3.x;
							pt4.y = pt1.y;

							//绘制成贝塞尔曲线测试
							std::vector<CPoint> vecPts;
							vecPts.push_back(pt1);
							//vecPts.push_back(pt4);
							vecPts.push_back(pt2);
							vecPts.push_back(pt3);
							std::vector<Point> points;
							for (int i = 0; i < vecPts.size(); i++)
							{
								Point pt(vecPts[i].x, vecPts[i].y);
								points.push_back(pt);
							}
							//计算曲线轨迹
							std::vector<Point> vecBezierPath;
							const float step = 0.02; // 步长
							for (float t = 0; t <= 1; t += step)
							{
								Point p = bezier_curve(points, t);
								vecBezierPath.push_back(p);
							}

							CAutoRefPtr<IPath> path;
							GETRENDERFACTORY->CreatePath(&path);

							std::vector<POINT> vecPoly;
							for (int i = 0; i < vecBezierPath.size(); i++)
							{
								POINT pt;
								pt.x = vecBezierPath[i].x;
								pt.y = vecBezierPath[i].y;
								vecPoly.push_back(pt);
							}
							if (vecPoly.size() > 0)
								path->addPoly(&vecPoly[0], vecPoly.size(), false);

							pRT->DrawPath(path, pathEffect);
						}
						else if (sstrChildClassName == L"json_array")
						{
							CJsonArray* pObj = sobj_cast<CJsonArray>(vecChildren[j]);
							CRect rcObj = pObj->GetWindowRect();
							CPoint ptObjCenter = rcObj.CenterPoint();
							pt2.x = pt1.x;
							pt2.y = ptObjCenter.y;

							pt3.x = rcObj.left;
							pt3.y = pt2.y;

							pt4.x = pt3.x;
							pt4.y = pt1.y;
							//绘制成贝塞尔曲线
							std::vector<CPoint> vecPts;
							vecPts.push_back(pt1);
							//vecPts.push_back(pt4);
							vecPts.push_back(pt2);
							vecPts.push_back(pt3);
							std::vector<Point> points;
							for (int i = 0; i < vecPts.size(); i++)
							{
								Point pt(vecPts[i].x, vecPts[i].y);
								points.push_back(pt);
							}
							//计算曲线轨迹
							std::vector<Point> vecBezierPath;
							const float step = 0.02; // 步长
							for (float t = 0; t <= 1; t += step)
							{
								Point p = bezier_curve(points, t);
								vecBezierPath.push_back(p);
							}

							CAutoRefPtr<IPath> path;
							GETRENDERFACTORY->CreatePath(&path);

							std::vector<POINT> vecPoly;
							for (int i = 0; i < vecBezierPath.size(); i++)
							{
								POINT pt;
								pt.x = vecBezierPath[i].x;
								pt.y = vecBezierPath[i].y;
								vecPoly.push_back(pt);
							}
							if (vecPoly.size() > 0)
								path->addPoly(&vecPoly[0], vecPoly.size(), false);

							pRT->DrawPath(path, pathEffect);
						}
						else if (sstrChildClassName == L"json_object")
						{
							CJsonObject* pObj = sobj_cast<CJsonObject>(vecChildren[j]);
							CRect rcObj = pObj->GetWindowRect();
							CPoint ptObjCenter = rcObj.CenterPoint();
							pt2.x = pt1.x;
							pt2.y = ptObjCenter.y;

							pt3.x = rcObj.left;
							pt3.y = pt2.y;

							pt4.x = pt3.x;
							pt4.y = pt1.y;
							//绘制成贝塞尔曲线
							std::vector<CPoint> vecPts;
							vecPts.push_back(pt1);
							//vecPts.push_back(pt4);
							vecPts.push_back(pt2);
							vecPts.push_back(pt3);
							std::vector<Point> points;
							for (int i = 0; i < vecPts.size(); i++)
							{
								Point pt(vecPts[i].x, vecPts[i].y);
								points.push_back(pt);
							}
							//计算曲线轨迹
							std::vector<Point> vecBezierPath;
							const float step = 0.02; // 步长
							for (float t = 0; t <= 1; t += step)
							{
								Point p = bezier_curve(points, t);
								vecBezierPath.push_back(p);
							}

							CAutoRefPtr<IPath> path;
							GETRENDERFACTORY->CreatePath(&path);

							std::vector<POINT> vecPoly;
							for (int i = 0; i < vecBezierPath.size(); i++)
							{
								POINT pt;
								pt.x = vecBezierPath[i].x;
								pt.y = vecBezierPath[i].y;
								vecPoly.push_back(pt);
							}
							if (vecPoly.size() > 0)
								path->addPoly(&vecPoly[0], vecPoly.size(), false);

							pRT->DrawPath(path, pathEffect);
						}
					}
				}
			}
			else if (sstrClassName == L"json_object")
			{
				CJsonObject* pRoot = sobj_cast<CJsonObject>(pChild);
				CRect rcParent = pRoot->GetWindowRect();
				CPoint ptParentCenter = rcParent.CenterPoint();

				int nParentX = pRoot->getPosX();
				int nParentY = pRoot->getPosY();
				//计算定位点
				CPoint pt1, pt2, pt3, pt4;
				pt1.x = rcParent.right + 30;
				pt1.y = ptParentCenter.y;

				std::vector<SWindow*> vecChildren = pRoot->getRootChildren();
				if (vecChildren.size() > 0) //有子控件
				{
					//绘制一条短直线
					CPoint ptStart;
					ptStart.x = rcParent.right;
					ptStart.y = pt1.y;

					std::vector<CPoint> line;
					line.push_back(ptStart);
					line.push_back(pt1);
					pRT->DrawLines(&line[0], 2);

					std::vector<CPoint> vecPoints;
					for (int j = 0; j < vecChildren.size(); j++)
					{
						SStringW sstrChildClassName = vecChildren[j]->GetObjectClass();
						if (sstrChildClassName == L"json_root")
						{
							CJsonRoot* pObj = sobj_cast<CJsonRoot>(vecChildren[j]);
							CRect rcObj = pObj->GetWindowRect();
							CPoint ptObjCenter = rcObj.CenterPoint();

							pt2.x = pt1.x;
							pt2.y = ptObjCenter.y;

							pt3.x = rcObj.left;
							pt3.y = pt2.y;

							pt4.x = pt3.x;
							pt4.y = pt1.y;

							//绘制成贝塞尔曲线测试
							std::vector<CPoint> vecPts;
							vecPts.push_back(pt1);
							//vecPts.push_back(pt4);
							vecPts.push_back(pt2);
							vecPts.push_back(pt3);
							std::vector<Point> points;
							for (int i = 0; i < vecPts.size(); i++)
							{
								Point pt(vecPts[i].x, vecPts[i].y);
								points.push_back(pt);
							}
							//计算曲线轨迹
							std::vector<Point> vecBezierPath;
							const float step = 0.02; // 步长
							for (float t = 0; t <= 1; t += step)
							{
								Point p = bezier_curve(points, t);
								vecBezierPath.push_back(p);
							}

							CAutoRefPtr<IPath> path;
							GETRENDERFACTORY->CreatePath(&path);

							std::vector<POINT> vecPoly;
							for (int i = 0; i < vecBezierPath.size(); i++)
							{
								POINT pt;
								pt.x = vecBezierPath[i].x;
								pt.y = vecBezierPath[i].y;
								vecPoly.push_back(pt);
							}
							if (vecPoly.size() > 0)
								path->addPoly(&vecPoly[0], vecPoly.size(), false);

							pRT->DrawPath(path, pathEffect);
						}
						else if (sstrChildClassName == L"json_array")
						{
							CJsonArray* pObj = sobj_cast<CJsonArray>(vecChildren[j]);
							CRect rcObj = pObj->GetWindowRect();
							CPoint ptObjCenter = rcObj.CenterPoint();
							pt2.x = pt1.x;
							pt2.y = ptObjCenter.y;

							pt3.x = rcObj.left;
							pt3.y = pt2.y;

							pt4.x = pt3.x;
							pt4.y = pt1.y;
							//绘制成贝塞尔曲线
							std::vector<CPoint> vecPts;
							vecPts.push_back(pt1);
							//vecPts.push_back(pt4);
							vecPts.push_back(pt2);
							vecPts.push_back(pt3);
							std::vector<Point> points;
							for (int i = 0; i < vecPts.size(); i++)
							{
								Point pt(vecPts[i].x, vecPts[i].y);
								points.push_back(pt);
							}
							//计算曲线轨迹
							std::vector<Point> vecBezierPath;
							const float step = 0.02; // 步长
							for (float t = 0; t <= 1; t += step)
							{
								Point p = bezier_curve(points, t);
								vecBezierPath.push_back(p);
							}

							CAutoRefPtr<IPath> path;
							GETRENDERFACTORY->CreatePath(&path);

							std::vector<POINT> vecPoly;
							for (int i = 0; i < vecBezierPath.size(); i++)
							{
								POINT pt;
								pt.x = vecBezierPath[i].x;
								pt.y = vecBezierPath[i].y;
								vecPoly.push_back(pt);
							}
							if (vecPoly.size() > 0)
								path->addPoly(&vecPoly[0], vecPoly.size(), false);

							pRT->DrawPath(path, pathEffect);
						}
						else if (sstrChildClassName == L"json_object")
						{
							CJsonObject* pObj = sobj_cast<CJsonObject>(vecChildren[j]);
							CRect rcObj = pObj->GetWindowRect();
							CPoint ptObjCenter = rcObj.CenterPoint();
							pt2.x = pt1.x;
							pt2.y = ptObjCenter.y;

							pt3.x = rcObj.left;
							pt3.y = pt2.y;

							pt4.x = pt3.x;
							pt4.y = pt1.y;
							//绘制成贝塞尔曲线
							std::vector<CPoint> vecPts;
							vecPts.push_back(pt1);
							//vecPts.push_back(pt4);
							vecPts.push_back(pt2);
							vecPts.push_back(pt3);
							std::vector<Point> points;
							for (int i = 0; i < vecPts.size(); i++)
							{
								Point pt(vecPts[i].x, vecPts[i].y);
								points.push_back(pt);
							}
							//计算曲线轨迹
							std::vector<Point> vecBezierPath;
							const float step = 0.02; // 步长
							for (float t = 0; t <= 1; t += step)
							{
								Point p = bezier_curve(points, t);
								vecBezierPath.push_back(p);
							}

							CAutoRefPtr<IPath> path;
							GETRENDERFACTORY->CreatePath(&path);

							std::vector<POINT> vecPoly;
							for (int i = 0; i < vecBezierPath.size(); i++)
							{
								POINT pt;
								pt.x = vecBezierPath[i].x;
								pt.y = vecBezierPath[i].y;
								vecPoly.push_back(pt);
							}
							if (vecPoly.size() > 0)
								path->addPoly(&vecPoly[0], vecPoly.size(), false);

							pRT->DrawPath(path, pathEffect);
						}
					}
				}
			}
		}

		pRT->SelectObject(oldpen, NULL);
	}
}

void CBoxContainer::OnLButtonDown(UINT nFlags, SOUI::CPoint point)
{
	m_bContainerLBDown = true;

	m_ptDown = point;

	for (int i = 0; i < m_vecSelectObjs.size(); i++)
	{
		SWindow* pChild = m_vecSelectObjs[i];
		SStringW sstrClassName = pChild->GetObjectClass();
		if (sstrClassName == L"json_root")
		{
			CJsonRoot* pRoot = sobj_cast<CJsonRoot>(pChild);
			pRoot->setSelect(false);
		}
		else if (sstrClassName == L"json_array")
		{
			CJsonArray* pArray = sobj_cast<CJsonArray>(pChild);
			pArray->setSelect(false);
		}
		else if (sstrClassName == L"json_object")
		{
			CJsonObject* pArray = sobj_cast<CJsonObject>(pChild);
			pArray->setSelect(false);
		}
	}
	m_vecSelectObjs.clear();

	m_curObject = NULL;

	//判断是否点击了已选中的
	switch (m_curEcObjType)
	{
	case JsonNull:
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
	m_bContainerLBDown = false;
}

void CBoxContainer::OnMouseMove(UINT nFlags, SOUI::CPoint point)
{
	if (m_curEcObjType == JsonNull)
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
	case JsonNull:
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

		pRoot->setPosX(pt.x);
		pRoot->setPosY(pt.y);

		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonRootLButtonDown, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonRootLButtonUp, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonRootMouseMoveing, this);
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

	m_curEcObjType = JsonNull;
}

bool CBoxContainer::OnEventJsonRootLButtonDown(EventJsonRootLButtonDown* pEvt)
{
	CJsonRoot* pRoot = sobj_cast<CJsonRoot>(pEvt->sender);
	if (pRoot)
	{
		m_vecSelectObjs.push_back(pRoot);
		m_curObject = pRoot;
	}
	return true;
}

bool CBoxContainer::OnEventJsonRootLButtonUp(EventJsonRootLButtonUp* pEvt)
{
	CJsonRoot* pRoot = sobj_cast<CJsonRoot>(pEvt->sender);
	if (pRoot && !m_bContainerLBDown)
	{
		switch (pEvt->m_ecPosType)
		{
		case Null:  //move
		{
			int nX = pRoot->getPosX();
			int nY = pRoot->getPosY();

			if (pEvt->ptDown.x > pEvt->ptMove.x)
				nX -= (pEvt->ptDown.x - pEvt->ptMove.x);
			else
				nX += (pEvt->ptMove.x - pEvt->ptDown.x);
			if (pEvt->ptDown.y > pEvt->ptMove.y)
				nY -= (pEvt->ptDown.y - pEvt->ptMove.y);
			else
				nY += (pEvt->ptMove.y - pEvt->ptDown.y);

			pRoot->setPosX(nX);
			pRoot->setPosY(nY);
		}
		break;
		default:
			break;
		}
	}
	return true;
}

bool CBoxContainer::OnEventJsonRootMouseMoveing(EventJsonRootMouseMoveing* pEvt)
{
	CJsonRoot* pRoot = sobj_cast<CJsonRoot>(pEvt->sender);
	if (pRoot && !m_bContainerLBDown)
	{
		switch (pEvt->m_ecPosType)
		{
		case Null:  //move
		{
			int nX = pRoot->getPosX();
			int nY = pRoot->getPosY();

			if (pEvt->ptDown.x > pEvt->ptMove.x)
				nX -= (pEvt->ptDown.x - pEvt->ptMove.x);
			else
				nX += (pEvt->ptMove.x - pEvt->ptDown.x);
			if (pEvt->ptDown.y > pEvt->ptMove.y)
				nY -= (pEvt->ptDown.y - pEvt->ptMove.y);
			else
				nY += (pEvt->ptMove.y - pEvt->ptDown.y);

			SStringW sstrPos;
			sstrPos.Format(L"%d,%d", nX, nY);
			pRoot->SetAttribute(L"pos", sstrPos);
		}
		break;
		case TopLeft:
		{
			//
		}
		break;

		default:
			break;
		}
	}
	return true;
}

bool CBoxContainer::OnEventJsonArrayLButtonDown(EventJsonArrayLButtonDown* pEvt)
{
	CJsonArray* pRoot = sobj_cast<CJsonArray>(pEvt->sender);
	if (pRoot)
	{
		m_vecSelectObjs.push_back(pRoot);
		m_curObject = pRoot;
	}
	return true;
}

bool CBoxContainer::OnEventJsonArrayLButtonUp(EventJsonArrayLButtonUp* pEvt)
{
	CJsonArray* pRoot = sobj_cast<CJsonArray>(pEvt->sender);
	if (pRoot && !m_bContainerLBDown)
	{
		switch (pEvt->m_ecPosType)
		{
		case Null:  //move
		{
			int nX = pRoot->getPosX();
			int nY = pRoot->getPosY();

			if (pEvt->ptDown.x > pEvt->ptMove.x)
				nX -= (pEvt->ptDown.x - pEvt->ptMove.x);
			else
				nX += (pEvt->ptMove.x - pEvt->ptDown.x);
			if (pEvt->ptDown.y > pEvt->ptMove.y)
				nY -= (pEvt->ptDown.y - pEvt->ptMove.y);
			else
				nY += (pEvt->ptMove.y - pEvt->ptDown.y);

			pRoot->setPosX(nX);
			pRoot->setPosY(nY);
		}
		break;
		default:
			break;
		}
	}
	return true;
}

bool CBoxContainer::OnEventJsonArrayMouseMoveing(EventJsonArrayMouseMoveing* pEvt)
{
	CJsonArray* pRoot = sobj_cast<CJsonArray>(pEvt->sender);
	if (pRoot && !m_bContainerLBDown)
	{
		switch (pEvt->m_ecPosType)
		{
		case Null:  //move
		{
			int nX = pRoot->getPosX();
			int nY = pRoot->getPosY();

			if (pEvt->ptDown.x > pEvt->ptMove.x)
				nX -= (pEvt->ptDown.x - pEvt->ptMove.x);
			else
				nX += (pEvt->ptMove.x - pEvt->ptDown.x);
			if (pEvt->ptDown.y > pEvt->ptMove.y)
				nY -= (pEvt->ptDown.y - pEvt->ptMove.y);
			else
				nY += (pEvt->ptMove.y - pEvt->ptDown.y);

			SStringW sstrPos;
			sstrPos.Format(L"%d,%d", nX, nY);
			pRoot->SetAttribute(L"pos", sstrPos);
		}
		break;
		case TopLeft:
		{
			//
		}
		break;

		default:
			break;
		}
	}
	return true;
}

bool CBoxContainer::OnEventJsonArrayLBDbClk(EventJsonArrayLBDbClk* pEvt)
{
	CJsonArray* pRoot = sobj_cast<CJsonArray>(pEvt->sender);
	if (pRoot)
	{
		pRoot->getKey();
		pRoot->getValue();

		//展示设置key  value的窗口
		CJsonSettingDlg dlg;
		dlg.setKey(pRoot->getKey());
		dlg.setValue(pRoot->getValue());
		if (dlg.DoModal())
		{
			SStringW sstrKey = dlg.getKey();
			SStringW sstrValue = dlg.getValue();

			pRoot->setKey(sstrKey);
			pRoot->setValue(sstrValue);
		}
	}
	return true;
}

bool CBoxContainer::OnEventJsonObjectLButtonDown(EventJsonObjectLButtonDown* pEvt)
{
	CJsonObject* pRoot = sobj_cast<CJsonObject>(pEvt->sender);
	if (pRoot)
	{
		m_vecSelectObjs.push_back(pRoot);
		m_curObject = pRoot;
	}
	return true;
}

bool CBoxContainer::OnEventJsonObjectLButtonUp(EventJsonObjectLButtonUp* pEvt)
{
	CJsonObject* pRoot = sobj_cast<CJsonObject>(pEvt->sender);
	if (pRoot && !m_bContainerLBDown)
	{
		switch (pEvt->m_ecPosType)
		{
		case Null:  //move
		{
			int nX = pRoot->getPosX();
			int nY = pRoot->getPosY();

			if (pEvt->ptDown.x > pEvt->ptMove.x)
				nX -= (pEvt->ptDown.x - pEvt->ptMove.x);
			else
				nX += (pEvt->ptMove.x - pEvt->ptDown.x);
			if (pEvt->ptDown.y > pEvt->ptMove.y)
				nY -= (pEvt->ptDown.y - pEvt->ptMove.y);
			else
				nY += (pEvt->ptMove.y - pEvt->ptDown.y);

			pRoot->setPosX(nX);
			pRoot->setPosY(nY);
		}
		break;
		default:
			break;
		}
	}
	return true;
}

bool CBoxContainer::OnEventJsonObjectMouseMoveing(EventJsonObjectMouseMoveing* pEvt)
{
	CJsonObject* pRoot = sobj_cast<CJsonObject>(pEvt->sender);
	if (pRoot && !m_bContainerLBDown)
	{
		switch (pEvt->m_ecPosType)
		{
		case Null:  //move
		{
			int nX = pRoot->getPosX();
			int nY = pRoot->getPosY();

			if (pEvt->ptDown.x > pEvt->ptMove.x)
				nX -= (pEvt->ptDown.x - pEvt->ptMove.x);
			else
				nX += (pEvt->ptMove.x - pEvt->ptDown.x);
			if (pEvt->ptDown.y > pEvt->ptMove.y)
				nY -= (pEvt->ptDown.y - pEvt->ptMove.y);
			else
				nY += (pEvt->ptMove.y - pEvt->ptDown.y);

			SStringW sstrPos;
			sstrPos.Format(L"%d,%d", nX, nY);
			pRoot->SetAttribute(L"pos", sstrPos);
		}
		break;
		case TopLeft:
		{
			//
		}
		break;

		default:
			break;
		}
	}
	return true;
}

bool CBoxContainer::OnEventJsonObjectLButtonDblClk(EventJsonObjectLButtonDblClk* pEvt)
{
	CJsonObject* pRoot = sobj_cast<CJsonObject>(pEvt->sender);
	if (pRoot)
	{
		pRoot->getKey();
		pRoot->getValue();

		//展示设置key  value的窗口
		CJsonSettingDlg dlg;
		dlg.setKey(pRoot->getKey());
		dlg.setValue(pRoot->getValue());
		if (dlg.DoModal())
		{
			SStringW sstrKey = dlg.getKey();
			SStringW sstrValue = dlg.getValue();

			pRoot->setKey(sstrKey);
			pRoot->setValue(sstrValue);
		}
	}
	return true;
}

void CBoxContainer::SetAddType(EcObjType type)
{
	//m_curEcObjType = type;

	//点击时直接创建
	switch (type)
	{
	case JsonNull:
		break;
	case JsonRoot:
	{
		CJsonRoot* pRoot = (CJsonRoot*)SApplication::getSingleton().CreateWindowByName(L"json_root");
		SASSERT(pRoot);
		SApplication::getSingleton().SetSwndDefAttr(pRoot);
		this->InsertChild(pRoot);
		pRoot->SSendMessage(WM_CREATE);

		int nX, nY;
		if (!m_curObject)
		{
			nX = 200;
			nY = 200;

			SStringW sstrPos;
			sstrPos.Format(L"%d, %d, @%d, @%d", nX, nY, m_nObjWidth, m_nObjHeight);
			pRoot->SetAttribute(L"pos", sstrPos);
			m_curObject = pRoot;
		}
		else
		{
			CJsonRoot* pCurObj = sobj_cast<CJsonRoot>(m_curObject);
			std::vector<SWindow*> vecChildren = pCurObj->getRootChildren();
			if (vecChildren.size() == 0)
			{
				nX = pCurObj->getPosX() + m_nObjWidth + 60;
				nY = pCurObj->getPosY();

				SStringT sstrPos;
				sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
				pRoot->SetAttribute(L"pos", sstrPos);
			}
			else
			{
				//需要重新布局
				vecChildren.push_back(pRoot);
				//总大小为数量*单个宽度 + 间隔*（数量 - 1）
				//间隔设置为30
				//int nTotalHeight = vecChildren.size() * 60 + (vecChildren.size() - 1) * 30;
				for (int i = 0; i < vecChildren.size(); i++)
				{
					nX = pCurObj->getPosX() + m_nObjWidth + 60;
					nY = pCurObj->getPosY() + i * (m_nObjHeight + m_nObjGap);
				}

				SStringT sstrPos;
				sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
				pRoot->SetAttribute(L"pos", sstrPos);
			}

			pCurObj->addRootChild(pRoot);
		}

		pRoot->setPosX(nX);
		pRoot->setPosY(nY);

		SStringW sstrContent;
		sstrContent.Format(L"Json根对象%d", m_nRootCut);
		pRoot->setKey(sstrContent);
		m_nRootCut++;

		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonRootLButtonDown, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonRootLButtonUp, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonRootMouseMoveing, this);
	}
	break;
	case JsonArray:
	{
		CJsonArray* pRoot = (CJsonArray*)SApplication::getSingleton().CreateWindowByName(L"json_array");
		SASSERT(pRoot);
		SApplication::getSingleton().SetSwndDefAttr(pRoot);
		this->InsertChild(pRoot);
		pRoot->SSendMessage(WM_CREATE);

		int nX, nY;
		if (!m_curObject)
		{
			nX = 200;
			nY = 200;

			SStringW sstrPos;
			sstrPos.Format(L"%d, %d, @%d, @%d", nX, nY, m_nObjWidth, m_nObjHeight);
			pRoot->SetAttribute(L"pos", sstrPos);
			m_curObject = pRoot;
		}
		else
		{
			SStringW sstrClassName = m_curObject->GetObjectClass();
			if (sstrClassName == L"json_root") //父节点为root
			{
				CJsonRoot* pCurObj = sobj_cast<CJsonRoot>(m_curObject);
				std::vector<SWindow*> vecChildren = pCurObj->getRootChildren();
				if (vecChildren.size() == 0)
				{
					nX = pCurObj->getPosX() + m_nObjWidth + 60;
					nY = pCurObj->getPosY();

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}
				else
				{
					//需要重新布局
					vecChildren.push_back(pRoot);
					//总大小为数量*单个宽度 + 间隔*（数量 - 1）
					//间隔设置为30
					//int nTotalHeight = vecChildren.size() * 60 + (vecChildren.size() - 1) * 30;
					for (int i = 0; i < vecChildren.size(); i++)
					{
						nX = pCurObj->getPosX() + m_nObjWidth + 60;
						nY = pCurObj->getPosY() + i * (m_nObjHeight + m_nObjGap);
					}

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}

				pCurObj->addRootChild(pRoot);
			}
			else if (sstrClassName == L"json_array")
			{
				CJsonArray* pCurObj = sobj_cast<CJsonArray>(m_curObject);
				std::vector<SWindow*> vecChildren = pCurObj->getRootChildren();
				if (vecChildren.size() == 0)
				{
					nX = pCurObj->getPosX() + m_nObjWidth + 60;
					nY = pCurObj->getPosY();

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}
				else
				{
					//需要重新布局
					vecChildren.push_back(pRoot);
					//总大小为数量*单个宽度 + 间隔*（数量 - 1）
					//间隔设置为30
					//int nTotalHeight = vecChildren.size() * 60 + (vecChildren.size() - 1) * 30;
					for (int i = 0; i < vecChildren.size(); i++)
					{
						nX = pCurObj->getPosX() + m_nObjWidth + 60;
						nY = pCurObj->getPosY() + i * (m_nObjHeight + m_nObjGap);
					}

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}

				pCurObj->addRootChild(pRoot);
			}
			else if (sstrClassName == L"json_object")
			{
				CJsonObject* pCurObj = sobj_cast<CJsonObject>(m_curObject);
				std::vector<SWindow*> vecChildren = pCurObj->getRootChildren();
				if (vecChildren.size() == 0)
				{
					nX = pCurObj->getPosX() + m_nObjWidth + 60;
					nY = pCurObj->getPosY();

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}
				else
				{
					//需要重新布局
					vecChildren.push_back(pRoot);
					//总大小为数量*单个宽度 + 间隔*（数量 - 1）
					//间隔设置为30
					//int nTotalHeight = vecChildren.size() * 60 + (vecChildren.size() - 1) * 30;
					for (int i = 0; i < vecChildren.size(); i++)
					{
						nX = pCurObj->getPosX() + m_nObjWidth + 60;
						nY = pCurObj->getPosY() + i * (m_nObjHeight + m_nObjGap);
					}

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}

				pCurObj->addRootChild(pRoot);
			}

			pRoot->setObjParent(m_curObject);
		}

		pRoot->setPosX(nX);
		pRoot->setPosY(nY);


		SStringW sstrContent;
		sstrContent.Format(L"Json数组%d", m_nArrCnt);
		pRoot->setKey(sstrContent);
		m_nArrCnt++;

		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonArrayLButtonDown, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonArrayLButtonUp, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonArrayMouseMoveing, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonArrayLBDbClk, this);
	}
	break;
	case JsonObj:
	{
		CJsonObject* pRoot = (CJsonObject*)SApplication::getSingleton().CreateWindowByName(L"json_object");
		SASSERT(pRoot);
		SApplication::getSingleton().SetSwndDefAttr(pRoot);
		this->InsertChild(pRoot);
		pRoot->SSendMessage(WM_CREATE);
		int nX, nY;
		if (!m_curObject)
		{
			nX = 200;
			nY = 200;

			SStringW sstrPos;
			sstrPos.Format(L"%d, %d, @%d, @%d", nX, nY, m_nObjWidth, m_nObjHeight);
			pRoot->SetAttribute(L"pos", sstrPos);
			m_curObject = pRoot;
		}
		else
		{
			SStringW sstrClassName = m_curObject->GetObjectClass();
			if (sstrClassName == L"json_root") //父节点为root
			{
				CJsonRoot* pCurObj = sobj_cast<CJsonRoot>(m_curObject);
				std::vector<SWindow*> vecChildren = pCurObj->getRootChildren();
				if (vecChildren.size() == 0)
				{
					nX = pCurObj->getPosX() + m_nObjWidth + 60;
					nY = pCurObj->getPosY();

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}
				else
				{
					//需要重新布局
					vecChildren.push_back(pRoot);
					//总大小为数量*单个宽度 + 间隔*（数量 - 1）
					//间隔设置为30
					//int nTotalHeight = vecChildren.size() * 60 + (vecChildren.size() - 1) * 30;
					for (int i = 0; i < vecChildren.size(); i++)
					{
						nX = pCurObj->getPosX() + m_nObjWidth + 60;
						nY = pCurObj->getPosY() + i * (m_nObjHeight + m_nObjGap);
					}

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}

				pCurObj->addRootChild(pRoot);
			}
			else if (sstrClassName == L"json_array")
			{
				CJsonArray* pCurObj = sobj_cast<CJsonArray>(m_curObject);
				std::vector<SWindow*> vecChildren = pCurObj->getRootChildren();
				if (vecChildren.size() == 0)
				{
					nX = pCurObj->getPosX() + m_nObjWidth + 60;
					nY = pCurObj->getPosY();

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}
				else
				{
					//需要重新布局
					vecChildren.push_back(pRoot);
					//总大小为数量*单个宽度 + 间隔*（数量 - 1）
					//间隔设置为30
					//int nTotalHeight = vecChildren.size() * 60 + (vecChildren.size() - 1) * 30;
					for (int i = 0; i < vecChildren.size(); i++)
					{
						nX = pCurObj->getPosX() + m_nObjWidth + 60;
						nY = pCurObj->getPosY() + i * (m_nObjHeight + m_nObjGap);
					}

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}

				pCurObj->addRootChild(pRoot);
			}
			else if (sstrClassName == L"json_object")
			{
				CJsonObject* pCurObj = sobj_cast<CJsonObject>(m_curObject);
				std::vector<SWindow*> vecChildren = pCurObj->getRootChildren();
				if (vecChildren.size() == 0)
				{
					nX = pCurObj->getPosX() + m_nObjWidth + 60;
					nY = pCurObj->getPosY();

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}
				else
				{
					//需要重新布局
					vecChildren.push_back(pRoot);
					//总大小为数量*单个宽度 + 间隔*（数量 - 1）
					//间隔设置为30
					//int nTotalHeight = vecChildren.size() * 60 + (vecChildren.size() - 1) * 30;
					for (int i = 0; i < vecChildren.size(); i++)
					{
						nX = pCurObj->getPosX() + m_nObjWidth + 60;
						nY = pCurObj->getPosY() + i * (m_nObjHeight + m_nObjGap);
					}

					SStringT sstrPos;
					sstrPos.Format(L"%d,%d,@%d,@%d", nX, nY, m_nObjWidth, m_nObjHeight);
					pRoot->SetAttribute(L"pos", sstrPos);
				}

				pCurObj->addRootChild(pRoot);
			}
			pRoot->setObjParent(m_curObject);
		}

		pRoot->setPosX(nX);
		pRoot->setPosY(nY);

		SStringW sstrContent;
		sstrContent.Format(L"Json对象%d", m_nObjCnt);
		pRoot->setKey(sstrContent);
		m_nObjCnt++;

		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonObjectLButtonDown, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonObjectLButtonUp, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonObjectMouseMoveing, this);
		pRoot->GetEventSet()->subscribeEvent(&CBoxContainer::OnEventJsonObjectLButtonDblClk, this);
	}
	break;
	case JsonSubObj:
		break;
	default:
		break;
	}

	Invalidate();
}

// 计算组合数
int CBoxContainer::binomial(int n, int i) {
	int res = 1;
	for (int j = 1; j <= i; ++j) {
		res *= (n - j + 1) / (double)j;
	}
	return res;
}

// 计算n次贝塞尔曲线上的点
CBoxContainer::Point CBoxContainer::bezier_curve(const std::vector<CBoxContainer::Point>& points, float t) {
	int n = points.size() - 1;
	CBoxContainer::Point res;
	for (int i = 0; i <= n; ++i) {
		float b = binomial(n, i) * pow(t, i) * pow(1 - t, n - i);
		res.x = res.x + points[i].x * b;
		res.y = res.y + points[i].y * b;
	}
	return res;
}

void CBoxContainer::GeneralJson()
{
	//生成JSON 字符串

	//找到最顶层的元素、然后根据其子控件关联的数据生成JSON数据
	SWindow* pRoot = NULL;
	for (int i = 0; i < GetChildrenCount(); i++)
	{
		SWindow* pChild = GetChild(i + 1);
		SStringW sstrClass = pChild->GetObjectClass();
		if (sstrClass == L"json_root")
		{
			CJsonRoot* pObj = sobj_cast<CJsonRoot>(pChild);
			if (!pObj->getObjParent())
			{
				pRoot = pObj;
				break;
			}
		}
		else if (sstrClass == L"json_array")
		{
			CJsonArray* pObj = sobj_cast<CJsonArray>(pChild);
			if (!pObj->getObjParent())
			{
				pRoot = pObj;
				break;
			}
		}
		else if (sstrClass == L"json_array")
		{
			CJsonObject* pObj = sobj_cast<CJsonObject>(pChild);
			if (!pObj->getObjParent())
			{
				pRoot = pObj;
				break;
			}
		}
	}

	std::string strJson = praseJsonFormat(pRoot);

	std::ostringstream os;
	//测试只替换第一行数据
	std::map<int, int> mapTmp;  //找到最大行
	auto iter = CGlobalUnits::GetInstance()->m_mapTitleDatas.begin();
	for (; iter != CGlobalUnits::GetInstance()->m_mapTitleDatas.end(); iter++)
	{
		mapTmp[iter->second.size()] = iter->second.size();
	}
	int nMaxRow = 0;
	if (mapTmp.size() > 0)
	{
		auto iterTmp = mapTmp.rbegin();
		nMaxRow = iterTmp->first;;
	}
	
	std::string strContent = "";
	for (int i = 0; i < nMaxRow; i++)
	{
		os.str("");
		SStringW sstrJson = S_CA2W(strJson.c_str());
		iter = CGlobalUnits::GetInstance()->m_mapTitleDatas.begin();
		for (; iter != CGlobalUnits::GetInstance()->m_mapTitleDatas.end(); iter++)
		{
			if (iter->second.size() > 0)
			{
				sstrJson.Replace(iter->first, iter->second[i]);
			}
		}
		std::string strTmp = S_CW2A(sstrJson);
		os << strTmp << "\n\n";

		strContent += os.str();
	}

	std::ofstream ofs;
	ofs.open("json.txt", std::ios::out);
	ofs << strContent.c_str();
	ofs << "\n";
	ofs.close();

	//将数据写入文件，然后打开文件
	ShellExecuteW(NULL, L"open", L"json.txt", NULL, NULL, SW_SHOW);
}

std::string CBoxContainer::praseJsonFormat(SWindow* pSWindow)
{
	std::ostringstream os;
	os.str("");

	SStringW sstrClass = pSWindow->GetObjectClass();
	if (sstrClass == L"json_root")
	{
		CJsonRoot* pObj = sobj_cast<CJsonRoot>(pSWindow);
		std::vector<SWindow*> vecChildren = pObj->getRootChildren();
		if (vecChildren.size() == 0)
			os << "{}";
		else
		{
			os << "{";
			for (int i = 0; i < vecChildren.size(); i++)
			{
				std::string strRet = praseJsonFormat(vecChildren[i]);
				os << strRet;

				if (i < vecChildren.size() - 1)
					os << ",";
			}
			os << "}";
		}
	}
	else if (sstrClass == L"json_array")
	{
		CJsonArray* pObj = sobj_cast<CJsonArray>(pSWindow);
		std::vector<SWindow*> vecChildren = pObj->getRootChildren();

		SStringW sstrKey = pObj->getKey();
		std::string strKey = S_CW2A(sstrKey);
		if (vecChildren.size() == 0)
		{
			os << "\"" << strKey.c_str() << "\"" << ":";
			os << "[";
			os << "]";
		}
		else
		{
			os << "\"" << strKey.c_str() << "\"" << ":";
			os << "[";
			os << "{";
			for (int i = 0; i < vecChildren.size(); i++)
			{
				std::string strRet = praseJsonFormat(vecChildren[i]);
				os << strRet.c_str();
				if (i < vecChildren.size() - 1)
					os << ",";
			}
			os << "}";
			os << "]";
		}
	}
	else if (sstrClass == L"json_object")
	{
		CJsonObject* pObj = sobj_cast<CJsonObject>(pSWindow);
		std::vector<SWindow*> vecChildren = pObj->getRootChildren();
		SStringW sstrKey = pObj->getKey();
		SStringW sstrValue = pObj->getValue();
		std::string strKey = S_CW2A(sstrKey);
		std::string strValue = S_CW2A(sstrValue);
		if (vecChildren.size() == 0)
		{
			os << "\"" << strKey.c_str() << "\"" << ":";
			os << "\"" << strValue.c_str() << "\"";
		}
		else
		{
			os << "\"" << strKey.c_str() << "\"" << ":";
			if (strValue == "")
			{
				os << "{";
				for (int i = 0; i < vecChildren.size(); i++)
				{
					std::string strRet = praseJsonFormat(vecChildren[i]);
					os << strRet.c_str();
					if (i < vecChildren.size() - 1)
						os << ",";
				}
				os << "}";
			}
			else
			{
				for (int i = 0; i < vecChildren.size(); i++)
				{
					std::string strRet = praseJsonFormat(vecChildren[i]);
					os << strRet.c_str();
					if (i < vecChildren.size() - 1)
						os << ",";
				}
			}
		}
	}

	return os.str();
}