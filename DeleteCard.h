#pragma once

#include "card.h"

// DeleteCard �Ի���

class DeleteCard : public CDialog
{
	DECLARE_DYNAMIC(DeleteCard)

public:
	DeleteCard(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DeleteCard();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE_CARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Ccard m_cardSet;
	CString m_cardNum;
	afx_msg void OnBnClickedOk();
};
