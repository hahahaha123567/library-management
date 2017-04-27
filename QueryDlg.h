#pragma once
#include "book.h"
#include "afxwin.h"

// CQueryDlg 对话框

class CQueryDlg : public CDialog
{
	DECLARE_DYNAMIC(CQueryDlg)

public:
	CQueryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQueryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_condition1;
	CString m_condition2;
	CString m_condition3;
	CString m_condition4;
	CString m_condition5;
	CString m_condition6;
	CString m_AndOr1;
	CString m_AndOr2;
	CString m_AndOr3;
	CString m_AndOr4;
	CString m_AndOr5;
	CString m_keyword1;
	CString m_keyword2;
	CString m_keyword3;
	CString m_keyword4;
	afx_msg void OnBnClickedOk();
	Cbook m_bookSet;
	afx_msg void OnSelchangeListResult();
	CListBox m_listDetail;
	CListBox m_listResult;
	CString m_keyword5;
	CString m_keyword6;
	CString m_keyword7;
	CString m_keyword8;
	CString m_orderItem;
	CString m_orderDir;
};
