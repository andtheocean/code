#include "StdAfx.h"
#include ".\tsp.h"
class CTsp
{
public:
	CTsp(void);
	~CTsp(void);

public:
	CAnt m_cAntAry[N_ANT_COUNT];
	CAnt m_cBestAnt; //������

	double m_dbRate; //�����Ϣ�غ���С��Ϣ�صı�ֵ

public:

	//��ʼ������
	void InitData(); 

	//��ʼ����
	void Search(); 

	//���»�����Ϣ��
	void UpdateTrial();

};
CTsp::CTsp(void)
{
	m_cBestAnt.m_dbPathLength=DB_MAX;
}

CTsp::~CTsp(void)
{
}


//��ʼ������
void CTsp::InitData() 
{

	//�����������м����
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

	//��̰���㷨�����ʼ�Ľ�
	m_cBestAnt.Init();
	m_cBestAnt.m_blGreedSearch=true;
	m_cBestAnt.Search();
	double Imax=1.0/(m_cBestAnt.m_dbPathLength*(1.0-ROU));

	//��ʼ��������Ϣ��
	for (int i=0;i<N_CITY_COUNT;i++)
	{
		for (int j=0;j<N_CITY_COUNT;j++)
		{
			g_Trial[i][j]=Imax;

			g_Prob[i][j]=pow(Imax,ALPHA)*g_DistanceBeta[i][j];
		}
	}

	//����������С��Ϣ��֮��ı�ֵ
	//dbTemp=pow(Pbest,1.0/(double)N_CITY_COUNT); //��Pbest��N_CITY_COUNT�η�
	dbTemp=exp(log(Pbest)/(double)N_CITY_COUNT); //��Pbest��N_CITY_COUNT�η�
	double dbFz=2.0*(1.0-dbTemp);
	double dbFm=((double)N_CITY_COUNT-2.0)*dbTemp;
	m_dbRate=dbFz/dbFm;

}


//���»�����Ϣ�أ�ֻ�õ�ǰ�������ȥ����
void CTsp::UpdateTrial()
{
	//��ʱ������Ϣ��
	double dbTempAry[N_CITY_COUNT][N_CITY_COUNT];
	memset(dbTempAry,0,sizeof(dbTempAry)); //��ȫ������Ϊ0

	//���������ӵ���Ϣ��,���浽��ʱ������
	int m=0;
	int n=0;
	//����Ŀǰ�����������µ���Ϣ��
	for (int j=1;j<N_CITY_COUNT;j++)
	{
		m=m_cBestAnt.m_nPath[j];
		n=m_cBestAnt.m_nPath[j-1];
		dbTempAry[n][m]=dbTempAry[n][m]+1.0/m_cBestAnt.m_dbPathLength;
		dbTempAry[m][n]=dbTempAry[n][m];
	}

	//�����кͿ�ʼ����֮�����Ϣ��
	n=m_cBestAnt.m_nPath[0];
	dbTempAry[n][m]=dbTempAry[n][m]+1.0/m_cBestAnt.m_dbPathLength;
	dbTempAry[m][n]=dbTempAry[n][m];


	//==================================================================
	//���»�����Ϣ��
	for (int i=0;i<N_CITY_COUNT;i++)
	{
		for (int j=0;j<N_CITY_COUNT;j++)
		{
			g_Trial[i][j]=g_Trial[i][j]*ROU+dbTempAry[i][j];  //���µĻ�����Ϣ�� = �������Ϣ�� + �����µ���Ϣ��
		}
	}

	//==================================================================
	//��黷����Ϣ�أ��������С�����ֵ�����棬�������µ���
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
		//ÿֻ��������һ��
		for (int j=0;j<N_ANT_COUNT;j++)
		{
			m_cAntAry[j].Search(); 
		}

		//������ѽ��
		for (int j=0;j<N_ANT_COUNT;j++)
		{
			if (m_cAntAry[j].m_dbPathLength < m_cBestAnt.m_dbPathLength)
			{
				m_cBestAnt=m_cAntAry[j];
			}
		}

		//���»�����Ϣ��
		UpdateTrial();

		//������
		sprintf(cBuf,"\n[%d] L=%.0f",i+1,m_cBestAnt.m_dbPathLength);
		printf(cBuf);
	}

}

