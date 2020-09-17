#pragma once

class CUserID
{

private:
	int m_Rank[5];
	CString m_ID;
public:
	CUserID();
	~CUserID();

public:
	CString GetUserID();;
	int GetUserRank(int i);
	void SetGameRank(int time);
	void SetUserID(CString UserID);
	void ChangeRank(CUserID tID);
	int m_RankCnt;
};