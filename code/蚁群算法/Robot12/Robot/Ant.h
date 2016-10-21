#pragma once
#include "Common.h"
class CAnt
{
public:
	CAnt(void);
	~CAnt(void);

public:

	CPoint m_ptCurrent; //���ϵ�ǰ����λ��
	CTabuArray m_tabuAry; //���������ߵ�·��
	int** m_pMapAry; //��¼�����߹���λ��

	bool m_blComplete; //�����Ƿ����
	double m_dbPathLength; //�����߹���·������


public:

	bool CheckXY(int x0,int y0,int x,int y); //����(x0,y0)��(x,y)�Ƿ�����


	void Init(); //��ʼ��,Move֮ǰ�ȵ���һ��
	void Move(); //�����ڳ��м��ƶ�
	void CalPathLength(); //���������߹���·������

	void AdjustPathX(); //����·������·ȥ��
	void AdjustPathY(); //����·������·ȥ��
	void AdjustPathXY(); //����·������·ȥ��

	//void AdjustPath(); //����·������·ȥ��
	bool CanMove(CPoint pt1,CPoint pt2,int &nXStep,int &nYStep,int &nCount); //��p1�Ƿ����ֱ���ƶ���p2

	double LenTwoPoint(CPoint pt1,CPoint pt2); //����������

	CPoint ChooseNextCity(); //ѡ����һ����

	void PrintPath(); //����

};
