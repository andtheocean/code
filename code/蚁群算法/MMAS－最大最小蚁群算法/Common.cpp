#include "stdafx.h"
#include "common.h"

double g_Trial[N_CITY_COUNT][N_CITY_COUNT]; //两两城市间信息素
double g_Distance[N_CITY_COUNT][N_CITY_COUNT]; //两两城市间距离

double g_Prob[N_CITY_COUNT][N_CITY_COUNT];
double g_DistanceBeta[N_CITY_COUNT][N_CITY_COUNT];

//eil51.tsp城市坐标数据
double  x_Ary[N_CITY_COUNT]=
{
	37,49,52,20,40,21,17,31,52,51,
	42,31,5,12,36,52,27,17,13,57,
	62,42,16,8,7,27,30,43,58,58,
	37,38,46,61,62,63,32,45,59,5,
	10,21,5,30,39,32,25,25,48,56,
	30
};

double y_Ary[N_CITY_COUNT]=
{
	52,49,64,26,30,47,63,62,33,21,
	41,32,25,42,16,41,23,33,13,58,
	42,57,57,52,38,68,48,67,48,27,
	69,46,10,33,63,69,22,35,15,6,
	17,10,64,15,10,39,32,55,28,37,
	40
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  用 途：返回指定范围内的随机整数
//
//  说 明：无
//
//  接 口：int nLow 随机数的下限
//                     int nUpper 随整数的上限
//
//  返 回：int ,范围是[nLow,nUpper)
//
/////////////
int rnd(int nLow,int nUpper)
{
	
	return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);

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
//  返 回：double  ,范围是[dbLow,dbUpper)
//
/////////////
double rnd(double dbLow,double dbUpper)
{
	double dbTemp=rand()/((double)RAND_MAX+1.0);
	return dbLow+dbTemp*(dbUpper-dbLow);
}

//返回浮点数四舍五入取整后的浮点数
double ROUND(double dbA)
{
	return (double)((int)(dbA+0.5));
}