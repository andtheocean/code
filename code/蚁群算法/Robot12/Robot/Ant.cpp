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
	//清空蚂蚁走的路径
	m_tabuAry.RemoveAll(); 

	//设置蚂蚁走过的地方为地图初始状态
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			m_pMapAry[i][j]=g_pMapAry[i][j];
		}
	}

	//加入起始点，并设置起始点为去过了
	m_ptCurrent=g_ptStart;
	m_tabuAry.Add(m_ptCurrent); 
	m_pMapAry[m_ptCurrent.x][m_ptCurrent.y]=1; 

	//设置完成搜索标志为false
	m_blComplete=false;

	 //蚂蚁走过的路径长度设置为0
	m_dbPathLength=0.0;

}


//检查从(x0,y0)到(x,y)是否允许
bool CAnt::CheckXY(int x0,int y0,int x,int y)
{
	//越界
	if ((x<0) || (x>=N_MAP_WIDTH))
	{
		return false;
	}

	//越界
	if ((y<0) || (y>=N_MAP_HEIGHT))
	{
		return false;
	}

	//该位置是障碍或者去过了
	if ((m_pMapAry[x][y] == BARRIER) || (m_pMapAry[x][y] == MOVED))
	{
		return false;
	}

	//如果没有越界且位置为空，要检查如果是斜穿，斜穿点的两边是否有障碍

	if ((x-x0 == -1) && (y-y0 ==-1)) //新位置在左上角
	{
		if ((m_pMapAry[x+1][y] == BARRIER) && (m_pMapAry[x][y+1] == BARRIER))
		{
			return false;
		}
	}

	if ((x-x0 == 1) && (y-y0 ==-1)) //新位置在右上角
	{
		if ((m_pMapAry[x-1][y] == BARRIER) && (m_pMapAry[x][y+1] == BARRIER))
		{
			return false;
		}
	}

	if ((x-x0 == -1) && (y-y0 ==1)) //新位置在左下角
	{
		if ((m_pMapAry[x][y-1] == BARRIER) && (m_pMapAry[x+1][y] == BARRIER))
		{
			return false;
		}
	}

	if ((x-x0 == 1) && (y-y0 ==1)) //新位置在右下角
	{
		if ((m_pMapAry[x-1][y] == BARRIER) && (m_pMapAry[x][y-1] == BARRIER))
		{
			return false;
		}
	}

	//上面都不返回，则可以到达
	return true;
}

//选择下一个点
//返回值 为点的坐标位置
CPoint CAnt::ChooseNextCity()
{

	CPoint pt(-1,-1);  //返回结果，先暂时把其设置为-1,-1

	//==============================================================================
	//计算当前点和周围8个点的信息素总和
	//为了用循环进行处理，编码方便，当前所在点也计算一下
	double dbTotal=0.0;	
	double prob[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1}; // 保存城市被选中的概率

	int nIndex=-1;
	int nCount=0; //周围有几个点可以去

	
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

	//周围没有点可以去，则直接返回
	if (nCount ==0)
	{
		return pt;
	}


	////==============================================================================
	//对周围点进行轮盘选择

	nIndex=-1; //记录周围那个点被选择
	int nIndexFirst=-1; //记录第一个可以去的点
	double dbTemp=rnd(0.0,dbTotal); //取一个随机数
	for (int i=0;i<9;i++)
	{
		if (prob[i]>=0) //点可以去
		{
			dbTemp=dbTemp-prob[i]; //这个操作相当于转动轮盘
			if (dbTemp <= 0.0) //轮盘停止转动，记下点位置，直接跳出循环
			{
				nIndex=i;
				break;
			}

			//保存第一个可以去的点
			//如果没有点选中就用这个点作为结果返回
			if (nIndexFirst == -1) 
			{
				nIndexFirst=i;
			}
		}
	}

	//如果经过上面操作没有点被选中
	//就把第一个可去的点作为结果返回
	if (nIndex == -1)
	{
		nIndex = nIndexFirst;
	}
	//根据索引得到位置
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
	//返回结果
	return pt;

}

//求两点间距离
double CAnt::LenTwoPoint(CPoint pt1,CPoint pt2)
{
	return sqrt((double)((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y)));
}



//调整路径把弯路去掉
void CAnt::AdjustPathX()
{
	//=================================================
	//计算个数并复制数据
	int nCount=(int)m_tabuAry.GetCount();
	CPoint* pAry=new CPoint[nCount];

	CPoint pt;
	for (int i=0;i<nCount;i++)
	{
		pt=m_tabuAry.GetAt(i);
		pAry[i]=pt;
	}

	//=================================================
	//开始处理
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

			//如果从pt1可以直接移动到pt2
			if ((pt1.x==pt2.x) && (CanMove(pt1,pt2,nX,nY,nP) == true))
			{
					//中间删除点做标记
					for (int k=i+1;k<j;k++)
					{
						pAry[k].x=-1;
						pAry[k].y=-1;
					}

					//把中间直线上的点加入
					for (int k=1;k<=nP;k++)
					{
						pAry[i+k].x=pt1.x+k*nX;
						pAry[i+k].y=pt1.y+k*nY;
					}

					//跳转到j开始检查，跳出循环
					i=j-1;
					break;
			}
		}

	}

	//=================================================
	//整理结果
	m_tabuAry.RemoveAll();
	for (int i=0;i<nCount;i++)
	{
		if (pAry[i].x != -1)
		{
			m_tabuAry.Add(pAry[i]);
		}
	}
	//=================================================
	//删除数组
	if (pAry!=NULL)
	{
		delete []pAry;
		pAry=NULL;
	}

}

