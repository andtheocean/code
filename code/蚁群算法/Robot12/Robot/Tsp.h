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
	CAnt m_cBestAnt; //保存结果

	double** m_pTrail; //临时保存信息素

public:

	//初始化数据
	void InitData(); 

	//开始搜索
	void Search(); 

	//更新环境信息素
	void UpdateTrial(int nItCount);


};
