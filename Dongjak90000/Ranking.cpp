// Ranking.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Dongjak90000.h"
#include "Ranking.h"
#include "afxdialogex.h"


// CRanking 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRanking, CDialogEx)

CRanking::CRanking(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RANKING, pParent)
{

}

CRanking::~CRanking()
{
}

void CRanking::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RANKING, m_listRanking);
}


BEGIN_MESSAGE_MAP(CRanking, CDialogEx)
END_MESSAGE_MAP()


// CRanking 메시지 처리기입니다.


BOOL CRanking::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	LPWSTR list[3] = { _T("순위"), _T("ID"), _T("점수") };
	int nWidth[3] = { 50, 150, 196 };
	CString strCount;
	int nCount = m_listRanking.GetItemCount();

	for (int i = 0; i < 3; i++)
	{
		m_listRanking.InsertColumn(i, list[i], LVCFMT_CENTER, nWidth[i]);
	}

	m_listRanking.SetExtendedStyle(m_listRanking.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	while (nCount < RK.totalRankCnt) {
		strCount.Format(_T("%d"), nCount + 1);
		m_listRanking.InsertItem(nCount, strCount);
		m_listRanking.SetItem(nCount, 1, LVIF_TEXT, RK.GetTotalName(nCount), 0, 0, 0, 0);
		m_listRanking.SetItem(nCount, 2, LVIF_TEXT, RK.GetTotalRank(nCount), 0, 0, 0, 0);
		nCount = m_listRanking.GetItemCount();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