//调整路径把弯路去掉
void CAnt::AdjustPathXY()
{
	//=================================================
	//计算个数并复制数据
	int nCount=(int)m_tabuAry.GetCount();
	CPoint* pAry=new CPoint[nCount];

	CPoint pt;
	for (int i=0;i<nCount;i++)
	{
		pt=m_tabuAry.GetAt(i);
		pAry[i]=pt;
	}

	//=================================================
	//开始处理
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

			//如果从pt1可以直接移动到pt2
			if ((abs(pt1.x-pt2.x)==abs(pt1.y-pt2.y)) && (CanMove(pt1,pt2,nX,nY,nP) == true))
			{
					//中间删除点做标记
					for (int k=i+1;k<j;k++)
					{
						pAry[k].x=-1;
						pAry[k].y=-1;
					}

					//把中间直线上的点加入
					for (int k=1;k<=nP;k++)
					{
						pAry[i+k].x=pt1.x+k*nX;
						pAry[i+k].y=pt1.y+k*nY;
					}

					//跳转到j开始检查，跳出循环
					i=j-1;
					break;
			}
		}

	}

	//=================================================
	//整理结果
	m_tabuAry.RemoveAll();
	for (int i=0;i<nCount;i++)
	{
		if (pAry[i].x != -1)
		{
			m_tabuAry.Add(pAry[i]);
		}
	}
	//=================================================
	//删除数组
	if (pAry!=NULL)
	{
		delete []pAry;
		pAry=NULL;
	}

}

//调整路径把弯路去掉
void CAnt::AdjustPathY()
{
	//=================================================
	//计算个数并复制数据
	int nCount=(int)m_tabuAry.GetCount();
	CPoint* pAry=new CPoint[nCount];

	CPoint pt;
	for (int i=0;i<nCount;i++)
	{
		pt=m_tabuAry.GetAt(i);
		pAry[i]=pt;
	}

	//=================================================
	//开始处理
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

			//如果从pt1可以直接移动到pt2
			if ((pt1.y==pt2.y) && (CanMove(pt1,pt2,nX,nY,nP) == true))
			{
					//中间删除点做标记
					for (int k=i+1;k<j;k++)
					{
						pAry[k].x=-1;
						pAry[k].y=-1;
					}

					//把中间直线上的点加入
					for (int k=1;k<=nP;k++)
					{
						pAry[i+k].x=pt1.x+k*nX;
						pAry[i+k].y=pt1.y+k*nY;
					}

					//跳转到j开始检查，跳出循环
					i=j-1;
					break;
			}
		}

	}

	//=================================================
	//整理结果
	m_tabuAry.RemoveAll();
	for (int i=0;i<nCount;i++)
	{
		if (pAry[i].x != -1)
		{
			m_tabuAry.Add(pAry[i]);
		}
	}
	//=================================================
	//删除数组
	if (pAry!=NULL)
	{
		delete []pAry;
		pAry=NULL;
	}

}

void CAnt::Move()
{

	//如果蚂蚁完成了搜索，就不再移动
	if (m_blComplete == true)
	{
		return;
	}

	//蚂蚁没有完成搜索，则继续搜索
	CPoint ptNext=ChooseNextCity(); //选择下一个城市

	if ((ptNext.x<0) && (ptNext.y<0)) //没有点可以选择，说明蚂蚁陷入陷阱，则后退一步
	{
		int nCount=(int)m_tabuAry.GetCount();
		if (nCount>=2)
		{
			m_ptCurrent=m_tabuAry.GetAt(nCount-2); //后退一步
			m_tabuAry.RemoveAt(nCount-1); //从路径里移除当前点
		}
		else //如果已经无法后退，说明无解
		{
			g_blCanSolved=false;
		}
	}
	else //有点可以选择，则前进
	{
		m_tabuAry.Add(ptNext);
		m_pMapAry[ptNext.x][ptNext.y]=MOVED; //设置这个点为去过了
		m_ptCurrent=ptNext;

		//减少去过点的信息素
		//g_pMapTrail[ptNext.x][ptNext.y]=g_pMapTrail[ptNext.x][ptNext.y]*ROU;

		//检查是否到达终点
		if (m_ptCurrent == g_ptEnd)
		{
			//AdjustPathX();
			//AdjustPathY();
			//AdjustPathXY();

			////再调整一次
			////因为调整完后可能还产生新的更短路径没有直接连接
			//AdjustPathX();
			//AdjustPathY();
			//AdjustPathXY();

			m_blComplete=true;
			CalPathLength();
		}
	}

}

//测试
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



//计算蚂蚁走过的路径长度
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


//从p1是否可以直接移动到p2
bool CAnt::CanMove(CPoint pt1,CPoint pt2,int &nXStep,int &nYStep,int &nCount)
{
	int X=pt2.x-pt1.x;
	int Y=pt2.y-pt1.y;
		
	//先判断是否在同一直线上
	if ((X==0) || (Y==0) || (X==Y) || (X==(-Y)))
	{
	}
	else
	{
		return false;
	}

	//中间有几个点
	nCount=max(abs(X),abs(Y))-1;

	//X Y 的递增值
	if (X==0) nXStep=0; else if (X<0) nXStep=-1; else if (X>0) nXStep=1;
	if (Y==0) nYStep=0; else if (Y<0) nYStep=-1; else if (Y>0) nYStep=1;

	//检查中间空格数目
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

	//如果是斜穿，还要检查两边是否有障碍
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
