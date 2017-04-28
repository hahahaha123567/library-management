#pragma once
#include "afxwin.h"

#include "borrow.h"
#include "book.h"
#include "card.h"


// BorrowDlg 对话框

class BorrowDlg : public CDialog
{
	DECLARE_DYNAMIC(BorrowDlg)

public:
	BorrowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BorrowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BORROW_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Cbook m_bookSet;
	Cborrow m_borrowSet;
	Ccard m_cardSet;

	CString m_bookNum;
	CString m_cardNum;

	CListBox m_listDetail;
	CListBox m_listResult;
	afx_msg void OnClickedHaveBorrowed1();
	afx_msg void OnSelchangeListResult2();
	afx_msg void OnBnClickedOk();
};
