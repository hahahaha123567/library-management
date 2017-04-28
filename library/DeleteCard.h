#pragma once

#include "card.h"

// DeleteCard 对话框

class DeleteCard : public CDialog
{
	DECLARE_DYNAMIC(DeleteCard)

public:
	DeleteCard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DeleteCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_CARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Ccard m_cardSet;
	CString m_cardNum;
	afx_msg void OnBnClickedOk();
};
