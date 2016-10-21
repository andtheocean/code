#pragma once
#include "Common.h"
class CAnt
{
public:
	CAnt(void);
	~CAnt(void);

public:

	CPoint m_ptCurrent; //蚂蚁当前所在位置
	CTabuArray m_tabuAry; //保存蚂蚁走的路径
	int** m_pMapAry; //记录蚂蚁走过的位置

	bool m_blComplete; //搜索是否完成
	double m_dbPathLength; //蚂蚁走过的路径长度


public:

	bool CheckXY(int x0,int y0,int x,int y); //检查从(x0,y0)到(x,y)是否允许


	void Init(); //初始化,Move之前先调用一次
	void Move(); //蚂蚁在城市间移动
	void CalPathLength(); //计算蚂蚁走过的路径长度

	void AdjustPathX(); //调整路径把弯路去掉
	void AdjustPathY(); //调整路径把弯路去掉
	void AdjustPathXY(); //调整路径把弯路去掉

	//void AdjustPath(); //调整路径把弯路去掉
	bool CanMove(CPoint pt1,CPoint pt2,int &nXStep,int &nYStep,int &nCount); //从p1是否可以直接移动到p2

	double LenTwoPoint(CPoint pt1,CPoint pt2); //求两点间距离

	CPoint ChooseNextCity(); //选择下一个点

	void PrintPath(); //测试

};
