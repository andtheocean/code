#pragma once
enum GRIDTYPE
{
	NIL=0,BARRIER,START,END,MOVED
};
enum ACTION
{
	LEFT_UP=0,RIGHT_UP,LEFT_DOWN,RIGHT_DOWN,
};


const int N_ANT_COUNT=10; //蚂蚁数量
const int N_IT_COUNT=200; //迭代次数
const int N_SORT=1; //用排名前几的蚂蚁更新信息素

//蚁群算法参数

const double ALPHA=1.0;
const double BETA=2.0;
const double ROU=0.5; //信息素传递参数

const double DBQ=1000.0; //总的信息素
const double DB_MAX=10e9; //一个标志数

extern int rnd(int nLow,int nUpper); //返回随机数
extern double rnd(double dbLow,double dbUpper);
extern double ROUND(double dbA);

//========================================================================
//显示控制参数
const COLORREF CLR_LINE=RGB(220,220,220); //线的颜色
const COLORREF CLR_BARRIER=RGB(100,100,100); //障碍物的颜色
const COLORREF CLR_START=RGB(0,200,0); //开始点的颜色
const COLORREF CLR_END=RGB(255,0,0); //结束点的颜色
const COLORREF CLR_TABU=RGB(130,130,255); //路径的颜色

const int N_MARGIN=12; //视图边距

extern HWND g_hwnd; //句柄

//========================================================================

const int N_MAX_MAP_WIDTH=100; //地图最大宽度
const int N_MAX_MAP_HEIGHT=100; //地图最大高度

typedef CArray<CPoint,CPoint> CTabuArray; //保存路径
extern int N_MAP_WIDTH; //地图宽度
extern int N_MAP_HEIGHT; //地图高度
extern int N_POINT_SIZE; //点的大小


extern int** g_pMapAry; //地图数据指针
extern double** g_pMapTrail; //环境信息素
extern double** g_pMapLen; //距离

extern double* g_pShortLenAry; //保存各代最短路径长度
extern double* g_pAvgLenAry; //保存各代平均路径长度

extern CPoint g_ptStart; //开始点
extern CPoint g_ptEnd; //结束点

extern bool g_blCanSolved; //是否有解


//========================================================================
//定义动态生成二维数组的模板
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

//定义释放动态生成的二维数组的模板
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