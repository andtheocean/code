#include "StdAfx.h"
#include ".\ant.h"

CAnt::CAnt(void)
{
	m_pMapAry=Create2DArray<int>(N_MAX_MAP_WIDTH,N_MAX_MAP_HEIGHT);
}

CAnt::~CAnt(void)
{
	Free2DArray(m_pMapAry,N_MAX_MAP_WIDTH);
}


void CAnt::Init()
{
	//��������ߵ�·��
	m_tabuAry.RemoveAll(); 

	//���������߹��ĵط�Ϊ��ͼ��ʼ״̬
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			m_pMapAry[i][j]=g_pMapAry[i][j];
		}
	}

	//������ʼ�㣬��������ʼ��Ϊȥ����
	m_ptCurrent=g_ptStart;
	m_tabuAry.Add(m_ptCurrent); 
	m_pMapAry[m_ptCurrent.x][m_ptCurrent.y]=1; 

	//�������������־Ϊfalse
	m_blComplete=false;

	 //�����߹���·����������Ϊ0
	m_dbPathLength=0.0;

}


//����(x0,y0)��(x,y)�Ƿ�����
bool CAnt::CheckXY(int x0,int y0,int x,int y)
{
	//Խ��
	if ((x<0) || (x>=N_MAP_WIDTH))
	{
		return false;
	}

	//Խ��
	if ((y<0) || (y>=N_MAP_HEIGHT))
	{
		return false;
	}

	//��λ�����ϰ�����ȥ����
	if ((m_pMapAry[x][y] == BARRIER) || (m_pMapAry[x][y] == MOVED))
	{
		return false;
	}

	//���û��Խ����λ��Ϊ�գ�Ҫ��������б����б����������Ƿ����ϰ�

	if ((x-x0 == -1) && (y-y0 ==-1)) //��λ�������Ͻ�
	{
		if ((m_pMapAry[x+1][y] == BARRIER) && (m_pMapAry[x][y+1] == BARRIER))
		{
			return false;
		}
	}

	if ((x-x0 == 1) && (y-y0 ==-1)) //��λ�������Ͻ�
	{
		if ((m_pMapAry[x-1][y] == BARRIER) && (m_pMapAry[x][y+1] == BARRIER))
		{
			return false;
		}
	}

	if ((x-x0 == -1) && (y-y0 ==1)) //��λ�������½�
	{
		if ((m_pMapAry[x][y-1] == BARRIER) && (m_pMapAry[x+1][y] == BARRIER))
		{
			return false;
		}
	}

	if ((x-x0 == 1) && (y-y0 ==1)) //��λ�������½�
	{
		if ((m_pMapAry[x-1][y] == BARRIER) && (m_pMapAry[x][y-1] == BARRIER))
		{
			return false;
		}
	}

	//���涼�����أ�����Ե���
	return true;
}

