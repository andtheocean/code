#pragma once

const int N_CITY_COUNT=51; //城市数量
const int N_ANT_COUNT=20; //蚂蚁数量
const int N_IT_COUNT=10000; //迭代次数

//蚁群算法参数
const double ALPHA=1.0;
const double BETA=2.0;
const double ROU=0.98; //信息素残留系数，(1-ROU)就是信息素的挥发速度
const double Pbest=0.05; //蚂蚁一次搜索找到最优路径的概率

const double DBQ=100.0; //总的信息素
const double DB_MAX=10e9; //一个标志数

extern double g_Trial[N_CITY_COUNT][N_CITY_COUNT]; //两两城市间信息素
extern double g_Distance[N_CITY_COUNT][N_CITY_COUNT]; //两两城市间距离

extern double g_Prob[N_CITY_COUNT][N_CITY_COUNT];
extern double g_DistanceBeta[N_CITY_COUNT][N_CITY_COUNT];

extern int rnd(int nLow,int nUpper); //返回随机数
extern double rnd(double dbLow,double dbUpper);
extern double ROUND(double dbA);

extern double x_Ary[N_CITY_COUNT];
extern double y_Ary[N_CITY_COUNT];

/*
                   1        2        3          4        5         6         7         8         9         10
============================================================
AS           436    454    445    448    450     460    445    457     452     446   //基本蚁群算法
MMAS    432    430    431    427    433     426    436    431     431     430  //最大最小蚁群算法

*/