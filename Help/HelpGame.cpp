// HelpGame.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "HelpGame.h"
#include "afxdialogex.h"
#include "resource.h"


// CHelpGame 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHelpGame, CDialogEx)

CHelpGame::CHelpGame(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HELPGAME, pParent)
{

}

CHelpGame::~CHelpGame()
{
}

void CHelpGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpGame, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CHelpGame 메시지 처리기입니다.


HBRUSH CHelpGame::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)::GetStockObject(NULL_BRUSH);

	return hbr;
}


BOOL CHelpGame::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt;
	GetClientRect(rt);
	pDC->FillSolidRect(rt, RGB(0, 0, 0));
	return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CHelpGame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LONG ExtendedStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, ExtendedStyle | WS_EX_LAYERED);

	BYTE byAlphaValue = 200;
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, byAlphaValue, LWA_ALPHA);
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_STATIC1)->GetFont()->GetLogFont(&m_lgfont1);
	m_lgfont1.lfWeight = 1000;
	m_lgfont1.lfHeight = 20;
	m_font1.CreateFontIndirect(&m_lgfont1);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_font1);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_font1);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_font1);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_font1);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_font1);
	GetDlgItem(IDC_STATIC6)->SetFont(&m_font1);

	GetDlgItem(IDC_STATIC_GAMERULE)->GetFont()->GetLogFont(&m_lgfont2);
	m_lgfont2.lfWeight = 800;
	m_lgfont2.lfHeight = 17;
	m_font2.CreateFontIndirect(&m_lgfont2);
	GetDlgItem(IDC_STATIC_GAMERULE)->SetFont(&m_font2);
	GetDlgItem(IDC_STATIC_HINT)->SetFont(&m_font2);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
