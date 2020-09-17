// ChoiceMode.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ChoiceMode.h"
#include "afxdialogex.h"
#include "Play16Cards.h"
#include "Play24Cards.h"
#include "Play32Cards.h"
#include "Play48Cards.h"
#include "IDManager.h"
#include "Ranking.h"
#include "resource.h"

// CChoiceMode 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChoiceMode, CDialogEx)

CChoiceMode::CChoiceMode(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHOICEMODE_DIALOG, pParent)
	, m_Option(0)
	, m_cbCheckP1(-1)
{
}

CChoiceMode::~CChoiceMode()
{
	for (int i = 0; i < IDCnt; i++) {
		ID[i].m_RankCnt = 0;
	}
	IDCnt = 0;
}

void CChoiceMode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_P1, m_cbP1);
	DDX_Control(pDX, IDC_BUTTON_EXIT2, m_btn);
	DDX_Control(pDX, IDC_BUTTON_1P, m_btnP1);
	DDX_Control(pDX, IDC_BUTTON_IDMANAGER, m_btnIDManager);
	DDX_Control(pDX, IDC_BUTTON_RANK, m_btnRank);
}


BEGIN_MESSAGE_MAP(CChoiceMode, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EXIT2, &CChoiceMode::OnClickedButtonExit2)
	ON_BN_CLICKED(IDC_RADIO_OPTION1, &CChoiceMode::OnBnClickedRadioOption1)
	ON_BN_CLICKED(IDC_RADIO_OPTION2, &CChoiceMode::OnBnClickedRadioOption2)
	ON_BN_CLICKED(IDC_RADIO_OPTION3, &CChoiceMode::OnBnClickedRadioOption3)
	ON_BN_CLICKED(IDC_BUTTON_1P, &CChoiceMode::OnClickedButton1p)
	ON_BN_CLICKED(IDC_BUTTON_IDMANAGER, &CChoiceMode::OnClickedButtonIdmanager)
	ON_CBN_SELCHANGE(IDC_COMBO_P1, &CChoiceMode::OnSelchangeComboP1)
	ON_BN_CLICKED(IDC_RADIO_OPTION4, &CChoiceMode::OnBnClickedRadioOption4)
	ON_BN_CLICKED(IDC_BUTTON_RANK, &CChoiceMode::OnClickedButtonRank)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChoiceMode 메시지 처리기입니다.


void CChoiceMode::OnClickedButtonExit2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IDCnt > 0 && (AfxMessageBox(_T("ID와 점수를 저장하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES))
	{
		SaveTxt();
		AfxMessageBox(_T("저장하기 성공!"), MB_ICONINFORMATION);
	}
	EndDialog(IDOK);
}

void CChoiceMode::OnBnClickedRadioOption1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Option = 1;
}


void CChoiceMode::OnBnClickedRadioOption2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Option = 2;
}


void CChoiceMode::OnBnClickedRadioOption3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Option = 3;
}

void CChoiceMode::OnBnClickedRadioOption4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Option = 4;
}

void CChoiceMode::OnClickedButton1p()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_Option != 0 && m_cbCheckP1 != -1) {
		CPlay16Cards Play16Cards;
		CPlay24Cards Play24Cards;
		CPlay32Cards Play32Cards;
		CPlay48Cards Play48Cards;
		if (m_cbCheckP1 != 0) {
			switch (m_Option)
			{
			case 1:
				Play16Cards.DoModal();
				if (Play16Cards.m_nTimer != -1) {
					ID[m_cbCheckP1 - 1].SetGameRank((180 - Play16Cards.m_nTimer) * 40);
				}
				break;
			case 2:
				Play24Cards.DoModal();
				if (Play24Cards.m_nTimer != -1) {
					ID[m_cbCheckP1 - 1].SetGameRank((180 - Play24Cards.m_nTimer) * 90);
				}
				break;
			case 3:
				Play32Cards.DoModal();
				if (Play32Cards.m_nTimer != -1) {
					ID[m_cbCheckP1 - 1].SetGameRank((180 - Play32Cards.m_nTimer) * 120);
				}
				break;
			case 4:
				Play48Cards.DoModal();
				if (Play48Cards.m_nTimer != -1) {
					ID[m_cbCheckP1 - 1].SetGameRank((180 - Play48Cards.m_nTimer) * 180);
				}
				break;
			}
		}
		else {
			switch (m_Option)
			{
			case 1:
				Play16Cards.DoModal();
				break;
			case 2:
				Play24Cards.DoModal();
				break;
			case 3:
				Play32Cards.DoModal();
				break;
			case 4:
				Play48Cards.DoModal();
				break;
			}
		}
	}
	else if (m_Option == 0) {
		AfxMessageBox(_T("옵션을 선택하세요!"), MB_OK | MB_ICONWARNING);
	}
	else {
		AfxMessageBox(_T("Player를 선택하세요."), MB_ICONWARNING);
	}
}


