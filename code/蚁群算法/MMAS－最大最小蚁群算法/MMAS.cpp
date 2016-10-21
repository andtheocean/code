// MMAS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Tsp.h"

int main()
{
	//初始化随机种子
	time_t tm;
	time(&tm);
	unsigned int nSeed=(unsigned int)tm;
	srand(nSeed);

	//开始搜索
	CTsp tsp;

	tsp.InitData();
	tsp.Search();

	//输出结果
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

