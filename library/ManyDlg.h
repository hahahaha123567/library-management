#pragma once

#include "book.h"

// ManyDlg 对话框

class ManyDlg : public CDialog
{
	DECLARE_DYNAMIC(ManyDlg)

public:
	ManyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ManyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Cbook m_bookSet;
	CString m_path;
	afx_msg void OnBnClickedOk();
};
