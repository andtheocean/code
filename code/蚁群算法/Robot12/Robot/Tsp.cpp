#include "StdAfx.h"
#include ".\tsp.h"

CTsp::CTsp(void)
{
	m_cBestAnt.m_dbPathLength=DB_MAX;
	
	g_pMapTrail=Create2DArray<double>(N_MAX_MAP_WIDTH,N_MAX_MAP_HEIGHT);	
	g_pMapLen=Create2DArray<double>(N_MAX_MAP_WIDTH,N_MAX_MAP_HEIGHT);	
	m_pTrail=Create2DArray<double>(N_MAX_MAP_WIDTH,N_MAX_MAP_HEIGHT);

	g_pShortLenAry=new double[N_IT_COUNT]; //����������·������
	g_pAvgLenAry=new double[N_IT_COUNT]; //�������ƽ��·������


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


//��ʼ������
void CTsp::InitData() 
{

	//�Ȱ���ѽ����·�����ó����
	m_cBestAnt.m_dbPathLength=DB_MAX; 

	//��ʼ��������Ϣ�أ�������ø��������Ŀ�ĵ�ľ���
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			g_pMapTrail[i][j]=DBQ;

			g_pMapLen[i][j]=sqrt((double)((i-g_ptEnd.x)*(i-g_ptEnd.x)+(j-g_ptEnd.y)*(j-g_ptEnd.y)))+1.0;
		}
	}

	//������̺�ƽ��·������Ϊ0
	for (int i=0;i<N_IT_COUNT;i++)
	{
		g_pShortLenAry[i]=0.0;
		g_pAvgLenAry[i]=0.0;
	}

	//�����н�Ϊtrue
	g_blCanSolved=true;

}


//���»�����Ϣ��
void CTsp::UpdateTrial(int nItCount)
{
	//��ʱ������Ϣ��
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			m_pTrail[i][j]=0.0;
		}
	}

	//�����ϰ�·����������
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

	//���������ӵ���Ϣ��,���浽��ʱ������
	CPoint pt;
	int nCount=0;
	double dbTemp=0.0;
	//��������ǰN_SORT���������µ���Ϣ��
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

	//ȫ����������
	dbTemp=1.0/m_cBestAnt.m_dbPathLength;

	nCount=(int)m_cBestAnt.m_tabuAry.GetCount();
	for (int j=0;j<nCount;j++)
	{
		pt=m_cBestAnt.m_tabuAry.GetAt(j);
		m_pTrail[pt.x][pt.y]=m_pTrail[pt.x][pt.y]+dbTemp;
	}

	//==================================================================
	//���»�����Ϣ��
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			g_pMapTrail[i][j]=g_pMapTrail[i][j]*ROU+m_pTrail[i][j];  //���µĻ�����Ϣ�� = �������Ϣ�� + �����µ���Ϣ��
		}
	}

	//==================================================================
	//����������·����ƽ��·������
	g_pShortLenAry[nItCount]=m_cAntAry[0].m_dbPathLength;
	for (int i=0;i<N_ANT_COUNT;i++)
	{
		g_pAvgLenAry[nItCount]=g_pAvgLenAry[nItCount]+m_cAntAry[i].m_dbPathLength;
	}
	g_pAvgLenAry[nItCount]=g_pAvgLenAry[nItCount]/((double)N_ANT_COUNT);

}

//��ʼ����
void CTsp::Search()
{

	int nCount=0;

	for (int i=0;i<N_IT_COUNT;i++)
	{

		//ÿֻ���ϳ�ʼ��һ��
		for (int j=0;j<N_ANT_COUNT;j++)
		{
			m_cAntAry[j].Init();
		}

		//ÿֻ��������һ��
		while (true)
		{
			nCount=0;

			for (int j=0;j<N_ANT_COUNT;j++) //ÿֻ�����ƶ�һ��
			{
				m_cAntAry[j].Move();
				if (m_cAntAry[j].m_blComplete == true)
				{
					nCount++; //�����������������
				}
			}

			//���ȫ��������������������ѭ��
			if (nCount == N_ANT_COUNT)
			{
				break;
			}

			//����޽⣬�����ѭ��
			if (g_blCanSolved == false)
			{
				break;
			}
		}

		//����޽⣬�����ѭ��
		if (g_blCanSolved == false)
		{
			break;
		}

		//������ѽ��
		for (int j=0;j<N_ANT_COUNT;j++)
		{
			if (m_cAntAry[j].m_dbPathLength < m_cBestAnt.m_dbPathLength)
			{
				m_cBestAnt.m_dbPathLength=m_cAntAry[j].m_dbPathLength;
				m_cBestAnt.m_tabuAry.Copy(m_cAntAry[j].m_tabuAry);
			}
		}

		//���»�����Ϣ��
		UpdateTrial(i);

		//������Ϣ��ʾ��������
		::SendMessage(g_hwnd,WM_USER+100,(WPARAM)i,0);
	}

	TRACE0("\n=== Complete! ===");
}

