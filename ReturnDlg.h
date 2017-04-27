#pragma once
#include "afxwin.h"

#include "borrow.h"
#include "book.h"
#include "card.h"

// ReturnDlg �Ի���

class ReturnDlg : public CDialog
{
	DECLARE_DYNAMIC(ReturnDlg)

public:
	ReturnDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ReturnDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RETURN_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Cbook m_bookSet;
	Cborrow m_borrowSet;
	Ccard m_cardSet;
	// Ҫ�������
	CString m_bookNum;
	// ���鿨��
	CString m_cardNum;
	CListBox m_listDetail;
	CListBox m_listResult;
	afx_msg void OnBnClickedHaveBorrowed2();
	afx_msg void OnSelchangeListResult3();
	afx_msg void OnBnClickedOk();
};
