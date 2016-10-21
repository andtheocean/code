// MapView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Robot.h"
#include "MapView.h"


// CMapView

IMPLEMENT_DYNCREATE(CMapView, CView)

CMapView::CMapView()
{
	//���·��
	m_bestTabuAry.RemoveAll();
	m_nFlag=0;
	m_blShowXY=true;
	m_blShowCurve=false;
}

CMapView::~CMapView()
{
}

BEGIN_MESSAGE_MAP(CMapView, CView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMapView ��ͼ

void CMapView::ShowTip()
{
	//��������

	CString str="";

	if (m_nFlag == 1)
	{
		str="��ͼ�е�������������߰�ס�������϶��������á�";
	}
	else if (m_nFlag == 2)
	{
		str="��ͼ�е�������������߰�ס�������϶����������";
	}
	else if (m_nFlag == 3)
	{ 
		str="��ͼ�е�����������ÿ�ʼ�㡣                             ";
	}
	else if (m_nFlag == 4)
	{
		str="��ͼ�е�����������ý����㡣                             ";
	}

	HDC hDC=this->GetDC()->m_hDC;

	HFONT hNewFont,hOldFont;
	hNewFont=CreateFont(12,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"����");
	hOldFont=(HFONT)SelectObject(hDC,hNewFont);


	::TextOut(hDC,m_pt.x,m_nViewHeight-28,str,str.GetLength());

	SelectObject(hDC,hOldFont);
	DeleteObject(hOldFont);
}

void CMapView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���

	//=============================================================
	//��������ԭ��λ��
	CRect rc;
	this->GetClientRect(rc);
	m_nViewWidth=rc.Width(); //��ͼ���
	m_nViewHeight=rc.Height(); //��ͼ�߶�
	
	int S1=(m_nViewWidth-2*N_MARGIN)/N_MAP_WIDTH;
	int S2=(m_nViewHeight-2*N_MARGIN)/N_MAP_HEIGHT;
	N_POINT_SIZE=min(S1,S2);
	N_POINT_SIZE=max(3,N_POINT_SIZE);

	m_pt.x=(m_nViewWidth-N_MAP_WIDTH*N_POINT_SIZE)/2;
	m_pt.y=(m_nViewHeight-N_MAP_HEIGHT*N_POINT_SIZE)/2;


	//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	// �����ڴ��豸������
	CRect rect;
	GetClientRect(&rect); //�õ���ͼ��С

	CDC dcMem;                                                 //���ڻ�����ͼ���ڴ�DC
	CBitmap bmp;                                                //�ڴ��г�����ʱͼ���λͼ
	dcMem.CreateCompatibleDC(pDC);              //��������DC���������ڴ�DC
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//��������λͼ
	dcMem.SelectObject(&bmp);                         //��λͼѡ����ڴ�DC
	dcMem.FillSolidRect(rect,pDC->GetBkColor());//��ԭ���������ͻ�������Ȼ���Ǻ�ɫ
	HDC hDC=dcMem.m_hDC;

	//��������
	HFONT hNewFont,hOldFont;
	hNewFont=CreateFont(12,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"����");
	hOldFont=(HFONT)SelectObject(hDC,hNewFont);

	if (m_blShowCurve == true)
	{
		DrawCurve(hDC);
	}
	else
	{	
		DrawMap(hDC);
	}

	SelectObject(hDC,hOldFont);
	DeleteObject(hOldFont);

	//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	// ���ڴ��豸�������е�ͼ�ο�������ͼ��
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);//���ڴ�DC�ϵ�ͼ�󿽱���ǰ̨
	dcMem.DeleteDC(); //ɾ��DC
	bmp.DeleteObject(); //ɾ��λͼ


}

//��λͼ
void CMapView::DrawBmp(int x,int y,HDC hDC,int iBmpIndex)
{
	CBitmap bmp;
	//bmp.LoadBitmap(IDB_BMP_MARK);
	bmp.LoadBitmap(iBmpIndex);

	BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

	//���ڴ��д����豸������
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(NULL);

	CBitmap* pOldBmp=dcMemory.SelectObject(&bmp);

	::BitBlt(hDC,x,y,bmpInfo.bmWidth,bmpInfo.bmHeight,dcMemory.m_hDC,0,0,SRCCOPY);

	dcMemory.SelectObject(pOldBmp);

}

