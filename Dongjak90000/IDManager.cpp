// IDManager.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "IDManager.h"
#include "afxdialogex.h"
#include "resource.h"
#include "UserID.h"

// CIDManager 대화 상자입니다.

IMPLEMENT_DYNAMIC(CIDManager, CDialogEx)

CIDManager::CIDManager(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ID_MANAGER, pParent)
	, m_nSelectedItem(0)
	, m_strID(_T(""))
{

}

CIDManager::~CIDManager()
{
}

void CIDManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMBER, m_listMember);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Control(pDX, IDC_EDIT_ID, m_focusID);
}


BEGIN_MESSAGE_MAP(CIDManager, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CIDManager::OnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CIDManager::OnClickedButtonDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MEMBER, &CIDManager::OnClickListMember)
END_MESSAGE_MAP()


// CIDManager 메시지 처리기입니다.


void CIDManager::OnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nCount = m_listMember.GetItemCount();
	CString strCount;
	
	UpdateData(TRUE);
	if (!m_strID.IsEmpty())
	{
		strCount.Format(_T("%d"), nCount + 1);
		m_listMember.InsertItem(nCount, strCount);
		m_listMember.SetItem(nCount, 1, LVIF_TEXT, m_strID, 0, 0, 0, 0);
		
		//ID에 Input
		ID[IDCnt++].SetUserID(m_strID);

		m_strID.Empty();

		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("항목을 입력해 주세요."), MB_OK | MB_ICONWARNING);
	}
}


void CIDManager::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedItem >= 0)
	{
		m_listMember.DeleteItem(m_nSelectedItem);
		for (int i = m_nSelectedItem - 1; i < m_listMember.GetItemCount(); i++)
		{
			CString strIndex;
			strIndex.Format(_T("%d"), i + 1);
			m_listMember.SetItemText(i, 0, strIndex);

		}
		ID[m_nSelectedItem].SetUserID(_T(""));
		ID[m_nSelectedItem].m_RankCnt = 0;
		for (int i = m_nSelectedItem; i < IDCnt - 1; i++) {
			ID[i].SetUserID(ID[i + 1].GetUserID());
			ID[i].ChangeRank(ID[i + 1]);
		}
		ID[IDCnt - 1].SetUserID(_T(""));
		ID[IDCnt - 1].m_RankCnt;
		IDCnt--;

		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox(_T("삭제할 ID를 선택하세요."), MB_OK | MB_ICONWARNING);
	}
	(GetDlgItem(IDC_EDIT_ID))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
}


BOOL CIDManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	LPWSTR list[2] = { _T("순번"), _T("ID") };
	int nWidth[2] = { 50, 345 };
	CString strCount;
	int nCount = m_listMember.GetItemCount();

	for (int i = 0; i < 2; i++)
	{
		m_listMember.InsertColumn(i, list[i], LVCFMT_CENTER, nWidth[i]);
	}

	m_listMember.SetExtendedStyle(m_listMember.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
	if (IDCnt > 0)
	{
		while (nCount != IDCnt) {
			strCount.Format(_T("%d"), nCount + 1);
			m_listMember.InsertItem(nCount, strCount);
			m_listMember.SetItem(nCount, 1, LVIF_TEXT, ID[nCount].GetUserID(), 0, 0, 0, 0);
			nCount = m_listMember.GetItemCount();
		}
	}
	return TRUE;
}


void CIDManager::OnClickListMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelectedItem = pNMItemActivate->iItem;
	
	(GetDlgItem(IDC_EDIT_ID))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_INSERT))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE);
	*pResult = 0;
}

BOOL CIDManager::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == m_focusID)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			OnClickedButtonInsert();
		}
		else {
			return FALSE;
		}
	}
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN))
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
