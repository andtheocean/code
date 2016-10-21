#pragma once
#include "Common.h"

// CMapView 视图

class CMapView : public CView
{
	DECLARE_DYNCREATE(CMapView)

protected:
	CMapView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMapView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

	//显示地图
	void DrawMap(HDC hDC);

	//视图的宽度和高度
	int m_nViewWidth;
	int m_nViewHeight;

	//坐标原点位置
	CPoint m_pt; 

public:
	//
	CPoint m_ptMouse; //鼠标位置
	bool m_blShowXY; //是否显示坐标
	bool m_blShowCurve; //是否显示曲线图


	float SplitY(float lMaxY,int iM);


public:
	CTabuArray m_bestTabuAry; //最佳路径
	double m_dbBestLength; //最短路径长度
	double m_dbTime; //搜索耗时

	int m_nFlag;

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void DrawBmp(int x,int y,HDC hDC,int iBmpIndex);

	void ShowTip();

	void DrawCurve(HDC hDC); //画收敛曲线图

};