//�õ�Y��̶�
float CMapView::SplitY(float lMaxY,int iM)
{
	float ln=1.0;
	float lResult=0.0;
	float y;

	y=lMaxY/((float)iM);

	while (y>10.0)
	{
		ln=(float)(ln*10.0);
		y=(float)(y/10.0);
	}

	if (y>0.0)
	{
		while (y<1.0)
		{
			ln=(float)(ln/10.0);
			y=(float)(y*10.0);
		}	
	}

	if (10.0*ln*iM>lMaxY) lResult=(float)10.0*ln;
	if (8.0*ln*iM>lMaxY) lResult=(float)8.0*ln;
	if (6.0*ln*iM>lMaxY) lResult=(float)6.0*ln;
	if (5.0*ln*iM>lMaxY) lResult=(float)5.0*ln;
	if (4.0*ln*iM>lMaxY) lResult=(float)4.0*ln;
	if (3.0*ln*iM>lMaxY) lResult=(float)3.0*ln;
	if (2.0*ln*iM>lMaxY) lResult=(float)2.0*ln;
	if (1.0*ln*iM>lMaxY) lResult=(float)1.0*ln;

	return lResult;

}



//����������ͼ
void CMapView::DrawCurve(HDC hDC)
{

	//�ҵ����ֵ
	double dbMax=0.0001;
	for (int i=0;i<N_IT_COUNT;i++)
	{
		if (dbMax < g_pShortLenAry[i]) dbMax = g_pShortLenAry[i];
		if (dbMax < g_pAvgLenAry[i]) dbMax = g_pAvgLenAry[i];
	}

	//dbMax=dbMax*1.2;
	dbMax=SplitY(dbMax,6)*6.0;

	//ȷ������ͼԭ��λ�á���ȡ��߶�
	int nMargin=30;
	int nWidth=m_nViewWidth-2*nMargin;
	int nHeight=m_nViewHeight/2;
	CPoint pt(nMargin,m_nViewHeight/4);


	//��������
	HPEN hP1=::CreatePen(PS_SOLID,1,RGB(160,160,160));
	HPEN hP2=::CreatePen(PS_SOLID,1,RGB(99,125,165));
	HPEN hP3=::CreatePen(PS_SOLID,1,RGB(222,121,115));

	//�����
	HPEN hOldP=(HPEN)::SelectObject(hDC,hP1);
	::Rectangle(hDC,pt.x,pt.y,pt.x+nWidth,pt.y+nHeight);
	double dbXScale=(double)nWidth/(double)N_IT_COUNT;

	if (dbXScale >2.0) dbXScale=2.0;

	int x=0;
	int y=0;

	//��X��̶Ⱥ��ı�
	CString str="";
	::SetTextAlign(hDC,TA_CENTER);
	for (int i=0;i<=10;i++)
	{
		x=i*N_IT_COUNT/10;
		str.Format("%d",x);
		::MoveToEx(hDC,pt.x+x*dbXScale,pt.y+nHeight,NULL);
		::LineTo(hDC,pt.x+x*dbXScale,pt.y+nHeight+2);
		::TextOut(hDC,pt.x+x*dbXScale,pt.y+nHeight+4,str,str.GetLength());
	}

	//��Y��̶Ⱥ��ı�
	int YCount=6;
	::SetTextAlign(hDC,TA_RIGHT);
	for (int i=1;i<=YCount;i++)
	{
		str.Format("%.0f",(i*dbMax)/YCount);

		::MoveToEx(hDC,pt.x,pt.y+(YCount-i)*nHeight/YCount,NULL);
		::LineTo(hDC,pt.x-3,pt.y+(YCount-i)*nHeight/YCount);
		::TextOut(hDC,pt.x-5,pt.y+(YCount-i)*nHeight/YCount-6,str,str.GetLength());
	}

	//��ƽ������
	::SelectObject(hDC,hP2);
	for (int i=0;i<N_IT_COUNT;i++)
	{
		x=pt.x+dbXScale*i+1;
		y=pt.y+nHeight*(1.0-g_pAvgLenAry[i]/dbMax)-2;
		if (i == 0)
		{
			::MoveToEx(hDC,x,y,NULL);
		}
		else
		{
			::LineTo(hDC,x,y);
		}
	}

	//���������
	::SelectObject(hDC,hP3);
	for (int i=0;i<N_IT_COUNT;i++)
	{
		x=pt.x+dbXScale*i+1;
		y=pt.y+nHeight*(1.0-g_pShortLenAry[i]/dbMax)-2;
		if (i == 0)
		{
			::MoveToEx(hDC,x,y,NULL);
		}
		else
		{
			::LineTo(hDC,x,y);
		}
	}


	//�ָ���ɾ���½����Ļ���
	::SelectObject(hDC,hOldP);

	::DeleteObject(hP1);
	::DeleteObject(hP2);
	::DeleteObject(hP3);

}

