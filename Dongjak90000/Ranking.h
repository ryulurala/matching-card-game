#pragma once
#include "afxcmn.h"


// CRanking 대화 상자입니다.

class CRanking : public CDialogEx
{
	DECLARE_DYNAMIC(CRanking)

public:
	CRanking(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRanking();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANKING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listRanking;
};
