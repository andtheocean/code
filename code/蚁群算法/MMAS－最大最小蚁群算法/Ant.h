#pragma once
#include "Common.h"
class CAnt
{
public:
	CAnt(void);
	~CAnt(void);

public:

	int m_nPath[N_CITY_COUNT]; //�����ߵ�·��
	double m_dbPathLength; //�����߹���·������

	int m_nAllowedCity[N_CITY_COUNT]; //ûȥ���ĳ���
	int m_nCurCityNo; //��ǰ���ڳ��б��
	int m_nMovedCityCount; //�Ѿ�ȥ���ĳ�������

	bool m_blGreedSearch; //�Ƿ�ʹ��̰��ԭ��ѡ����һ����
public:

	int ChooseNextCity(); //ѡ����һ������
	int GreedChooseNextCity(); //̰��ԭ��ѡ����һ������

	void Init(); //��ʼ��
	void Move(); //�����ڳ��м��ƶ�
	void Search(); //����·��
	void CalPathLength(); //���������߹���·������

};