//��ʾ��ͼ
void CMapView::DrawMap(HDC hDC)
{

	//��������ͼƬ
	if (m_pt.x >=32)
	{
		DrawBmp(m_pt.x-32,m_nViewHeight-32,hDC,IDB_BMP_ROBOT);
	}
	else
	{
		DrawBmp(0,m_nViewHeight-32,hDC,IDB_BMP_ROBOT);
	}

	HPEN hNewPen=::CreatePen(PS_SOLID,1,CLR_LINE);
	HPEN hTabuPen=::CreatePen(PS_SOLID,1,CLR_TABU);
	HPEN hOldPen=(HPEN)::SelectObject(hDC,hNewPen);

	//=============================================================
	//��������
	for (int i=0;i<N_MAP_WIDTH+1;i++)
	{
		::MoveToEx(hDC,m_pt.x+i*N_POINT_SIZE,m_pt.y,NULL);
		::LineTo(hDC,m_pt.x+i*N_POINT_SIZE,m_pt.y+N_POINT_SIZE*N_MAP_HEIGHT);
	}

	for (int i=0;i<N_MAP_HEIGHT+1;i++)
	{
		::MoveToEx(hDC,m_pt.x,m_pt.y+i*N_POINT_SIZE,NULL);
		::LineTo(hDC,m_pt.x+N_MAP_WIDTH*N_POINT_SIZE,m_pt.y+i*N_POINT_SIZE);
	}

	//=============================================================
	//���ϰ����ʼ��ͽ�����
	HBRUSH hBarrierBrush=::CreateSolidBrush(CLR_BARRIER);
	HBRUSH hStartBrush=::CreateSolidBrush(CLR_START);
	HBRUSH hEndBrush=::CreateSolidBrush(CLR_END);

	HBRUSH hOldBrush=(HBRUSH)::SelectObject(hDC,hBarrierBrush);
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			if (g_pMapAry[i][j] == 1)
			{
				::Rectangle(hDC,m_pt.x+i*N_POINT_SIZE,m_pt.y+j*N_POINT_SIZE,m_pt.x+(i+1)*N_POINT_SIZE+1,m_pt.y+(j+1)*N_POINT_SIZE+1);
			}
		}
	}

	//=============================================================
	//��·��
	::SelectObject(hDC,hTabuPen);

	CPoint pt;
	int nCount=(int)m_bestTabuAry.GetCount();
	int x=0;
	int y=0;
	//int r=N_POINT_SIZE/6;
	int r=2;
	for (int i=0;i<nCount;i++)
	{
		pt=m_bestTabuAry.GetAt(i);
		if (i == 0)
		{
			::MoveToEx(hDC,m_pt.x+pt.x*N_POINT_SIZE+N_POINT_SIZE/2,m_pt.y+pt.y*N_POINT_SIZE+N_POINT_SIZE/2,NULL);
		}
		else
		{
			x=m_pt.x+pt.x*N_POINT_SIZE+N_POINT_SIZE/2;
			y=m_pt.y+pt.y*N_POINT_SIZE+N_POINT_SIZE/2;
			::LineTo(hDC,x,y);
			::Rectangle(hDC,x-r,y-r,x+r+1,y+r+1);
		}
	}

	CString str="";
	if (nCount >0)
	{
		str.Format("������%d��·����%.2f����ʱ��%.3fs",(int)m_bestTabuAry.GetCount(),m_dbBestLength,m_dbTime);
		::DrawText(hDC,str,str.GetLength(),CRect(m_pt.x,m_nViewHeight-12,m_pt.x+300,m_nViewHeight),0);
	}

	//=============================================================
	//���ϰ����ʼ��ͽ�����
	::SelectObject(hDC,hNewPen);
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			if ((i==g_ptStart.x) && (j==g_ptStart.y))
			{
				::SelectObject(hDC,hStartBrush);
				::Rectangle(hDC,m_pt.x+i*N_POINT_SIZE,m_pt.y+j*N_POINT_SIZE,m_pt.x+(i+1)*N_POINT_SIZE+1,m_pt.y+(j+1)*N_POINT_SIZE+1);
				::SelectObject(hDC,hBarrierBrush);
			}
			else if ((i==g_ptEnd.x) && (j==g_ptEnd.y))
			{
				::SelectObject(hDC,hEndBrush);
				::Rectangle(hDC,m_pt.x+i*N_POINT_SIZE,m_pt.y+j*N_POINT_SIZE,m_pt.x+(i+1)*N_POINT_SIZE+1,m_pt.y+(j+1)*N_POINT_SIZE+1);
				::SelectObject(hDC,hBarrierBrush);
			}

		}
	}

	//=============================================================
	//���������λ��������
	x=(m_ptMouse.x-m_pt.x)/N_POINT_SIZE;
	y=(m_ptMouse.y-m_pt.y)/N_POINT_SIZE;

	if ((x>=0 && x<N_MAP_WIDTH) && (y>=0 && y<N_MAP_HEIGHT) && (m_blShowXY==true))
	{
		::SetBkMode(hDC,1);

		::SelectObject(hDC,hTabuPen);
		::MoveToEx(hDC,0,m_ptMouse.y,NULL);
		::LineTo(hDC,2000,m_ptMouse.y);

		::MoveToEx(hDC,m_ptMouse.x,0,NULL);
		::LineTo(hDC,m_ptMouse.x,2000);

		//��ʾ�����������
		str.Format("%d",x+1);
		::TextOut(hDC,m_ptMouse.x+2,m_pt.y+N_POINT_SIZE*N_MAP_HEIGHT+2,str,str.GetLength());
		::TextOut(hDC,m_ptMouse.x+2,m_pt.y-13,str,str.GetLength());

		str.Format("%d",y+1);
		::TextOut(hDC,m_pt.x+N_POINT_SIZE*N_MAP_WIDTH+3,m_ptMouse.y-13,str,str.GetLength());
		::TextOut(hDC,m_pt.x-13,m_ptMouse.y-13,str,str.GetLength());

		//str.Format("[%d,%d]",x+1,y+1);
		//::TextOut(hDC,m_ptMouse.x+5,m_ptMouse.y-17,str,str.GetLength());
	}

	//=============================================================
	//�ظ����ʡ���ˢ��ɾ���½��Ķ���
	::SelectObject(hDC,hOldBrush);
	
	::DeleteObject(hBarrierBrush);
	::DeleteObject(hStartBrush);
	::DeleteObject(hEndBrush);
	::DeleteObject(hTabuPen);


	::SelectObject(hDC,hOldPen);
	::DeleteObject(hNewPen);


}

