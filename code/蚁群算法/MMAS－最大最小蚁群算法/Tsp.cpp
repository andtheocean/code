#include "StdAfx.h"
#include ".\tsp.h"
class CTsp
{
public:
	CTsp(void);
	~CTsp(void);

public:
	CAnt m_cAntAry[N_ANT_COUNT];
	CAnt m_cBestAnt; //保存结果

	double m_dbRate; //最大信息素和最小信息素的比值

public:

	//初始化数据
	void InitData(); 

	//开始搜索
	void Search(); 

	//更新环境信息素
	void UpdateTrial();

};
CTsp::CTsp(void)
{
	m_cBestAnt.m_dbPathLength=DB_MAX;
}

CTsp::~CTsp(void)
{
}


//初始化数据
void CTsp::InitData() 
{

	//计算两两城市间距离
	double dbTemp=0.0;
	for (int i=0;i<N_CITY_COUNT;i++)
	{
		for (int j=0;j<N_CITY_COUNT;j++)
		{
			dbTemp=(x_Ary[i]-x_Ary[j])*(x_Ary[i]-x_Ary[j])+(y_Ary[i]-y_Ary[j])*(y_Ary[i]-y_Ary[j]);
			dbTemp=pow(dbTemp,0.5);
			g_Distance[i][j]=ROUND(dbTemp);

			g_DistanceBeta[i][j]=pow(1.0/g_Distance[i][j],BETA);
		}
	}

	//用贪心算法生成最开始的解
	m_cBestAnt.Init();
	m_cBestAnt.m_blGreedSearch=true;
	m_cBestAnt.Search();
	double Imax=1.0/(m_cBestAnt.m_dbPathLength*(1.0-ROU));

	//初始化环境信息素
	for (int i=0;i<N_CITY_COUNT;i++)
	{
		for (int j=0;j<N_CITY_COUNT;j++)
		{
			g_Trial[i][j]=Imax;

			g_Prob[i][j]=pow(Imax,ALPHA)*g_DistanceBeta[i][j];
		}
	}

	//计算最大和最小信息素之间的比值
	//dbTemp=pow(Pbest,1.0/(double)N_CITY_COUNT); //对Pbest开N_CITY_COUNT次方
	dbTemp=exp(log(Pbest)/(double)N_CITY_COUNT); //对Pbest开N_CITY_COUNT次方
	double dbFz=2.0*(1.0-dbTemp);
	double dbFm=((double)N_CITY_COUNT-2.0)*dbTemp;
	m_dbRate=dbFz/dbFm;

}


//更新环境信息素，只用当前最好蚂蚁去更新
void CTsp::UpdateTrial()
{
	//临时保存信息素
	double dbTempAry[N_CITY_COUNT][N_CITY_COUNT];
	memset(dbTempAry,0,sizeof(dbTempAry)); //先全部设置为0

	//计算新增加的信息素,保存到临时数组里
	int m=0;
	int n=0;
	//计算目前最优蚂蚁留下的信息素
	for (int j=1;j<N_CITY_COUNT;j++)
	{
		m=m_cBestAnt.m_nPath[j];
		n=m_cBestAnt.m_nPath[j-1];
		dbTempAry[n][m]=dbTempAry[n][m]+1.0/m_cBestAnt.m_dbPathLength;
		dbTempAry[m][n]=dbTempAry[n][m];
	}

	//最后城市和开始城市之间的信息素
	n=m_cBestAnt.m_nPath[0];
	dbTempAry[n][m]=dbTempAry[n][m]+1.0/m_cBestAnt.m_dbPathLength;
	dbTempAry[m][n]=dbTempAry[n][m];


	//==================================================================
	//更新环境信息素
	for (int i=0;i<N_CITY_COUNT;i++)
	{
		for (int j=0;j<N_CITY_COUNT;j++)
		{
			g_Trial[i][j]=g_Trial[i][j]*ROU+dbTempAry[i][j];  //最新的环境信息素 = 留存的信息素 + 新留下的信息素
		}
	}

	//==================================================================
	//检查环境信息素，如果在最小和最大值的外面，则将其重新调整
	double Imax=1.0/(m_cBestAnt.m_dbPathLength*(1.0-ROU));
	double Imin=Imax*m_dbRate;

	for (int i=0;i<N_CITY_COUNT;i++)
	{
		for (int j=0;j<N_CITY_COUNT;j++)
		{
			if (g_Trial[i][j] < Imin)
			{
				g_Trial[i][j] = Imin;
			}

			if (g_Trial[i][j] > Imax)
			{
				g_Trial[i][j] = Imax;
			}

		}
	}


	for (int i=0;i<N_CITY_COUNT;i++)
	{
		for (int j=0;j<N_CITY_COUNT;j++)
		{
			g_Prob[i][j]=pow(g_Trial[i][j],ALPHA)*g_DistanceBeta[i][j];
		}
	}

}


void CTsp::Search()
{

	char cBuf[256];

	for (int i=0;i<N_IT_COUNT;i++)
	{
		//每只蚂蚁搜索一遍
		for (int j=0;j<N_ANT_COUNT;j++)
		{
			m_cAntAry[j].Search(); 
		}

		//保存最佳结果
		for (int j=0;j<N_ANT_COUNT;j++)
		{
			if (m_cAntAry[j].m_dbPathLength < m_cBestAnt.m_dbPathLength)
			{
				m_cBestAnt=m_cAntAry[j];
			}
		}

		//更新环境信息素
		UpdateTrial();

		//输出结果
		sprintf(cBuf,"\n[%d] L=%.0f",i+1,m_cBestAnt.m_dbPathLength);
		printf(cBuf);
	}

}