//ѡ����һ����
//����ֵ Ϊ�������λ��
CPoint CAnt::ChooseNextCity()
{

	CPoint pt(-1,-1);  //���ؽ��������ʱ��������Ϊ-1,-1

	//==============================================================================
	//���㵱ǰ�����Χ8�������Ϣ���ܺ�
	//Ϊ����ѭ�����д������뷽�㣬��ǰ���ڵ�Ҳ����һ��
	double dbTotal=0.0;	
	double prob[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1}; // ������б�ѡ�еĸ���

	int nIndex=-1;
	int nCount=0; //��Χ�м��������ȥ

	
	for (int x=m_ptCurrent.x-1;x<=m_ptCurrent.x+1;x++)
	{
		for (int y=m_ptCurrent.y-1;y<=m_ptCurrent.y+1;y++)
		{
			nIndex++;
			if (CheckXY(m_ptCurrent.x,m_ptCurrent.y,x,y) == true)
			{
				prob[nIndex]=g_pMapTrail[x][y]/(g_pMapLen[x][y]*g_pMapLen[x][y]);
				
				dbTotal=dbTotal+prob[nIndex];
				nCount++;
			}
		}
	}

	//��Χû�е����ȥ����ֱ�ӷ���
	if (nCount ==0)
	{
		return pt;
	}


	////==============================================================================
	//����Χ���������ѡ��

	nIndex=-1; //��¼��Χ�Ǹ��㱻ѡ��
	int nIndexFirst=-1; //��¼��һ������ȥ�ĵ�
	double dbTemp=rnd(0.0,dbTotal); //ȡһ�������
	for (int i=0;i<9;i++)
	{
		if (prob[i]>=0) //�����ȥ
		{
			dbTemp=dbTemp-prob[i]; //��������൱��ת������
			if (dbTemp <= 0.0) //����ֹͣת�������µ�λ�ã�ֱ������ѭ��
			{
				nIndex=i;
				break;
			}

			//�����һ������ȥ�ĵ�
			//���û�е�ѡ�о����������Ϊ�������
			if (nIndexFirst == -1) 
			{
				nIndexFirst=i;
			}
		}
	}

	//��������������û�е㱻ѡ��
	//�Ͱѵ�һ����ȥ�ĵ���Ϊ�������
	if (nIndex == -1)
	{
		nIndex = nIndexFirst;
	}
	//���������õ�λ��
	switch (nIndex)
	{	
		case 0 : pt.x=m_ptCurrent.x-1; pt.y=m_ptCurrent.y-1; break;
		case 1 : pt.x=m_ptCurrent.x-1; pt.y=m_ptCurrent.y; break;
		case 2 : pt.x=m_ptCurrent.x-1; pt.y=m_ptCurrent.y+1; break;

		case 3 : pt.x=m_ptCurrent.x; pt.y=m_ptCurrent.y-1; break;
		case 4 : pt.x=m_ptCurrent.x; pt.y=m_ptCurrent.y; break;
		case 5 : pt.x=m_ptCurrent.x; pt.y=m_ptCurrent.y+1; break;

		case 6 : pt.x=m_ptCurrent.x+1; pt.y=m_ptCurrent.y-1; break;
		case 7 : pt.x=m_ptCurrent.x+1; pt.y=m_ptCurrent.y; break;
		case 8 : pt.x=m_ptCurrent.x+1; pt.y=m_ptCurrent.y+1; break;

		default : break;
	}

	//==============================================================================
	//���ؽ��
	return pt;

}

//����������
double CAnt::LenTwoPoint(CPoint pt1,CPoint pt2)
{
	return sqrt((double)((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y)));
}



//����·������·ȥ��
void CAnt::AdjustPathX()
{
	//=================================================
	//�����������������
	int nCount=(int)m_tabuAry.GetCount();
	CPoint* pAry=new CPoint[nCount];

	CPoint pt;
	for (int i=0;i<nCount;i++)
	{
		pt=m_tabuAry.GetAt(i);
		pAry[i]=pt;
	}

	//=================================================
	//��ʼ����
	CPoint pt1;
	CPoint pt2;

	
	int nNewi=0;
	int nX=0;
	int nY=0;
	int nP=0;

	for (int i=0;i<nCount-1;i++)
	{
		pt1=pAry[i];

		for (int j=nCount-1;j>i;j--)
		{
			pt2=pAry[j];

			//�����pt1����ֱ���ƶ���pt2
			if ((pt1.x==pt2.x) && (CanMove(pt1,pt2,nX,nY,nP) == true))
			{
					//�м�ɾ���������
					for (int k=i+1;k<j;k++)
					{
						pAry[k].x=-1;
						pAry[k].y=-1;
					}

					//���м�ֱ���ϵĵ����
					for (int k=1;k<=nP;k++)
					{
						pAry[i+k].x=pt1.x+k*nX;
						pAry[i+k].y=pt1.y+k*nY;
					}

					//��ת��j��ʼ��飬����ѭ��
					i=j-1;
					break;
			}
		}

	}

	//=================================================
	//������
	m_tabuAry.RemoveAll();
	for (int i=0;i<nCount;i++)
	{
		if (pAry[i].x != -1)
		{
			m_tabuAry.Add(pAry[i]);
		}
	}
	//=================================================
	//ɾ������
	if (pAry!=NULL)
	{
		delete []pAry;
		pAry=NULL;
	}

}

