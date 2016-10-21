// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)
CMyButton::CMyButton()
{
	
	b_InRect = false; 
	b_Flag = false;
	b_Down=false;


	m_nBmpID=0;
	m_nBmpIndex=-1;

	m_nBmpSize=0; //图像尺寸
	m_Jg=0; //图像和文本之间的间隔

	clrMask=RGB(255,255,255);

	iOffsetX=0;
	iOffsetY=0;

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CMyButton 消息处理程序

void CMyButton::ShowBmp(CDC* pDC)
{
	CBitmap bmp;
	bmp.LoadBitmap(m_nBmpID);

	CDC* pMemDC=new CDC;
	pMemDC->CreateCompatibleDC(pDC);

	CBitmap* poldbmp=pMemDC->SelectObject(&bmp);
	
	pDC->BitBlt(m_ImagePt.x+iOffsetX,m_ImagePt.y+iOffsetY,m_nBmpSize,m_nBmpSize, pMemDC,m_nBmpSize*(m_nBmpIndex-1),0,SRCAND); 

	pMemDC->SelectObject(poldbmp);

	ReleaseDC(pMemDC);
	delete pMemDC;


}

void CMyButton::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	CButton::PreSubclassWindow();

	ModifyStyle(0,BS_OWNERDRAW ); //设置按钮属性为自画式 

}


void CMyButton::SetBmp(UINT nBmpID,int nBmpIndex)
{
	m_nBmpID=nBmpID;
	m_nBmpIndex=nBmpIndex;
	m_nBmpSize=16;
	m_Jg=1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 用途：设置按钮自画样式
//
/////////
void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	m_ButRect=lpDrawItemStruct->rcItem;
	GetWindowText(m_strText);

	CPoint m_ptCentre = m_ButRect.CenterPoint(); //求按钮中心点 
	CSize Extent = pDC->GetTextExtent(m_strText ); //求文本尺寸 
	

	m_ImagePt = CPoint(m_ptCentre.x-(Extent.cx+m_nBmpSize+m_Jg)/2,m_ptCentre.y-m_nBmpSize/2 ); //设置文本坐标 
	m_textPt.x=m_ImagePt.x+m_nBmpSize+m_Jg;
	m_textPt.y=m_ptCentre.y-Extent.cy/2;


	int nSavedDC = pDC->SaveDC(); 
	VERIFY(pDC); 


	if (!(::GetWindowLong(m_hWnd,GWL_STYLE) & WS_DISABLED)) 
	{ 
		if(!b_Flag ) 
		{ 
			NormalButton(pDC); //画正常按钮 
		} 
		else 
		{ 
			if ((b_Down) && (b_InRect))
				DownButton(pDC); //鼠标按下且在按钮区域内
			else
				PassButton(pDC); //画鼠标经过时的按钮 
		} 
	} 
	else 
	{ 
		LockButton(pDC); //画锁定的按钮 
	} 



	pDC->RestoreDC( nSavedDC ); 

}


void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CButton::OnMouseMove(nFlags, point);

	if(!b_InRect || GetCapture()!=this ) //鼠标进入按钮
	{ 
		b_InRect = true; 
		SetCapture(); 
		b_Flag = true; 

		if (nFlags==1) 
			b_Down=true;
		else
			b_Down=false;


		Invalidate(); //重绘按钮 
	} 
	else 
	{ 
		CRect rc; 
		this->GetClientRect( &rc ); 
		if ( !rc.PtInRect(point) ) //鼠标离开按钮 
		{ 
			b_InRect = false; 
			ReleaseCapture(); 
			b_Flag = false; 
			
	
			Invalidate(); //重绘按钮 
		} 
	} 


}

void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	b_Flag = false;
	b_Down=false;
	if (GetFocus()!=this) 
	{ 
		this->SetFocus(); 
	} 
	CButton::OnLButtonUp( nFlags, point ); 

	Invalidate(); //重绘按钮 

}

void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	b_Flag = true;
	b_Down=true;
	if (GetFocus()!=this) 
	{ 
		this->SetFocus(); 
	} 
	CButton::OnLButtonDown( nFlags, point ); 
	Invalidate(); //重绘按钮 

}

void CMyButton::NormalButton(CDC* pDC)
{

	iOffsetX=0;
	iOffsetY=0;

	//画按钮外框
	CPen pen;
	CPen* pOldPen;
	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));
	pOldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(m_ButRect);
	pDC->SelectObject(pOldPen);


	pen.DeleteObject();
//	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));

	pOldPen=pDC->SelectObject(&pen);

	pDC->MoveTo(m_ButRect.left,m_ButRect.top);
	pDC->LineTo(m_ButRect.left,m_ButRect.bottom-1);

	pDC->MoveTo(m_ButRect.left,m_ButRect.top);
	pDC->LineTo(m_ButRect.right-1,m_ButRect.top);

	pDC->SelectObject(pOldPen);

	////填充按钮框内颜色
	CBrush brush;
	brush.CreateSolidBrush(RGB(234,232,228));