void CChoiceMode::OnClickedButtonIdmanager()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CIDManager IDManager;
	IDManager.DoModal();
	UpdateComboBox();
}


void CChoiceMode::UpdateComboBox()
{
	m_cbP1.ResetContent();
	m_cbP1.AddString(_T("(None)"));
	for (int i = 0; i < IDCnt; i++) {
		m_cbP1.AddString(ID[i].GetUserID());
	}
}


BOOL CChoiceMode::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_btn.LoadBitmaps(IDB_BITMAP_XBUTTON, IDB_BITMAP_XBUTTON, IDB_BITMAP_XBUTTON, IDB_BITMAP_XBUTTON);
	m_btn.SizeToContent();
	m_btnP1.EnableWindowsTheming(FALSE);
	m_btnP1.SetFaceColor(RGB(245, 175, 28), true);
	m_btnIDManager.EnableWindowsTheming(FALSE);
	m_btnIDManager.SetFaceColor(RGB(245, 175, 28), true);
	m_btnRank.EnableWindowsTheming(FALSE);
	m_btnRank.SetFaceColor(RGB(245, 175, 28), true);
	SetWindowTheme(GetDlgItem(IDC_RADIO_OPTION1)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_RADIO_OPTION2)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_RADIO_OPTION3)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_RADIO_OPTION4)->m_hWnd, _T(""), _T(""));
	SetWindowTheme(GetDlgItem(IDC_STATIC)->m_hWnd, _T(""), _T(""));
	UpdateComboBox();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CChoiceMode::OnSelchangeComboP1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cbCheckP1 = m_cbP1.GetCurSel();
}


void CChoiceMode::SaveTxt()
{
	FILE *get_file = NULL;
	get_file = fopen("..\\Data\\DataID.txt", "w");

	char id[50];
	int rankTemp[5];

	for (int i = 0; i < IDCnt; i++) {
		fprintf(get_file, "%s\t\t\t%d\t\t\t", (CStringA)ID[i].GetUserID(), ID[i].m_RankCnt);
		for (int j = 0; j < ID[i].m_RankCnt; j++) {
			fprintf(get_file, "%d, ", ID[i].GetUserRank(j));
		}
		fprintf(get_file, "\n", NULL);
	}
	fclose(get_file);
}


void CChoiceMode::OnClickedButtonRank()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRanking Ranking;
	RK.SetTotalRank(ID, IDCnt);
	Ranking.DoModal();
}


void CChoiceMode::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	CRect rect;
	GetClientRect(&rect);

	int cx = rect.Width();
	int cy = rect.Height();

	CBitmap resBack;
	CBitmap *old_resBack;
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	resBack.LoadBitmap(IDB_BITMAP_BACKGROUND);
	old_resBack = memDC.SelectObject(&resBack);

	dc.BitBlt(0, 0, cx, cy, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(old_resBack);
	resBack.DeleteObject();
	memDC.DeleteDC();
}


HBRUSH CChoiceMode::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	UINT nID = pWnd->GetDlgCtrlID();
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		pDC->SetBkMode(TRANSPARENT);      // 배경투명
		pDC->SetBkColor(RGB(245, 175, 28));  // 배경 색
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	case CTLCOLOR_BTN:
		pDC->SetBkMode(TRANSPARENT);      // 배경투명
		pDC->SetBkColor(RGB(245, 175, 28));  // 배경 색
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL CChoiceMode::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
