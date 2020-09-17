
// Dongjak90000Dlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

// CDongjak90000Dlg 대화 상자
class CDongjak90000Dlg : public CDialogEx
{
// 생성입니다.
public:
	CDongjak90000Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DONGJAK90000_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonExit();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnClickedButtonLoad();
	void LoadTxt();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
