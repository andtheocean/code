#include "StdAfx.h"
#include ".\ant.h"

CAnt::CAnt(void)
{
	m_blGreedSearch=false;
}

CAnt::~CAnt(void)
	{
}


void CAnt::Init()
{

	for (int i=0;i<N_CITY_COUNT;i++)
	{
		m_nAllowedCity[i]=1; //����ȫ������Ϊû��ȥ��
		m_nPath[i]=0; //�����ߵ�·��ȫ������Ϊ0
	}

	//�����߹���·����������Ϊ0
	m_dbPathLength=0.0; 

	//���ѡ��һ����������
	m_nCurCityNo=rnd(0,N_CITY_COUNT);

	//���ó�������
	m_nPath[0]=m_nCurCityNo;

	//��ʶ��������Ϊ�Ѿ�ȥ����
	m_nAllowedCity[m_nCurCityNo]=0; 

	//�Ѿ�ȥ���ĳ�����������Ϊ1
	m_nMovedCityCount=1; 

	//��ʹ��̰��ԭ��ѡ����һ����
	m_blGreedSearch=false;

}

//̰��ԭ��ѡ����һ������
int CAnt::GreedChooseNextCity()
{
	int nSelectedCity=-1; //���ؽ��������ʱ��������Ϊ-1
	double dbLen=DB_MAX;

	for (int i=0;i<N_CITY_COUNT;i++)
	{
		if (m_nAllowedCity[i] == 1) //����ûȥ��
		{
			if (g_Distance[m_nCurCityNo][i] < dbLen)
			{
				dbLen=g_Distance[m_nCurCityNo][i];
				nSelectedCity=i;
			}
		}
	}

	return nSelectedCity;
}

//ѡ����һ������
//����ֵ Ϊ���б��
int CAnt::ChooseNextCity()
{

	int nSelectedCity=-1; //���ؽ��������ʱ��������Ϊ-1

	//==============================================================================
	//���㵱ǰ���к�ûȥ���ĳ���֮�����Ϣ���ܺ�
	double dbTotal=0.0;	
	double prob[N_CITY_COUNT]; // ������б�ѡ�еĸ���

	for (int i=0;i<N_CITY_COUNT;i++)
	{
		if (m_nAllowedCity[i] == 1) //����ûȥ��
		{
//			prob[i]=pow(g_Trial[m_nCurCityNo][i],ALPHA)*pow(1.0/g_Distance[m_nCurCityNo][i],BETA); //�ó��к͵�ǰ���м����Ϣ��
			prob[i]=g_Prob[m_nCurCityNo][i];
			dbTotal=dbTotal+prob[i]; //�ۼ���Ϣ�أ��õ��ܺ�
		}
		else
		{
			prob[i]=0.0;
		}
	}

	//==============================================================================
	//����ѡ��
	double dbTemp=0.0;
	if (dbTotal > 0.0) //�ܵ���Ϣ��ֵ����0
	{
		dbTemp=rnd(0.0,dbTotal); //ȡһ�������

		for (int i=0;i<N_CITY_COUNT;i++)
		{
			if (m_nAllowedCity[i] == 1) //����ûȥ��
			{
				dbTemp=dbTemp-prob[i]; //��������൱��ת�����̣����������ѡ����Ϥ����ϸ����һ��
				if (dbTemp < 0.0) //����ֹͣת�������³��б�ţ�ֱ������ѭ��
				{
					nSelectedCity=i;
					break;
				}
			}
		}
	}

	//==============================================================================
	//������м����Ϣ�طǳ�С ( С����double�ܹ���ʾ����С�����ֻ�ҪС )
	//��ô���ڸ�����������ԭ���������ĸ����ܺͿ���Ϊ0
	//����־�������������û�г��б�ѡ�����
	//��������������Ͱѵ�һ��ûȥ���ĳ�����Ϊ���ؽ��
	if (nSelectedCity == -1)
	{
		for (int i=0;i<N_CITY_COUNT;i++)
		{
			if (m_nAllowedCity[i] == 1) //����ûȥ��
			{
				nSelectedCity=i;
				break;
			}
		}
	}

	//==============================================================================
	//���ؽ��
	return nSelectedCity;
}

void CAnt::Move()
{
	int nCityNo=0;

	//ѡ����һ������
	if (m_blGreedSearch == true)
		nCityNo=GreedChooseNextCity(); 
	else
		nCityNo=ChooseNextCity();


	m_nPath[m_nMovedCityCount]=nCityNo; //�����ߵ�·��
	m_nAllowedCity[nCityNo]=0;//ûȥ���ĳ���
	m_nCurCityNo=nCityNo; //��ǰ���ڳ��б��
	m_nMovedCityCount++; //�Ѿ�ȥ���ĳ�������
}

//����һ��
void CAnt::Search()
{
	Init();

	while (m_nMovedCityCount < N_CITY_COUNT)
	{
		Move();
	}

	CalPathLength();
}


//���������߹���·������
void CAnt::CalPathLength()
{
	m_dbPathLength=0.0;
	int m=0;
	int n=0;
	for (int i=1;i<N_CITY_COUNT;i++)
	{
		m=m_nPath[i];
		n=m_nPath[i-1];
		m_dbPathLength=m_dbPathLength+g_Distance[m][n];
	}

	//���ϴ������з��س������еľ���
	n=m_nPath[0];
	m_dbPathLength=m_dbPathLength+g_Distance[m][n];	

}