//����·������·ȥ��
void CAnt::AdjustPathXY()
{
	//=================================================
	//�����������������
	int nCount=(int)m_tabuAry.GetCount();
	CPoint* pAry=new CPoint[nCount];

	CPoint pt;
	for (int i=0;i<nCount;i++)
	{
		pt=m_tabuAry.GetAt(i);
		pAry[i]=pt;
	}

	//=================================================
	//��ʼ����
	CPoint pt1;
	CPoint pt2;

	
	int nNewi=0;
	int nX=0;
	int nY=0;
	int nP=0;

	for (int i=0;i<nCount-1;i++)
	{
		pt1=pAry[i];

		for (int j=nCount-1;j>i;j--)
		{
			pt2=pAry[j];

			//�����pt1����ֱ���ƶ���pt2
			if ((abs(pt1.x-pt2.x)==abs(pt1.y-pt2.y)) && (CanMove(pt1,pt2,nX,nY,nP) == true))
			{
					//�м�ɾ���������
					for (int k=i+1;k<j;k++)
					{
						pAry[k].x=-1;
						pAry[k].y=-1;
					}

					//���м�ֱ���ϵĵ����
					for (int k=1;k<=nP;k++)
					{
						pAry[i+k].x=pt1.x+k*nX;
						pAry[i+k].y=pt1.y+k*nY;
					}

					//��ת��j��ʼ��飬����ѭ��
					i=j-1;
					break;
			}
		}

	}

	//=================================================
	//������
	m_tabuAry.RemoveAll();
	for (int i=0;i<nCount;i++)
	{
		if (pAry[i].x != -1)
		{
			m_tabuAry.Add(pAry[i]);
		}
	}
	//=================================================
	//ɾ������
	if (pAry!=NULL)
	{
		delete []pAry;
		pAry=NULL;
	}

}

//����·������·ȥ��
void CAnt::AdjustPathY()
{
	//=================================================
	//�����������������
	int nCount=(int)m_tabuAry.GetCount();
	CPoint* pAry=new CPoint[nCount];

	CPoint pt;
	for (int i=0;i<nCount;i++)
	{
		pt=m_tabuAry.GetAt(i);
		pAry[i]=pt;
	}

	//=================================================
	//��ʼ����
	CPoint pt1;
	CPoint pt2;

	
	int nNewi=0;
	int nX=0;
	int nY=0;
	int nP=0;

	for (int i=0;i<nCount-1;i++)
	{
		pt1=pAry[i];

		for (int j=nCount-1;j>i;j--)
		{
			pt2=pAry[j];

			//�����pt1����ֱ���ƶ���pt2
			if ((pt1.y==pt2.y) && (CanMove(pt1,pt2,nX,nY,nP) == true))
			{
					//�м�ɾ���������
					for (int k=i+1;k<j;k++)
					{
						pAry[k].x=-1;
						pAry[k].y=-1;
					}

					//���м�ֱ���ϵĵ����
					for (int k=1;k<=nP;k++)
					{
						pAry[i+k].x=pt1.x+k*nX;
						pAry[i+k].y=pt1.y+k*nY;
					}

					//��ת��j��ʼ��飬����ѭ��
					i=j-1;
					break;
			}
		}

	}

	//=================================================
	//������
	m_tabuAry.RemoveAll();
	for (int i=0;i<nCount;i++)
	{
		if (pAry[i].x != -1)
		{
			m_tabuAry.Add(pAry[i]);
		}
	}
	//=================================================
	//ɾ������
	if (pAry!=NULL)
	{
		delete []pAry;
		pAry=NULL;
	}

}

