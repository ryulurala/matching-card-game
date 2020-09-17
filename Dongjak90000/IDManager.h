#pragma once
#include "afxwin.h"


// CIDManager 대화 상자입니다.

class CIDManager : public CDialogEx
{
	DECLARE_DYNAMIC(CIDManager)

public:
	CIDManager(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CIDManager();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ID_MANAGER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nSelectedItem;
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonDelete();
	virtual BOOL OnInitDialog();
	CListCtrl m_listMember;
	CString m_strID;
	afx_msg void OnClickListMember(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_focusID;
};
