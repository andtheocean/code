#include "stdafx.h"
#include "common.h"


//===========================================
int** g_pMapAry; //��ͼ����ָ��
double** g_pMapTrail; //������Ϣ��
double** g_pMapLen; //����

double* g_pShortLenAry; //����������·������
double* g_pAvgLenAry; //�������ƽ��·������

int N_MAP_WIDTH=40; //��ͼ���
int N_MAP_HEIGHT=40; //��ͼ�߶�
int N_POINT_SIZE=10; //��Ĵ�С

CPoint g_ptStart; //��ʼ��
CPoint g_ptEnd; //������

bool g_blCanSolved; //�Ƿ��н�

HWND g_hwnd; //���

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  �� ;������ָ����Χ�ڵ��������
//
//  ˵ ������
//
//  �� �ڣ�int nLow �����������
//                     int nUpper ������������
//
//  �� �أ�int ,��Χ��[nLow,nUpper]
//
/////////////
int rnd(int nLow,int nUpper)
{	
	return nLow+(int)((nUpper-nLow)*rand()/(double)RAND_MAX+0.5);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  �� ;������ָ����Χ�ڵ����������
//
//  ˵ ������
//
//  �� �ڣ�double dbLow �����������
//                     double dbUpper �����������
//
//  �� �أ�double  ,��Χ��[dbLow,dbUpper]
//
/////////////
double rnd(double dbLow,double dbUpper)
{
	double dbTemp=rand()/(double)RAND_MAX;
	return dbLow+dbTemp*(dbUpper-dbLow);
}

//���ظ�������������ȡ����ĸ�����
double ROUND(double dbA)
{
	return (double)((int)(dbA+0.5));
}