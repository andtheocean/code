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

	double m_dbRate; //最大信息素和最小信息素的比值

public:

	//初始化数据
	void InitData(); 

	//开始搜索
	void Search(); 

	//更新环境信息素
	void UpdateTrial();

};
