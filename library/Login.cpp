// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "library.h"
#include "Login.h"
#include "afxdialogex.h"


// Login 对话框

IMPLEMENT_DYNAMIC(Login, CDialog)

Login::Login(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOGIN, pParent)
	, m_userName(_T(""))
	, m_password(_T(""))
{
}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAME, m_userName);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
}


BEGIN_MESSAGE_MAP(Login, CDialog)
	ON_BN_CLICKED(IDOK, &Login::OnBnClickedOk)
END_MESSAGE_MAP()


// Login 消息处理程序

extern int passwordKey;

void Login::OnBnClickedOk()
{
	UpdateData();
	if (m_adminSet.IsOpen() == false) {
		m_adminSet.Open();
	}
	m_adminSet.m_strFilter.Format("id = '%s'", m_userName);
	m_adminSet.Requery();
	if (m_adminSet.IsEOF() || m_password != m_adminSet.m_password) {
		AfxMessageBox("ID或密码错误");
		return;
	}
	else {
		passwordKey = 1;
		AfxMessageBox("登陆成功");
	}
	CDialog::OnOK();
}
