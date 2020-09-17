// HelpDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "HelpDialog.h"
#include "afxdialogex.h"
#include "resource.h"


// CHelpDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_HELP, m_tabSelection);
	//  DDX_Control(pDX, IDC_BUTTON_EXITHELP, m_btn);
	DDX_Control(pDX, IDC_BUTTON_EXITHELP, m_btn);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_HELP, &CHelpDialog::OnSelchangeTabHelp)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_EXITHELP, &CHelpDialog::OnBnClickedButtonExithelp)
END_MESSAGE_MAP()


// CHelpDialog 메시지 처리기입니다.


void CHelpDialog::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CHelpDialog::UpdateDrawing()
{
	CRect rectView;
	GetDlgItem(IDC_STATIC_VIEW)->GetWindowRect(&rectView);
	ScreenToClient(&rectView);
	rectView.DeflateRect(1, 1, 1, 1);
}


BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_btn.LoadBitmaps(IDB_BITMAP_XBUTTON, IDB_BITMAP_XBUTTON, IDB_BITMAP_XBUTTON, IDB_BITMAP_XBUTTON);
	m_btn.SizeToContent();
	LONG ExtendedStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, ExtendedStyle | WS_EX_LAYERED);

	BYTE byAlphaValue = 200;
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, byAlphaValue, LWA_ALPHA);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_tabSelection.DeleteAllItems();
	m_tabSelection.InsertItem(0, _T("게임설명"));
	m_tabSelection.InsertItem(1, _T("단축키"));

	GetDlgItem(IDC_TAB_HELP)->GetFont()->GetLogFont(&m_tabLogFont);
	m_tabLogFont.lfWeight = 800;
	m_tabLogFont.lfHeight = 20;
	m_tabFont.CreateFontIndirect(&m_tabLogFont);
	GetDlgItem(IDC_TAB_HELP)->SetFont(&m_tabFont);

	CRect rect;
	m_dlgHelpGame.Create(IDD_DIALOG_HELPGAME, &m_tabSelection);
	m_dlgHelpGame.GetWindowRect(&rect);
	m_dlgHelpGame.MoveWindow(5, 25, rect.Width(), rect.Height());
	m_dlgHelpGame.ShowWindow(SW_SHOW);

	m_dlgHelpAcc.Create(IDD_DIALOG_ACC, &m_tabSelection);
	m_dlgHelpAcc.GetWindowRect(&rect);
	m_dlgHelpAcc.MoveWindow(5, 25, rect.Width(), rect.Height());
	m_dlgHelpAcc.ShowWindow(SW_HIDE);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHelpDialog::OnSelchangeTabHelp(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelection = m_tabSelection.GetCurSel();

	switch(nSelection)
	{
		case 0 :
			m_dlgHelpGame.ShowWindow(SW_SHOW);
			m_dlgHelpAcc.ShowWindow(SW_HIDE);
			break;
		case 1:
			m_dlgHelpGame.ShowWindow(SW_HIDE);
			m_dlgHelpAcc.ShowWindow(SW_SHOW);
			break;
	}
	*pResult = 0;
}


BOOL CHelpDialog::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
	GetClientRect(rt);
	pDC->FillSolidRect(rt, RGB(0, 0, 0));
	return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}



void CHelpDialog::OnBnClickedButtonExithelp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bClose = TRUE;
	EndDialog(IDOK);
	
}


BOOL CHelpDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
