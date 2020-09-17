// Play32Cards.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Play32Cards.h"
#include "afxdialogex.h"
#include "resource.h"
#include "HelpDialog.h"

#include <stdlib.h>
#include <time.h>

// CPlay32Cards 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPlay32Cards, CDialogEx)

CPlay32Cards::CPlay32Cards(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_32CARDS, pParent)
	, m_strEditHint(_T(""))
	, m_nTimer(0)
	, m_Flag(1)
	, m_nCheck(FALSE)
{
}

CPlay32Cards::~CPlay32Cards()
{
}

void CPlay32Cards::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT_TIME, m_editTimer);
	DDX_Control(pDX, IDC_PROGRESS_TIMER, m_prgsTimer);
	DDX_Control(pDX, IDC_EDIT_HINT, m_focusHint);
	DDX_Text(pDX, IDC_EDIT_HINT, m_strEditHint);
	DDX_Control(pDX, IDC_STATIC_TIMER, m_staticTimer);
}


BEGIN_MESSAGE_MAP(CPlay32Cards, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CPlay32Cards::OnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_HINT, &CPlay32Cards::OnClickedButtonHint)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CPlay32Cards::OnClickedButtonInput)
	ON_WM_SYSCOMMAND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPlay32Cards 메시지 처리기입니다.


BOOL CPlay32Cards::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	int dialog = 0;
	CHelpDialog CHelpDialog;
	CHelpDialog.DoModal();
	if (CHelpDialog.m_bClose == TRUE)
	{
		dialog = 1;
	}
	if (dialog == 1)
	{
		MoveWindow(0, 0, 1400, 800);
		CString str;
		m_prgsTimer.SetRange(0, 120);
		m_prgsTimer.SetPos(120);
		str.Format(_T("%d"), m_prgsTimer.GetPos());
		SetWindowTheme(GetDlgItem(IDC_STATIC_1)->m_hWnd, _T(""), _T(""));
		SetWindowTheme(GetDlgItem(IDC_STATIC_2)->m_hWnd, _T(""), _T(""));
		SetWindowTheme(GetDlgItem(IDC_STATIC_TIMER)->m_hWnd, _T(""), _T(""));
		m_staticTimer.SetWindowText(str);
		m_btmHint.LoadBitmap(IDB_BITMAP1);
		for (int i = 0; i < MAX_CARD_COUNT; i++)
		{
			str.Format(L"..\\pokemon\\%03d.bmp", i);
			m_CardImage[i].Load(str);
		}
		for (int i = 0; i < REAL_CARD_COUNT; i++)
		{
			m_CardTable[i] = i;
			m_CardTable[16 + i] = i;
		}
		srand((unsigned)time(NULL));
		char first_index, second_index, temp;

		for (int i = 0; i < 500; i++)
		{
			first_index = rand() % (REAL_CARD_COUNT * 2);
			second_index = rand() % (REAL_CARD_COUNT * 2);

			temp = m_CardTable[first_index];
			m_CardTable[first_index] = m_CardTable[second_index];
			m_CardTable[second_index] = temp;
		}
		((CButton*)GetDlgItem(IDC_BUTTON_HINT))->EnableWindow(FALSE);
		SetTimer(1, 3000, NULL);

		return TRUE;  // return TRUE unless you set the focus to a control
					  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
	}
}


void CPlay32Cards::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.

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
	dc.BitBlt(0, 0, 1120, 1280, &memDC, 0, 0, SRCCOPY);//
	resBack.DeleteObject();
	memDC.DeleteDC();

		if (m_Flag == 1) {
			for (i = 0; i < REAL_CARD_COUNT * 2; i++)
			{
				if (m_CardTable[i] != -1)
				{
					index = m_CardTable[i] + 1;
					m_CardImage[index].Draw(dc, (i % 8) * 140, (i / 8) * 160);
				}
			}
		}
		else
		{
			m_nCount = 0;
			for (i = 0; i < REAL_CARD_COUNT * 2; i++)
			{
				if (m_CardTable[i] != -1)
				{
					m_CardImage[0].Draw(dc, (i % 8) * 140, (i / 8) * 160);
					m_nCount++;
				}
			}
		}
		
		if (m_nCount == 0 && m_nCheck==FALSE) {
			m_nCheck = TRUE;
			CString msg;
			KillTimer(2);
			m_nTimer = 120 - (m_prgsTimer.GetPos());
			msg.Format(_T("%d 점\n%d 초"), (180 - m_nTimer) * 120, m_nTimer);
			AfxMessageBox(msg, MB_ICONINFORMATION);
			EndDialog(IDOK);
		}
	}
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.



void CPlay32Cards::OnTimer(UINT_PTR nIDEvent)
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
			m_staticTimer.SetWindowText(str);
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


