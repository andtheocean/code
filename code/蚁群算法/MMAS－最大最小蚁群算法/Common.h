#pragma once

const int N_CITY_COUNT=51; //��������
const int N_ANT_COUNT=20; //��������
const int N_IT_COUNT=10000; //��������

//��Ⱥ�㷨����
const double ALPHA=1.0;
const double BETA=2.0;
const double ROU=0.98; //��Ϣ�ز���ϵ����(1-ROU)������Ϣ�صĻӷ��ٶ�
const double Pbest=0.05; //����һ�������ҵ�����·���ĸ���

const double DBQ=100.0; //�ܵ���Ϣ��
const double DB_MAX=10e9; //һ����־��

extern double g_Trial[N_CITY_COUNT][N_CITY_COUNT]; //�������м���Ϣ��
extern double g_Distance[N_CITY_COUNT][N_CITY_COUNT]; //�������м����

extern double g_Prob[N_CITY_COUNT][N_CITY_COUNT];
extern double g_DistanceBeta[N_CITY_COUNT][N_CITY_COUNT];

extern int rnd(int nLow,int nUpper); //���������
extern double rnd(double dbLow,double dbUpper);
extern double ROUND(double dbA);

extern double x_Ary[N_CITY_COUNT];
extern double y_Ary[N_CITY_COUNT];

/*
                   1        2        3          4        5         6         7         8         9         10
============================================================
AS           436    454    445    448    450     460    445    457     452     446   //������Ⱥ�㷨
MMAS    432    430    431    427    433     426    436    431     431     430  //�����С��Ⱥ�㷨

*/