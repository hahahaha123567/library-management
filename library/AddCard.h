#pragma once

#include "card.h"

// AddCard �Ի���

class AddCard : public CDialog
{
	DECLARE_DYNAMIC(AddCard)

public:
	AddCard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddCard();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_CARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Ccard m_cardSet;

	CString m_infoCardnum;
	CString m_infoCompany;
	CString m_infoCategory;
	CString m_infoName;
	afx_msg void OnBnClickedOk();
};
