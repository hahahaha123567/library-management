#pragma once
#include "afxwin.h"

#include "borrow.h"
#include "book.h"
#include "card.h"

// ReturnDlg 对话框

class ReturnDlg : public CDialog
{
	DECLARE_DYNAMIC(ReturnDlg)

public:
	ReturnDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ReturnDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RETURN_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Cbook m_bookSet;
	Cborrow m_borrowSet;
	Ccard m_cardSet;
	// 要还的书号
	CString m_bookNum;
	// 借书卡号
	CString m_cardNum;
	CListBox m_listDetail;
	CListBox m_listResult;
	afx_msg void OnBnClickedHaveBorrowed2();
	afx_msg void OnSelchangeListResult3();
	afx_msg void OnBnClickedOk();
};
