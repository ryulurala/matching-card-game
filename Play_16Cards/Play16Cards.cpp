// Play16Cards.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Play16Cards.h"
#include "afxdialogex.h"
#include "resource.h"
#include "HelpDialog.h"

#include <stdlib.h>
#include <time.h>
// CPlay16Cards 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPlay16Cards, CDialogEx)

CPlay16Cards::CPlay16Cards(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_16CARDS, pParent)
	, m_nTimer(0)
	, m_strEditHint(_T(""))
	, m_str(_T(""))
	, inputNum(0)
	, m_nCheck(FALSE)
{
}

CPlay16Cards::~CPlay16Cards()
{
}

void CPlay16Cards::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_TIMER, m_prgsTimer);
	DDX_Text(pDX, IDC_EDIT_HINT, m_strEditHint);
	DDX_Control(pDX, IDC_EDIT_HINT, m_focusHint);
	DDX_Control(pDX, IDC_STATIC_TIMER, m_staticTimer);
	DDX_Control(pDX, IDC_FOCUS, m_staticSize);
	DDX_Control(pDX, IDC_BUTTON_INPUT, m_focusInput);
}


BEGIN_MESSAGE_MAP(CPlay16Cards, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CPlay16Cards::OnClickedBUTTON_HELP)
	ON_BN_CLICKED(IDC_BUTTON_HINT, &CPlay16Cards::OnClickedButtonHint)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CPlay16Cards::OnClickedButtonInput)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPlay16Cards 메시지 처리기입니다.


BOOL CPlay16Cards::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	int dialog = 0;
	CHelpDialog CHelpDialog;
	CHelpDialog.DoModal();
	if (CHelpDialog.m_bClose == TRUE) {
		dialog = 1;
	}
	if (dialog == 1) {
		CString str;
		MoveWindow(0, 0, 800, 800);
		m_prgsTimer.SetRange(0, 40);
		m_prgsTimer.SetPos(40);
		str.Format(_T("%d"), m_prgsTimer.GetPos());
		SetWindowTheme(GetDlgItem(IDC_STATIC_1)->m_hWnd, _T(""), _T(""));
		SetWindowTheme(GetDlgItem(IDC_STATIC_2)->m_hWnd, _T(""), _T(""));
		SetWindowTheme(GetDlgItem(IDC_STATIC_TIMER)->m_hWnd, _T(""), _T(""));
		m_staticTimer.SetWindowTextW(str);
		m_btmHint.LoadBitmap(IDB_BITMAP1);
		for (int i = 0; i < MAX_CARD_COUNT; i++) {
			str.Format(L"..\\character\\%03d.bmp", i);
			m_CardImage[i].Load(str);
		}
		for (int i = 0; i < REAL_CARD_COUNT; i++) {
			m_CardTable[i] = i;
			m_CardTable[8 + i] = i;
		}

		srand((unsigned)time(NULL));
		char first_index, second_index, temp;

		for (int i = 0; i < 500; i++) {
			first_index = rand() % (REAL_CARD_COUNT * 2);
			second_index = rand() % (REAL_CARD_COUNT * 2);
			temp = m_CardTable[first_index];
			m_CardTable[first_index] = m_CardTable[second_index];
			m_CardTable[second_index] = temp;
		}
		((CButton*)GetDlgItem(IDC_BUTTON_HINT))->EnableWindow(FALSE);
		SetTimer(1, 3000, NULL);
		return TRUE;  // return TRUE unless you set the focus to a control
	}
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CPlay16Cards::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.	
	int index, i;
	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

	CRect rect;
	GetClientRect(&rect);

	int cx = rect.Width();
	int cy = rect.Height();
	int m_nCount = -1;

	CBitmap resBack;
	CBitmap *old_resBack;
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	resBack.LoadBitmap(IDB_BITMAP_BKG);
	old_resBack = memDC.SelectObject(&resBack);

	dc.BitBlt(0, 0, cx, cy, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(old_resBack);
	memDC.SelectObject(&m_btmHint);//
	dc.BitBlt(0, 0, 560, 640, &memDC, 0, 0, SRCCOPY);//
	resBack.DeleteObject();
	memDC.DeleteDC();


	if (m_Flag == 1) {
		for (i = 0; i < REAL_CARD_COUNT * 2; i++) {
			if (m_CardTable[i] != -1) {
				index = m_CardTable[i] + 1;
				m_CardImage[index].Draw(dc, (i % 4) * 140, (i / 4) * 160);
			}
		}
	}
	else {
		m_nCount = 0;
		for (i = 0; i < REAL_CARD_COUNT * 2; i++) {
			if (m_CardTable[i] != -1) {
				m_CardImage[0].Draw(dc, (i % 4) * 140, (i / 4) * 160);
				m_nCount++;
			}
		}
	}

	if (m_nCount == 0 && m_nCheck == FALSE) {
		m_nCheck = TRUE;
		KillTimer(2);
		m_nTimer = 40 - (m_prgsTimer.GetPos());
		CString msg;
		msg.Format(_T("%d 점\n%d 초"), (180 - m_nTimer) * 40, m_nTimer);
		AfxMessageBox(msg, MB_ICONINFORMATION);
		EndDialog(IDOK);
	}
}


