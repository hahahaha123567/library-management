#pragma once

#include "book.h"

// ManyDlg �Ի���

class ManyDlg : public CDialog
{
	DECLARE_DYNAMIC(ManyDlg)

public:
	ManyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ManyDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Cbook m_bookSet;
	CString m_path;
	afx_msg void OnBnClickedOk();
};