void CAnt::Move()
{

	//�������������������Ͳ����ƶ�
	if (m_blComplete == true)
	{
		return;
	}

	//����û��������������������
	CPoint ptNext=ChooseNextCity(); //ѡ����һ������

	if ((ptNext.x<0) && (ptNext.y<0)) //û�е����ѡ��˵�������������壬�����һ��
	{
		int nCount=(int)m_tabuAry.GetCount();
		if (nCount>=2)
		{
			m_ptCurrent=m_tabuAry.GetAt(nCount-2); //����һ��
			m_tabuAry.RemoveAt(nCount-1); //��·�����Ƴ���ǰ��
		}
		else //����Ѿ��޷����ˣ�˵���޽�
		{
			g_blCanSolved=false;
		}
	}
	else //�е����ѡ����ǰ��
	{
		m_tabuAry.Add(ptNext);
		m_pMapAry[ptNext.x][ptNext.y]=MOVED; //���������Ϊȥ����
		m_ptCurrent=ptNext;

		//����ȥ�������Ϣ��
		//g_pMapTrail[ptNext.x][ptNext.y]=g_pMapTrail[ptNext.x][ptNext.y]*ROU;

		//����Ƿ񵽴��յ�
		if (m_ptCurrent == g_ptEnd)
		{
			//AdjustPathX();
			//AdjustPathY();
			//AdjustPathXY();

			////�ٵ���һ��
			////��Ϊ���������ܻ������µĸ���·��û��ֱ������
			//AdjustPathX();
			//AdjustPathY();
			//AdjustPathXY();

			m_blComplete=true;
			CalPathLength();
		}
	}

}

//����
void CAnt::PrintPath()
{
	return;

	int nCount=(int)m_tabuAry.GetCount();

	CString str="";
	CPoint pt;
	str.Format("%d ",nCount);
	TRACE0(str);
	for (int i=0;i<nCount;i++)
	{
		pt=m_tabuAry.GetAt(i);
		if (pt.x == -1)
		{
			continue;
		}
		str.Format("[%d,%d]",pt.x,pt.y);
		TRACE0(str);
	}
	TRACE0("\n");

}



//���������߹���·������
void CAnt::CalPathLength()
{
	m_dbPathLength=0.0;

	CPoint pt1;
	CPoint pt2;
	int nCount=(int)m_tabuAry.GetCount();
	for (int i=0;i<nCount-1;i++)
	{
		pt1=m_tabuAry.GetAt(i);
		pt2=m_tabuAry.GetAt(i+1);
		m_dbPathLength=m_dbPathLength+LenTwoPoint(pt1,pt2);
	}

}


//��p1�Ƿ����ֱ���ƶ���p2
bool CAnt::CanMove(CPoint pt1,CPoint pt2,int &nXStep,int &nYStep,int &nCount)
{
	int X=pt2.x-pt1.x;
	int Y=pt2.y-pt1.y;
		
	//���ж��Ƿ���ͬһֱ����
	if ((X==0) || (Y==0) || (X==Y) || (X==(-Y)))
	{
	}
	else
	{
		return false;
	}

	//�м��м�����
	nCount=max(abs(X),abs(Y))-1;

	//X Y �ĵ���ֵ
	if (X==0) nXStep=0; else if (X<0) nXStep=-1; else if (X>0) nXStep=1;
	if (Y==0) nYStep=0; else if (Y<0) nYStep=-1; else if (Y>0) nYStep=1;

	//����м�ո���Ŀ
	int nRoomCount=0;
	for (int i=1;i<=nCount;i++)
	{
		if (g_pMapAry[pt1.x+i*nXStep][pt1.y+i*nYStep]== NIL)
		{
			nRoomCount++;
		}
	}

	if (nRoomCount != nCount)
	{
		return false;
	}

	//�����б������Ҫ��������Ƿ����ϰ�
	int nBarrierCount=0;
	if (X*Y !=0)
	{
		for (int i=0;i<=nCount;i++)
		{
			if ((g_pMapAry[pt1.x+i*nXStep+nXStep][pt1.y+i*nYStep]== BARRIER) && (g_pMapAry[pt1.x+i*nXStep][pt1.y+i*nYStep+nYStep]== BARRIER))
			{
				nBarrierCount++;
			}
		}
	}

	if (nBarrierCount > 0)
	{
		return false;
	}

	//
	return true;
}
