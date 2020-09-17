#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define MAX_CARD_COUNT 17
#define REAL_CARD_COUNT 16

// CPlay32Cards 대화 상자입니다.

class AFX_EXT_CLASS CPlay32Cards : public CDialogEx
{
	DECLARE_DYNAMIC(CPlay32Cards)
private:
	CImage m_CardImage[MAX_CARD_COUNT];
	char m_CardTable[REAL_CARD_COUNT * 2];
	char m_Flag;
	char m_FirstSelectIndex = -1, m_SecondSelectIndex = -1;
public:
	CPlay32Cards(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPlay32Cards();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_32CARDS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CProgressCtrl m_prgsTimer;
	int m_nTimer;
	afx_msg void OnClickedButtonHelp();
	afx_msg void OnClickedButtonHint();
	afx_msg void OnClickedButtonInput();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_focusHint;
	CString m_strEditHint;
	CString m_str;
	char inputNum;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_staticTimer;
	CBitmap m_btmHint;
	bool m_nCheck;
};
