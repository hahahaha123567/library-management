// DeleteCard.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "library.h"
#include "DeleteCard.h"
#include "afxdialogex.h"


// DeleteCard �Ի���

IMPLEMENT_DYNAMIC(DeleteCard, CDialog)

DeleteCard::DeleteCard(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DELETE_CARD, pParent)
	, m_cardNum(_T(""))
{

}

DeleteCard::~DeleteCard()
{
}

void DeleteCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CARDNUMBER, m_cardNum);
}


BEGIN_MESSAGE_MAP(DeleteCard, CDialog)
	ON_BN_CLICKED(IDOK, &DeleteCard::OnBnClickedOk)
END_MESSAGE_MAP()


// DeleteCard ��Ϣ�������


void DeleteCard::OnBnClickedOk()
{
	UpdateData();
	if (m_cardSet.IsOpen() == false) {
		m_cardSet.Open();
	}
	m_cardSet.m_strFilter.Format("number = '%s'", m_cardNum);
	m_cardSet.Requery();
	if (m_cardSet.IsEOF()) {
		AfxMessageBox("���Ų�����");
		return;
	}
	m_cardSet.Delete();
	AfxMessageBox("ɾ���ɹ�");
	CDialog::OnOK();
}
