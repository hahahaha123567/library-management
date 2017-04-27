// ManyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "library.h"
#include "ManyDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <fstream>

using std::string;


// ManyDlg �Ի���

IMPLEMENT_DYNAMIC(ManyDlg, CDialog)

ManyDlg::ManyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MANY, pParent)
	, m_path(_T(""))
{

}

ManyDlg::~ManyDlg()
{
}

void ManyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATH, m_path);
}


BEGIN_MESSAGE_MAP(ManyDlg, CDialog)
	ON_BN_CLICKED(IDOK, &ManyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ManyDlg ��Ϣ�������


void ManyDlg::OnBnClickedOk()
{
	UpdateData();
	std::ifstream file(m_path);
	if (file.is_open() == false) {
		AfxMessageBox("�ļ��޷���");
		return;
	}
	if (m_bookSet.IsOpen() == false) {
		m_bookSet.Open();
	}
	int count = 0;
	while (file.peek() != EOF) {
		// ����д��ѿո����ȥ
		char buf[255];
		file.getline(buf, 255, ',');
		CString m_id(buf);
		file.getline(buf, 255, ',');
		CString m_category(buf);
		file.getline(buf, 255, ',');
		CString m_name(buf);
		file.getline(buf, 255, ',');
		CString m_press(buf);
		long m_year;
		file >> m_year;
		file.getline(buf, 255, ',');
		file.getline(buf, 255, ',');
		CString m_author(buf);
		float m_price;
		file >> m_price;
		file.getline(buf, 255, ',');
		long m_total;
		file >> m_total;
		//
		m_bookSet.m_strFilter.Format("id = '%s'", m_id);
		m_bookSet.Requery();
		if (m_bookSet.IsEOF() == false) {
			AfxMessageBox("����ʧ�ܣ����ظ�id");
			return;
		}
		//
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
		count++;
	}
	CString temp;
	temp.Format("�������,��%d������");
	AfxMessageBox(temp);
	file.close();
}
