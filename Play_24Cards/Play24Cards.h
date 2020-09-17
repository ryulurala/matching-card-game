#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPlay24Cards 대화 상자입니다.

#define MAX_CARD_COUNT 13
#define REAL_CARD_COUNT 12

class AFX_EXT_CLASS CPlay24Cards : public CDialogEx
{
	DECLARE_DYNAMIC(CPlay24Cards)
private:
	CImage m_CardImage[MAX_CARD_COUNT];
	char m_CardTable[REAL_CARD_COUNT * 2];
	char m_Flag = 1;
	char m_FirstSelectIndex = -1, m_SecondSelectIndex = -1;

public:
	CPlay24Cards(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPlay24Cards();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_24CARDS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	int m_nTimer;
	CProgressCtrl m_prgsTimer;
	afx_msg void OnClickedButtonHint();
	afx_msg void OnClickedButtonInput();
	afx_msg void OnClickedButtonHelp();
	CString m_strEditHint;
	CEdit m_focusHint;
	CString m_str;
	char inputNum;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_staticTimer;
	CBitmap m_btmHint;
	bool m_nCheck;
};