//	brush.CreateSolidBrush(RGB(236,233,216));


	CRect rc=m_ButRect;
	rc.left=rc.left+1;
	rc.top=rc.top+1;
	rc.bottom=rc.bottom-1;
	rc.right=rc.right-1;
	pDC->FillRect(rc,&brush);


	//画按钮文本
	pDC->SetBkColor(RGB(234,232,228));
	pDC->TextOut(m_textPt.x+iOffsetX,m_textPt.y+iOffsetY,m_strText);


	//显示图像
	if (m_nBmpIndex!=-1) ShowBmp(pDC);

}

void CMyButton::PassButton(CDC* pDC)
{
	iOffsetX=0;
	iOffsetY=0;


	//画按钮外框
	CPen pen;
	CPen* pOldPen;
	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));
	pOldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(m_ButRect);
	pDC->SelectObject(pOldPen);


	pen.DeleteObject();
//	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));
	pOldPen=pDC->SelectObject(&pen);

	pDC->MoveTo(m_ButRect.left,m_ButRect.top);
	pDC->LineTo(m_ButRect.left,m_ButRect.bottom-1);

	pDC->MoveTo(m_ButRect.left,m_ButRect.top);
	pDC->LineTo(m_ButRect.right-1,m_ButRect.top);

	pDC->SelectObject(pOldPen);

	////填充按钮框内颜色
	CBrush brush;
	brush.CreateSolidBrush(RGB(236,233,216));

	CRect rc=m_ButRect;
	rc.left=rc.left+1;
	rc.top=rc.top+1;
	rc.bottom=rc.bottom-1;
	rc.right=rc.right-1;
	pDC->FillRect(rc,&brush);


	//画按钮文本
	//pDC->SetBkColor(RGB(182,189,210));
	pDC->SetBkColor(RGB(236,233,216));
	pDC->TextOut(m_textPt.x+iOffsetX,m_textPt.y+iOffsetY,m_strText);

	//显示图像
	if (m_nBmpIndex!=-1) ShowBmp(pDC);

}

void CMyButton::LockButton(CDC* pDC)
{

	iOffsetX=0;
	iOffsetY=0;

	//画按钮外框
	CPen pen;
	CPen* pOldPen;
	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));
	pOldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(m_ButRect);
	pDC->SelectObject(pOldPen);


	pen.DeleteObject();
//	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));

	pOldPen=pDC->SelectObject(&pen);

	pDC->MoveTo(m_ButRect.left,m_ButRect.top);
	pDC->LineTo(m_ButRect.left,m_ButRect.bottom-1);

	pDC->MoveTo(m_ButRect.left,m_ButRect.top);
	pDC->LineTo(m_ButRect.right-1,m_ButRect.top);

	pDC->SelectObject(pOldPen);

	////填充按钮框内颜色
	CBrush brush;
	brush.CreateSolidBrush(RGB(234,232,228));
//	brush.CreateSolidBrush(RGB(236,233,216));


	CRect rc=m_ButRect;
	rc.left=rc.left+1;
	rc.top=rc.top+1;
	rc.bottom=rc.bottom-1;
	rc.right=rc.right-1;
	pDC->FillRect(rc,&brush);


	//画按钮文本
	pDC->SetBkColor(RGB(234,232,228));
	pDC->SetTextColor(RGB(128,128,128));
	pDC->TextOut(m_textPt.x+iOffsetX,m_textPt.y+iOffsetY,m_strText);
	pDC->SetTextColor(RGB(0,0,0));


	//显示图像
	if (m_nBmpIndex!=-1) ShowBmp(pDC);

}

void CMyButton::DownButton(CDC* pDC)
{
	iOffsetX=1;
	iOffsetY=1;

	//画按钮外框
	CPen pen;
	CPen* pOldPen;
	pen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	pOldPen=pDC->SelectObject(&pen);
	pDC->Rectangle(m_ButRect);
	pDC->SelectObject(pOldPen);


	pen.DeleteObject();
	pen.CreatePen(PS_SOLID,1,RGB(128,128,128));
	pOldPen=pDC->SelectObject(&pen);

	pDC->MoveTo(m_ButRect.left,m_ButRect.top);
	pDC->LineTo(m_ButRect.left,m_ButRect.bottom-1);

	pDC->MoveTo(m_ButRect.left,m_ButRect.top);
	pDC->LineTo(m_ButRect.right-1,m_ButRect.top);

	pDC->SelectObject(pOldPen);

	////填充按钮框内颜色
	CBrush brush;
	brush.CreateSolidBrush(RGB(236,233,216));

	CRect rc=m_ButRect;
	rc.left=rc.left+1;
	rc.top=rc.top+1;
	rc.bottom=rc.bottom-1;
	rc.right=rc.right-1;
	pDC->FillRect(rc,&brush);


	//画按钮文本
	pDC->SetBkColor(RGB(236,233,216));
	//pDC->SetTextColor(RGB(255,255,255));

	pDC->TextOut(m_textPt.x+iOffsetX,m_textPt.y+iOffsetY,m_strText);

	//显示图像
	if (m_nBmpIndex!=-1) ShowBmp(pDC);

}

