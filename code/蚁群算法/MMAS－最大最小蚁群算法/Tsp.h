#pragma once
#include "Common.h"
#include "Ant.h"

class CTsp
{
public:
	CTsp(void);
	~CTsp(void);

public:
	CAnt m_cAntAry[N_ANT_COUNT];
	CAnt m_cBestAnt; //������

	double m_dbRate; //�����Ϣ�غ���С��Ϣ�صı�ֵ

public:

	//��ʼ������
	void InitData(); 

	//��ʼ����
	void Search(); 

	//���»�����Ϣ��
	void UpdateTrial();

};
