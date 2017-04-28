// AddCard.cpp : 实现文件
//

#include "stdafx.h"
#include "library.h"
#include "AddCard.h"
#include "afxdialogex.h"


// AddCard 对话框

IMPLEMENT_DYNAMIC(AddCard, CDialog)

AddCard::AddCard(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ADD_CARD, pParent)
	, m_infoCardnum(_T(""))
	, m_infoCompany(_T(""))
	, m_infoCategory(_T(""))
	, m_infoName(_T(""))
{

}

AddCard::~AddCard()
{
}

void AddCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INFO_CARDNUM, m_infoCardnum);
	//  DDX_Text(pDX, IDC_INFO_CATEGORY, m_info_category);
	DDX_Text(pDX, IDC_INFO_COMPANY, m_infoCompany);
	DDX_Text(pDX, IDC_INFO_CATEGORY, m_infoCategory);
	DDX_Text(pDX, IDC_INFO_NAME, m_infoName);
}


BEGIN_MESSAGE_MAP(AddCard, CDialog)
	ON_BN_CLICKED(IDOK, &AddCard::OnBnClickedOk)
END_MESSAGE_MAP()


// AddCard 消息处理程序


void AddCard::OnBnClickedOk()
{
	UpdateData();
	CString a(m_infoCardnum), b(m_infoName), c(m_infoCompany), d(m_infoCategory);
	if (a == "" || b == "" || c == "" || d == "") {
		AfxMessageBox("请将信息完整填入");
		return;
	}
	if (m_cardSet.IsOpen() == false) {
		m_cardSet.Open();
	}
	m_cardSet.m_strFilter.Format("number = '%s'", a);
	m_cardSet.Requery();
	if (m_cardSet.IsEOF() == false) {
		AfxMessageBox("该卡号已存在，请重新输入");
		return;
	}
	m_cardSet.AddNew();
	m_cardSet.m_number = a;
	m_cardSet.m_name = b;
	m_cardSet.m_company = c;
	m_cardSet.m_category = d;
	m_cardSet.Update();
	m_cardSet.Requery();
	AfxMessageBox("添加成功");
	CDialog::OnOK();
}
