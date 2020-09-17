#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPlay16Cards 대화 상자입니다.

#define MAX_CARD_COUNT 9
#define REAL_CARD_COUNT 8

class AFX_EXT_CLASS CPlay16Cards : public CDialogEx
{
	DECLARE_DYNAMIC(CPlay16Cards)
private:
	CImage m_CardImage[MAX_CARD_COUNT];
	char m_CardTable[REAL_CARD_COUNT * 2];
	char m_Flag = 1;
	char m_FirstSelectIndex = -1, m_SecondSelectIndex = -1;

public:
	CPlay16Cards(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPlay16Cards();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_16CARDS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CProgressCtrl m_prgsTimer;
	int m_nTimer;
	afx_msg void OnClickedBUTTON_HELP();
	afx_msg void OnClickedButtonHint();
	CString m_strEditHint;
	afx_msg void OnClickedButtonInput();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_focusHint;
	CString m_str;
	char inputNum;
	bool m_nCheck;
	CStatic m_staticTimer;
	CStatic m_staticSize;
	CBitmap m_btmHint;
	CButton m_focusInput;
};
