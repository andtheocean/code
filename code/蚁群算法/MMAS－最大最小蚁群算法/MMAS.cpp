// MMAS.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Tsp.h"

int main()
{
	//��ʼ���������
	time_t tm;
	time(&tm);
	unsigned int nSeed=(unsigned int)tm;
	srand(nSeed);

	//��ʼ����
	CTsp tsp;

	tsp.InitData();
	tsp.Search();

	//������
	printf("\nThe best tour is :\n\n");

	char cBuf[128];
	for (int i=0;i<N_CITY_COUNT;i++)
	{
		sprintf(cBuf,"%d ",tsp.m_cBestAnt.m_nPath[i]+1);
		printf(cBuf);
	}

	sprintf(cBuf,"\n\nThe rand seed is : %d ",nSeed);
	printf(cBuf);

	printf("\n\nPress any key to exit!");
	getchar();

	return 0;
}

