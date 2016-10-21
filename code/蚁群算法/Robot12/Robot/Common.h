#pragma once
enum GRIDTYPE
{
	NIL=0,BARRIER,START,END,MOVED
};
enum ACTION
{
	LEFT_UP=0,RIGHT_UP,LEFT_DOWN,RIGHT_DOWN,
};


const int N_ANT_COUNT=10; //��������
const int N_IT_COUNT=200; //��������
const int N_SORT=1; //������ǰ�������ϸ�����Ϣ��

//��Ⱥ�㷨����

const double ALPHA=1.0;
const double BETA=2.0;
const double ROU=0.5; //��Ϣ�ش��ݲ���

const double DBQ=1000.0; //�ܵ���Ϣ��
const double DB_MAX=10e9; //һ����־��

extern int rnd(int nLow,int nUpper); //���������
extern double rnd(double dbLow,double dbUpper);
extern double ROUND(double dbA);

//========================================================================
//��ʾ���Ʋ���
const COLORREF CLR_LINE=RGB(220,220,220); //�ߵ���ɫ
const COLORREF CLR_BARRIER=RGB(100,100,100); //�ϰ������ɫ
const COLORREF CLR_START=RGB(0,200,0); //��ʼ�����ɫ
const COLORREF CLR_END=RGB(255,0,0); //���������ɫ
const COLORREF CLR_TABU=RGB(130,130,255); //·������ɫ

const int N_MARGIN=12; //��ͼ�߾�

extern HWND g_hwnd; //���

//========================================================================

const int N_MAX_MAP_WIDTH=100; //��ͼ�����
const int N_MAX_MAP_HEIGHT=100; //��ͼ���߶�

typedef CArray<CPoint,CPoint> CTabuArray; //����·��
extern int N_MAP_WIDTH; //��ͼ���
extern int N_MAP_HEIGHT; //��ͼ�߶�
extern int N_POINT_SIZE; //��Ĵ�С


extern int** g_pMapAry; //��ͼ����ָ��
extern double** g_pMapTrail; //������Ϣ��
extern double** g_pMapLen; //����

extern double* g_pShortLenAry; //����������·������
extern double* g_pAvgLenAry; //�������ƽ��·������

extern CPoint g_ptStart; //��ʼ��
extern CPoint g_ptEnd; //������

extern bool g_blCanSolved; //�Ƿ��н�


//========================================================================
//���嶯̬���ɶ�ά�����ģ��
template <class T> T** Create2DArray(int M,int N) 
{ 
 //   T** pAry=(T**)malloc(M*sizeof(T*));
 //   for (int i=0;i<M;i++)
 //   {
 //       *(pAry+i)=(T*)malloc(N*sizeof(T));
 //   }
//   return pAry;

	T **pAry=new T *[M];
	for (int i=0; i<M; i++) 
	{
		pAry[i] = new T[N];
	}

	return pAry;
}

//�����ͷŶ�̬���ɵĶ�ά�����ģ��
template <class T> void Free2DArray(T** pAry,int M)
{
	if (pAry == NULL)
	{
		return;
	}

	for (int i=0;i<M; i++) 
	{
		delete []pAry[i];
	}
	delete []pAry;
	pAry=NULL;

	//for (int i=0; i<M; i++) 
	//{
	//	delete *(pAry+i);
	//}
	//delete []pAry;
}