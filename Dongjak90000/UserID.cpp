#include "stdafx.h"

#include "UserID.h"


CUserID::CUserID()
	: m_ID(_T(""))
	, m_RankCnt(0)
{
}


CUserID::~CUserID()
{
}


CString CUserID::GetUserID()
{
	return m_ID;
}


int CUserID::GetUserRank(int i)
{
	return m_Rank[i];
}


void CUserID::SetGameRank(int time)
{
	//전체가 sorting된건 아니다.

	//기록된 랭크 갯수가 5개 미만일경우
	if (m_RankCnt < 5) {
		m_Rank[m_RankCnt] = time;
		m_RankCnt++;
	}
	//5개 이상일 경우
	else {
		int temp;
		//먼저 Sorting한다.
		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; j < 5; j++) {
				if (m_Rank[i] > m_Rank[j]) {
					temp = m_Rank[j];
					m_Rank[i] = m_Rank[j];
					m_Rank[j] = temp;
				}
			}
		}
		//time을 넣을지 말지 결정
		if (m_Rank[4] > time) {
			m_Rank[4] = time;
		}
	}
}


void CUserID::SetUserID(CString UserID)
{
	m_ID = UserID;
}


void CUserID::ChangeRank(CUserID tID)
{
	m_RankCnt = tID.m_RankCnt;
	for (int i = 0; i < m_RankCnt; i++) {
		m_Rank[i] = tID.GetUserRank(i);
	}
}
