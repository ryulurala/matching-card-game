#pragma once

#include "UserID.h"

class CRank
{
public:
	CRank();
	~CRank();
private:
	CString *m_TotalName;
	CString *m_TotalRank;
public:
	CString GetTotalName(int i);
	CString GetTotalRank(int i);
	void SetTotalRank(CUserID * ID, int IDCnt);
	int totalRankCnt;
};

