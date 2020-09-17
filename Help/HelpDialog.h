#pragma once
#include "afxcmn.h"
#include "HelpGame.h"
#include "HelpAcc.h"
#include "afxwin.h"
#include "afxext.h"


// CHelpDialog 대화 상자입니다.

class AFX_EXT_CLASS CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHelpDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_tabSelection;
	CHelpGame m_dlgHelpGame;
	CHelpAcc m_dlgHelpAcc;
	void UpdateDrawing();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabHelp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CFont m_tabFont;
	LOGFONT m_tabLogFont;
	afx_msg void OnBnClickedButtonExithelp();
	CBitmapButton m_btn;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool m_bClose;
};