// CMapView ���

#ifdef _DEBUG
void CMapView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMapView ��Ϣ�������

void CMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	m_ptMouse=point;  //�������λ��
	this->Invalidate(FALSE);

	//����Ҫ��ͼ
	if (m_nFlag == 0)
	{
		return;
	}

	//���û�а���
	if (nFlags != MK_LBUTTON)
	{
		return;
	}

	int x=(point.x-m_pt.x)/N_POINT_SIZE;
	if ((x<0) || (x>=N_MAP_WIDTH)) //Խ��
	{
		return;
	}

	int y=(point.y-m_pt.y)/N_POINT_SIZE;
	if ((y<0) || (y>=N_MAP_HEIGHT)) //Խ��
	{
		return;
	}


	if ((g_pMapAry[x][y] != NIL) && (g_pMapAry[x][y] != BARRIER)) //���ǿ�
	{
		return;
	}


	//�ı��ͼ��ˢ��
	if (m_nFlag == 1)
	{
		m_bestTabuAry.RemoveAll();
		g_pMapAry[x][y]=BARRIER;
		this->Invalidate(FALSE);
	}
	else if (m_nFlag == 2)
	{
		m_bestTabuAry.RemoveAll();
		g_pMapAry[x][y]=NIL;
		this->Invalidate(FALSE);
	}


	CView::OnMouseMove(nFlags, point);
}

void CMapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//����Ҫ��ͼ
	if (m_nFlag == 0)
	{
		return;
	}

	int x=(point.x-m_pt.x)/N_POINT_SIZE;
	if ((x<0) || (x>=N_MAP_WIDTH)) //Խ��
	{
		return;
	}

	int y=(point.y-m_pt.y)/N_POINT_SIZE;
	if ((y<0) || (y>=N_MAP_HEIGHT)) //Խ��
	{
		return;
	}

	//�����ϰ�
	if (m_nFlag == 1)
	{
		m_bestTabuAry.RemoveAll();
		g_pMapAry[x][y]=BARRIER;
		this->Invalidate(FALSE);
	}
	if (m_nFlag == 2)
	{
		m_bestTabuAry.RemoveAll();
		g_pMapAry[x][y]=NIL;
		this->Invalidate(FALSE);
	}

	//�����ÿ�ʼ��
	if (m_nFlag == 3) 
	{
		if (g_pMapAry[x][y] == END)
		{
			return;
		}
		else
		{
			g_pMapAry[g_ptStart.x][g_ptStart.y]=NIL;
			g_ptStart.x=x;
			g_ptStart.y=y;
			g_pMapAry[g_ptStart.x][g_ptStart.y]=START;
			m_bestTabuAry.RemoveAll();
			this->Invalidate(FALSE);
		}
	}

	//�����ý�����
	if (m_nFlag == 4) 
	{
		if (g_pMapAry[x][y] == START)
		{
			return;
		}
		else
		{
			g_pMapAry[g_ptEnd.x][g_ptEnd.y]=NIL;
			g_ptEnd.x=x;
			g_ptEnd.y=y;
			g_pMapAry[g_ptEnd.x][g_ptEnd.y]=END;
			m_bestTabuAry.RemoveAll();
			this->Invalidate(FALSE);
		}
	}

	CView::OnLButtonDown(nFlags, point);
}