void CPlay32Cards::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (GetFocus() == (CButton*)GetDlgItem(IDC_EDIT_HINT))
	{
		((CButton*)GetDlgItem(IDC_FOCUS))->SetFocus();
	}

	if (m_Flag == 1 || m_Flag == 2||m_Flag ==3)
		return;
	if (point.x >= 0 && point.y >= 0 && point.x <= 8 * 140 && point.y <= 4 * 160)
	{
		int x = point.x / 140;
		int y = point.y / 160;
		int selectIndex = y * 8 + x;

		int cardIndex = m_CardTable[selectIndex];

		CClientDC dc(this);
		if (cardIndex == -1) return;

		if (m_FirstSelectIndex == -1) {
			m_FirstSelectIndex = selectIndex;
			m_CardImage[cardIndex + 1].Draw(dc, x * 140, y * 160);
		}
		else
		{
			if (selectIndex != m_FirstSelectIndex)
			{
				m_SecondSelectIndex = selectIndex;
				m_CardImage[cardIndex + 1].Draw(dc, x * 140, y * 160);

				if (m_CardTable[m_FirstSelectIndex] == m_CardTable[m_SecondSelectIndex])
				{
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
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CPlay32Cards::OnClickedButtonHelp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CHelpDialog CHelpDialog;
	CHelpDialog.DoModal();
}


void CPlay32Cards::OnClickedButtonHint()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetTimer(1, 4000, NULL);
	m_Flag = 1;
	Invalidate();
	((CButton*)GetDlgItem(IDC_BUTTON_HINT))->EnableWindow(FALSE);
}


void CPlay32Cards::OnClickedButtonInput()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString strAns;
	strAns = "이상해씨";
	CString strHint;
	GetDlgItemText(IDC_EDIT_HINT, strHint);
	if (strAns == strHint)
	{
		((CButton*)GetDlgItem(IDC_BUTTON_HINT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_EDIT_HINT))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_INPUT))->ShowWindow(SW_HIDE);
	}
	else
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_HINT);
		pEdit->GetWindowTextW(m_strEditHint);
		pEdit->SetWindowTextW(_T(""));
		GetDlgItem(IDC_EDIT_HINT)->SetFocus();
	}
}


void CPlay32Cards::OnSysCommand(UINT nID, LPARAM lParam)
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


BOOL CPlay32Cards::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString string_x, string_y;
	int x, y;

	if (pMsg->message != WM_KEYDOWN) {
		return FALSE;
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


	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F1)
	{
		CHelpDialog CHelpDialog;
		CHelpDialog.DoModal();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && m_str.GetLength() == 0 && m_Flag != 1 && m_Flag != 2 && m_Flag != 3
		&& pMsg->wParam != VK_RETURN && pMsg->wParam != VK_ESCAPE)
	{
		switch (pMsg->wParam)
		{
		case 0x31:
			inputNum = '1';
			m_str += (WCHAR)inputNum;
			break;
		case 0x32:
			inputNum = '2';
			m_str += (WCHAR)inputNum;
			break;
		case 0x33:
			inputNum = '3';
			m_str += (WCHAR)inputNum;
			break;
		case 0x34:
			inputNum = '4';
			m_str += (WCHAR)inputNum;
			break;
		default:
			m_str.Empty();
			AfxMessageBox(_T("다시 입력하세요"));
			return TRUE;
		}
	}
	else if (pMsg->message == WM_KEYDOWN && m_str.GetLength() == 1 && m_Flag != 1 && m_Flag != 2 && m_Flag != 3
		&& pMsg->wParam != VK_RETURN && pMsg->wParam != VK_ESCAPE)
	{
		switch (pMsg->wParam)
		{
		case 0x31:
			inputNum = '1';
			m_str += (WCHAR)inputNum;
			break;
		case 0x32:
			inputNum = '2';
			m_str += (WCHAR)inputNum;
			break;
		case 0x33:
			inputNum = '3';
			m_str += (WCHAR)inputNum;
			break;
		case 0x34:
			inputNum = '4';
			m_str += (WCHAR)inputNum;
			break;
		case 0x35:
			inputNum = '5';
			m_str += (WCHAR)inputNum;
			break;
		case 0x36:
			inputNum = '6';
			m_str += (WCHAR)inputNum;
			break;
		case 0x37:
			inputNum = '7';
			m_str += (WCHAR)inputNum;
			break;
		case 0x38:
			inputNum = '8';
			m_str += (WCHAR)inputNum;
			break;
		default:
			m_str.Empty();
			AfxMessageBox(_T("다시 입력하세요"));
			return TRUE;
		}

		if (m_str.GetLength() == 2)
		{
			string_x = m_str.GetAt(1);
			string_y = m_str.GetAt(0);


			x = _ttoi(string_x) - 1;
			y = _ttoi(string_y) - 1;
			m_str.Empty();

			int selectIndex = y * 8 + x;

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


HBRUSH CPlay32Cards::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	UINT nID = pWnd->GetDlgCtrlID();
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hbr;
}


