#include "stdafx.h"
#include "common.h"


//===========================================
int** g_pMapAry; //地图数据指针
double** g_pMapTrail; //环境信息素
double** g_pMapLen; //距离

double* g_pShortLenAry; //保存各代最短路径长度
double* g_pAvgLenAry; //保存各代平均路径长度

int N_MAP_WIDTH=40; //地图宽度
int N_MAP_HEIGHT=40; //地图高度
int N_POINT_SIZE=10; //点的大小

CPoint g_ptStart; //开始点
CPoint g_ptEnd; //结束点

bool g_blCanSolved; //是否有解

HWND g_hwnd; //句柄

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  用 途：返回指定范围内的随机整数
//
//  说 明：无
//
//  接 口：int nLow 随机数的下限
//                     int nUpper 随整数的上限
//
//  返 回：int ,范围是[nLow,nUpper]
//
/////////////
int rnd(int nLow,int nUpper)
{	
	return nLow+(int)((nUpper-nLow)*rand()/(double)RAND_MAX+0.5);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  用 途：返回指定范围内的随机浮点数
//
//  说 明：无
//
//  接 口：double dbLow 随机数的下限
//                     double dbUpper 随机数的上限
//
//  返 回：double  ,范围是[dbLow,dbUpper]
//
/////////////
double rnd(double dbLow,double dbUpper)
{
	double dbTemp=rand()/(double)RAND_MAX;
	return dbLow+dbTemp*(dbUpper-dbLow);
}

//返回浮点数四舍五入取整后的浮点数
double ROUND(double dbA)
{
	return (double)((int)(dbA+0.5));
}