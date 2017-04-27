// ReturnDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "library.h"
#include "ReturnDlg.h"
#include "afxdialogex.h"


// ReturnDlg �Ի���

IMPLEMENT_DYNAMIC(ReturnDlg, CDialog)

ReturnDlg::ReturnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RETURN_BOOK, pParent)
	, m_bookNum(_T(""))
	, m_cardNum(_T(""))
{

}

ReturnDlg::~ReturnDlg()
{
}

void ReturnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOOKNUM2, m_bookNum);
	DDX_Text(pDX, IDC_CARDNUM2, m_cardNum);
	DDX_Control(pDX, IDC_LIST_DETAIL3, m_listDetail);
	DDX_Control(pDX, IDC_LIST_RESULT3, m_listResult);
}


BEGIN_MESSAGE_MAP(ReturnDlg, CDialog)
	ON_BN_CLICKED(IDC_HAVE_BORROWED2, &ReturnDlg::OnBnClickedHaveBorrowed2)
	ON_LBN_SELCHANGE(IDC_LIST_RESULT3, &ReturnDlg::OnSelchangeListResult3)
	ON_BN_CLICKED(IDOK, &ReturnDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ReturnDlg ��Ϣ�������


void ReturnDlg::OnBnClickedHaveBorrowed2()
{
	UpdateData();//���༭�����ݸ��µ���˰󶨵ĳ�Ա������m_strKeyWord��
	m_listResult.ResetContent();//��ս���б�����ݣ�����У�
	m_listDetail.ResetContent();

	// ��鿨���Ƿ���ȷ
	if (m_cardSet.IsOpen() == false) {
		m_cardSet.Open();
	}
	m_cardSet.m_strFilter.Format("number = '%s'", m_cardNum);
	m_cardSet.Requery();
	if (m_cardSet.IsEOF()) {
		AfxMessageBox("���Ų�����");
		return;
	}

	// ��ѯ�ѽ����
	if (m_borrowSet.IsOpen() == false) {
		m_borrowSet.Open();
	}
	if (!m_bookSet.IsOpen()) {
		m_bookSet.Open();
	}
	m_borrowSet.m_strFilter.Format("card = '%s'", m_cardNum);
	m_borrowSet.Requery();
	if (m_borrowSet.IsEOF()) {
		AfxMessageBox("��û���ѽ����");
		return;
	}
	while (!m_borrowSet.IsEOF()) {//��������е�ÿһ�����������ӵ���ѯ����б���	
		CString tempStr;
		tempStr = m_borrowSet.m_id;
		m_bookSet.m_strFilter.Format("id = '%s'", m_borrowSet.m_id);
		m_bookSet.Requery();
		tempStr = m_bookSet.m_name;
		m_listResult.AddString(tempStr);
		m_borrowSet.MoveNext();
	}
	AfxMessageBox("��ѯ���");
}



void ReturnDlg::OnSelchangeListResult3()
{
	// titles
	CString  title[9];
	title[0] = "��ţ�		";
	title[1] = "���		";
	title[2] = "������		";
	title[3] = "�����磺		";
	title[4] = "��ݣ�		";
	title[5] = "���ߣ�		";
	title[6] = "�۸�		";
	title[7] = "����������	";
	title[8] = "��棺		";

	m_listDetail.ResetContent();
	int curSel = m_listResult.GetCurSel(); // get current select item in listbox
	m_bookSet.SetAbsolutePosition(curSel + 1);
	// since the data types are different, I have no better idea to deal with them
	CString tempStr;
	tempStr += title[0];
	tempStr += m_bookSet.m_id;
	m_listDetail.InsertString(0, tempStr);
	tempStr.Empty();
	tempStr += title[1];
	tempStr += m_bookSet.m_category;
	m_listDetail.InsertString(1, tempStr);
	tempStr.Empty();
	tempStr += title[2];
	tempStr += m_bookSet.m_name;
	m_listDetail.InsertString(2, tempStr);
	tempStr.Empty();
	tempStr += title[3];
	tempStr += m_bookSet.m_press;
	m_listDetail.InsertString(3, tempStr);
	tempStr.Empty();
	tempStr += title[4];
	CString year;
	year.Format(_T("%ld"), m_bookSet.m_year);
	tempStr += year;
	m_listDetail.InsertString(4, tempStr);
	tempStr.Empty();
	tempStr += title[5];
	tempStr += m_bookSet.m_author;
	m_listDetail.InsertString(5, tempStr);
	tempStr.Empty();
	tempStr += title[6];
	CString price;
	price.Format(_T("%.2f"), m_bookSet.m_price);
	tempStr += price;
	m_listDetail.InsertString(6, tempStr);
	tempStr.Empty();
	tempStr += title[7];
	CString total;
	total.Format(_T("%ld"), m_bookSet.m_total);
	tempStr += total;
	m_listDetail.InsertString(7, tempStr);
	tempStr.Empty();
	tempStr += title[8];
	CString stock;
	stock.Format(_T("%ld"), m_bookSet.m_stock);
	tempStr += stock;
	m_listDetail.InsertString(8, tempStr);
}


void ReturnDlg::OnBnClickedOk()
{
	UpdateData();
	if (!m_bookSet.IsOpen()) {
		m_bookSet.Open();
	}
	m_bookSet.m_strFilter.Format("id = '%s'", m_bookNum);
	m_bookSet.Requery();
	if (m_bookSet.IsEOF()) {
		AfxMessageBox("���鲻����");
		return;
	}
	if (!m_borrowSet.IsOpen()) {
		m_borrowSet.Open();
	}
	m_borrowSet.m_strFilter.Format("id = '%s' and card = '%s'", m_bookNum, m_cardNum);
	m_borrowSet.Requery();
	if (m_borrowSet.IsEOF()) {
		AfxMessageBox("��û�н��Ȿ��");
		return;
	}
	//��book���еĲ�������+1
	m_bookSet.Edit();
	m_bookSet.m_stock++;
	m_bookSet.Update();

	//��borrow����ɾ�������¼
	m_borrowSet.Delete();
	AfxMessageBox("����ɹ�");
}
