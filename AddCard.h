#pragma once

#include "card.h"

// AddCard 对话框

class AddCard : public CDialog
{
	DECLARE_DYNAMIC(AddCard)

public:
	AddCard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_CARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Ccard m_cardSet;

	CString m_infoCardnum;
	CString m_infoCompany;
	CString m_infoCategory;
	CString m_infoName;
	afx_msg void OnBnClickedOk();
};
