#pragma once
#include "Common.h"

// CMapView ��ͼ

class CMapView : public CView
{
	DECLARE_DYNCREATE(CMapView)

protected:
	CMapView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMapView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

	//��ʾ��ͼ
	void DrawMap(HDC hDC);

	//��ͼ�Ŀ�Ⱥ͸߶�
	int m_nViewWidth;
	int m_nViewHeight;

	//����ԭ��λ��
	CPoint m_pt; 

public:
	//
	CPoint m_ptMouse; //���λ��
	bool m_blShowXY; //�Ƿ���ʾ����
	bool m_blShowCurve; //�Ƿ���ʾ����ͼ


	float SplitY(float lMaxY,int iM);


public:
	CTabuArray m_bestTabuAry; //���·��
	double m_dbBestLength; //���·������
	double m_dbTime; //������ʱ

	int m_nFlag;

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void DrawBmp(int x,int y,HDC hDC,int iBmpIndex);

	void ShowTip();

	void DrawCurve(HDC hDC); //����������ͼ

};


