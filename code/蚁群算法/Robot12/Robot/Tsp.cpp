#include "StdAfx.h"
#include ".\tsp.h"

CTsp::CTsp(void)
{
	m_cBestAnt.m_dbPathLength=DB_MAX;
	
	g_pMapTrail=Create2DArray<double>(N_MAX_MAP_WIDTH,N_MAX_MAP_HEIGHT);	
	g_pMapLen=Create2DArray<double>(N_MAX_MAP_WIDTH,N_MAX_MAP_HEIGHT);	
	m_pTrail=Create2DArray<double>(N_MAX_MAP_WIDTH,N_MAX_MAP_HEIGHT);

	g_pShortLenAry=new double[N_IT_COUNT]; //保存各代最短路径长度
	g_pAvgLenAry=new double[N_IT_COUNT]; //保存各代平均路径长度


}

CTsp::~CTsp(void)
{
	Free2DArray(g_pMapTrail,N_MAX_MAP_WIDTH);
	Free2DArray(g_pMapLen,N_MAX_MAP_WIDTH);
	Free2DArray(m_pTrail,N_MAX_MAP_WIDTH);

	if (g_pShortLenAry == NULL)
	{
		delete []g_pShortLenAry;
		g_pShortLenAry=NULL;
	}

	if (g_pAvgLenAry == NULL)
	{
		delete []g_pAvgLenAry;
		g_pAvgLenAry=NULL;
	}

}


//初始化数据
void CTsp::InitData() 
{

	//先把最佳结果的路径设置成最大
	m_cBestAnt.m_dbPathLength=DB_MAX; 

	//初始化环境信息素，并计算好各个点距离目的点的距离
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			g_pMapTrail[i][j]=DBQ;

			g_pMapLen[i][j]=sqrt((double)((i-g_ptEnd.x)*(i-g_ptEnd.x)+(j-g_ptEnd.y)*(j-g_ptEnd.y)))+1.0;
		}
	}

	//设置最短和平均路径长度为0
	for (int i=0;i<N_IT_COUNT;i++)
	{
		g_pShortLenAry[i]=0.0;
		g_pAvgLenAry[i]=0.0;
	}

	//设置有解为true
	g_blCanSolved=true;

}


//更新环境信息素
void CTsp::UpdateTrial(int nItCount)
{
	//临时保存信息素
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			m_pTrail[i][j]=0.0;
		}
	}

	//对蚂蚁按路径长短排序
	CAnt cAntTemp;
	for (int i=0;i<N_ANT_COUNT-1;i++)
	{
		for (int j=i+1;j<N_ANT_COUNT;j++)
		{
			if (m_cAntAry[i].m_dbPathLength>m_cAntAry[j].m_dbPathLength)
			{
				cAntTemp.m_dbPathLength=m_cAntAry[i].m_dbPathLength;
				cAntTemp.m_tabuAry.Copy(m_cAntAry[i].m_tabuAry);

				m_cAntAry[i].m_dbPathLength=m_cAntAry[j].m_dbPathLength;
				m_cAntAry[i].m_tabuAry.Copy(m_cAntAry[j].m_tabuAry);

				m_cAntAry[j].m_dbPathLength=cAntTemp.m_dbPathLength;
				m_cAntAry[j].m_tabuAry.Copy(cAntTemp.m_tabuAry);
			}
		}
	}

	//CString str="";
	//str.Format("%.2f\n",m_cAntAry[0].m_dbPathLength);
	//TRACE0(str);

	//计算新增加的信息素,保存到临时数组里
	CPoint pt;
	int nCount=0;
	double dbTemp=0.0;
	//计算排名前N_SORT的蚂蚁留下的信息素
	for (int i=0;i<N_SORT;i++)
	{
		dbTemp=1.0/m_cAntAry[i].m_dbPathLength;

		nCount=(int)m_cAntAry[i].m_tabuAry.GetCount();
		for (int j=0;j<nCount;j++)
		{
			pt=m_cAntAry[i].m_tabuAry.GetAt(j);
			m_pTrail[pt.x][pt.y]=m_pTrail[pt.x][pt.y]+dbTemp;
		}
	}

	//全局最优蚂蚁
	dbTemp=1.0/m_cBestAnt.m_dbPathLength;

	nCount=(int)m_cBestAnt.m_tabuAry.GetCount();
	for (int j=0;j<nCount;j++)
	{
		pt=m_cBestAnt.m_tabuAry.GetAt(j);
		m_pTrail[pt.x][pt.y]=m_pTrail[pt.x][pt.y]+dbTemp;
	}

	//==================================================================
	//更新环境信息素
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			g_pMapTrail[i][j]=g_pMapTrail[i][j]*ROU+m_pTrail[i][j];  //最新的环境信息素 = 留存的信息素 + 新留下的信息素
		}
	}

	//==================================================================
	//保存各代最短路径和平均路径长度
	g_pShortLenAry[nItCount]=m_cAntAry[0].m_dbPathLength;
	for (int i=0;i<N_ANT_COUNT;i++)
	{
		g_pAvgLenAry[nItCount]=g_pAvgLenAry[nItCount]+m_cAntAry[i].m_dbPathLength;
	}
	g_pAvgLenAry[nItCount]=g_pAvgLenAry[nItCount]/((double)N_ANT_COUNT);

}

//开始搜索
void CTsp::Search()
{

	int nCount=0;

	for (int i=0;i<N_IT_COUNT;i++)
	{

		//每只蚂蚁初始化一下
		for (int j=0;j<N_ANT_COUNT;j++)
		{
			m_cAntAry[j].Init();
		}

		//每只蚂蚁搜索一遍
		while (true)
		{
			nCount=0;

			for (int j=0;j<N_ANT_COUNT;j++) //每只蚂蚁移动一步
			{
				m_cAntAry[j].Move();
				if (m_cAntAry[j].m_blComplete == true)
				{
					nCount++; //完成搜索的蚂蚁数量
				}
			}

			//如果全部蚂蚁完成搜索，则结束循环
			if (nCount == N_ANT_COUNT)
			{
				break;
			}

			//如果无解，则结束循环
			if (g_blCanSolved == false)
			{
				break;
			}
		}

		//如果无解，则结束循环
		if (g_blCanSolved == false)
		{
			break;
		}

		//保存最佳结果
		for (int j=0;j<N_ANT_COUNT;j++)
		{
			if (m_cAntAry[j].m_dbPathLength < m_cBestAnt.m_dbPathLength)
			{
				m_cBestAnt.m_dbPathLength=m_cAntAry[j].m_dbPathLength;
				m_cBestAnt.m_tabuAry.Copy(m_cAntAry[j].m_tabuAry);
			}
		}

		//更新环境信息素
		UpdateTrial(i);

		//发送消息显示搜索进度
		::SendMessage(g_hwnd,WM_USER+100,(WPARAM)i,0);
	}

	TRACE0("\n=== Complete! ===");
}

