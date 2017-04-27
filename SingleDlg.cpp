// SingleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "library.h"
#include "SingleDlg.h"
#include "afxdialogex.h"


// SingleDlg 对话框

IMPLEMENT_DYNAMIC(SingleDlg, CDialog)

SingleDlg::SingleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SINGLE, pParent)
	, m_year(0)
	, m_total(0)
	, m_price(0)
	, m_author(_T(""))
	, m_category(_T(""))
	, m_id(_T(""))
	, m_name(_T(""))
	, m_press(_T(""))
{

}

SingleDlg::~SingleDlg()
{
}

void SingleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_YEAR, m_year);
	DDX_Text(pDX, IDC_TOTAL, m_total);
	DDX_Text(pDX, IDC_PRICE, m_price);
	DDX_Text(pDX, IDC_AUTHOR, m_author);
	DDX_Text(pDX, IDC_CATEGORY, m_category);
	DDX_Text(pDX, IDC_ID, m_id);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_PRESS, m_press);
}


BEGIN_MESSAGE_MAP(SingleDlg, CDialog)
	ON_BN_CLICKED(IDOK, &SingleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SingleDlg 消息处理程序


void SingleDlg::OnBnClickedOk()
{
	UpdateData();
	if (m_id == "" || m_category == "" || m_name == "" || m_press == ""
		|| m_year == 0 || m_author == "" || m_price == 0 || m_total == 0) {
		AfxMessageBox("请将信息填写完整");
		return;
	}
	if (m_bookSet.IsOpen() == false) {
		m_bookSet.Open();
	}
	m_bookSet.m_strFilter.Format("id = '%s'", m_id);
	m_bookSet.Requery();
	if (m_bookSet.IsEOF() == false) {
		AfxMessageBox("已存在该书号");
		return;
	}
	m_bookSet.AddNew();
	m_bookSet.m_id = m_id;
	m_bookSet.m_category = m_category;
	m_bookSet.m_name = m_name;
	m_bookSet.m_press = m_press;
	m_bookSet.m_year = m_year;
	m_bookSet.m_author = m_author;
	m_bookSet.m_price = m_price;
	m_bookSet.m_stock = m_total;
	m_bookSet.m_total = m_total;
	m_bookSet.Update();
	m_bookSet.Requery();
	AfxMessageBox("入库成功");
	CDialog::OnOK();
}