void CPlay16Cards::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1) {
		KillTimer(1);
		m_Flag = 0;
		Invalidate();
		SetTimer(2, 1000, NULL);
	}
	else if (nIDEvent == 2)
	{
		CString str;
		int pos = m_prgsTimer.GetPos();
		if (pos > 0)
		{
			CRect rect;
			pos--;
			m_prgsTimer.SetPos(pos);
			str.Format(_T("%d"), m_prgsTimer.GetPos());   
			GetDlgItem(IDC_STATIC_TIMER)->GetWindowRect(&rect);
			ScreenToClient(rect);
			InvalidateRect(rect);
			m_staticTimer.SetWindowTextW(str);
		}
		else
		{
			KillTimer(2);
			AfxMessageBox(_T("Game Over"));
			m_Flag = 3;
			m_nTimer = 180;
			EndDialog(IDOK);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CPlay16Cards::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (GetFocus() == (CButton*)GetDlgItem(IDC_EDIT_HINT))
	{
		((CButton*)GetDlgItem(IDC_FOCUS))->SetFocus();
	}

	if (m_Flag == 3 || m_Flag == 2 || m_Flag == 1) { return; }

	if (point.x >= 0 && point.y >= 0 && point.x <= 4 * 140 && point.y <= 4 * 160) {
		int x = point.x / 140;
		int y = point.y / 160;
		int selectIndex = y * 4 + x;

		int cardIndex = m_CardTable[selectIndex];

		CClientDC dc(this);
		if (cardIndex == -1)
			return;

		if (m_FirstSelectIndex == -1) {
			m_FirstSelectIndex = selectIndex;
			m_CardImage[cardIndex + 1].Draw(dc, x * 140, y * 160);
		}
		else {
			if (selectIndex != m_FirstSelectIndex) {
				m_SecondSelectIndex = selectIndex;

				m_CardImage[cardIndex + 1].Draw(dc, x * 140, y * 160);

				if (m_CardTable[m_FirstSelectIndex] == m_CardTable[m_SecondSelectIndex]) {
					m_CardTable[m_FirstSelectIndex] = -1;
					m_CardTable[m_SecondSelectIndex] = -1;
					m_FirstSelectIndex = -1;
					m_SecondSelectIndex = -1;

				}
				else {
					m_FirstSelectIndex = -1;
					m_SecondSelectIndex = -1;
				}
				m_Flag = 2;
				SetTimer(1, 500, NULL);
			}
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPlay16Cards::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nID == SC_CLOSE) {
		if ((AfxMessageBox(_T("강제종료하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES))
		{
			m_nTimer = -1;
			EndDialog(IDOK);
		}
		else {
			return;
		}
	}
	CDialogEx::OnSysCommand(nID, lParam);
}

void CPlay16Cards::OnClickedBUTTON_HELP()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CHelpDialog CHelpDialog;
	CHelpDialog.DoModal();
}


void CPlay16Cards::OnClickedButtonHint()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetTimer(1, 1500, NULL);
	m_Flag = 1;
	Invalidate();
	((CButton*)GetDlgItem(IDC_BUTTON_HINT))->EnableWindow(FALSE);
}

void CPlay16Cards::OnClickedButtonInput()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString strAns;
	strAns = "제이지";
	CString strHint;
	GetDlgItemText(IDC_EDIT_HINT, strHint);
	if (strAns == strHint)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_HINT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_EDIT_HINT))->EnableWindow(FALSE);
	}
	else
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_HINT);
		pEdit->GetWindowTextW(m_strEditHint);
		pEdit->SetWindowTextW(_T(""));
		GetDlgItem(IDC_EDIT_HINT)->SetFocus();
	}
}

HBRUSH CPlay16Cards::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	UINT nID = pWnd->GetDlgCtrlID();
	
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}

BOOL CPlay16Cards::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CHelpDialog CHelpDialog;
	CString string_x, string_y;
	int x, y;

	if (pMsg->message != WM_KEYDOWN) {
		return FALSE;
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F1)
	{
		CHelpDialog.DoModal();
		return TRUE;
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == m_focusHint)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			GetDlgItem(IDC_BUTTON_INPUT)->SetFocus();
			OnClickedButtonInput();
		}
		else {
			return FALSE;
		}
	}
	
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		return TRUE;
	}


	if (pMsg->message == WM_KEYDOWN && m_Flag != 1 && m_Flag != 2 && m_Flag != 3
		&& pMsg->wParam != VK_RETURN && pMsg->wParam != VK_ESCAPE)
	{
		switch (pMsg->wParam)
		{
		case 0x31:
			inputNum = '1';
			break;
		case 0x32:
			inputNum = '2';
			break;
		case 0x33:
			inputNum = '3';
			break;
		case 0x34:
			inputNum = '4';
			break;
		default:
			m_str.Empty();
			AfxMessageBox(_T("다시 입력하세요"));
			return TRUE;
		}
		m_str += (WCHAR)inputNum;

		if (m_str.GetLength() == 2)
		{
			string_x = m_str.GetAt(1);
			string_y = m_str.GetAt(0);


			x = _ttoi(string_x) - 1;
			y = _ttoi(string_y) - 1;
			m_str.Empty();

			int selectIndex = y * 4 + x;

			int cardIndex = m_CardTable[selectIndex];

			CClientDC dc(this);
			if (cardIndex == -1)
				return TRUE;
			if (m_FirstSelectIndex == -1)
			{
				m_FirstSelectIndex = selectIndex;
				m_CardImage[cardIndex + 1].Draw(dc, x * 140, y * 160);
			}
			else
			{
				if (selectIndex != m_FirstSelectIndex)
				{
					m_SecondSelectIndex = selectIndex;

					m_CardImage[cardIndex + 1].Draw(dc, x * 140, y * 160);

					if (m_CardTable[m_FirstSelectIndex] == m_CardTable[m_SecondSelectIndex]) {
						m_CardTable[m_FirstSelectIndex] = -1;
						m_CardTable[m_SecondSelectIndex] = -1;
						m_FirstSelectIndex = -1;
						m_SecondSelectIndex = -1;
					}
					else
					{
						m_FirstSelectIndex = -1;
						m_SecondSelectIndex = -1;
					}
					m_Flag = 2;
					SetTimer(1, 500, NULL);
				}
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

