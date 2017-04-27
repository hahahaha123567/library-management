#pragma once
#include "book.h"

// SingleDlg 对话框

class SingleDlg : public CDialog
{
	DECLARE_DYNAMIC(SingleDlg)

public:
	SingleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SingleDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SINGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Cbook m_bookSet;

	int m_year;
	int m_total;
	float m_price;
	CString m_author;
	CString m_category;
	CString m_id;
	CString m_name;
	CString m_press;
	afx_msg void OnBnClickedOk();
};
