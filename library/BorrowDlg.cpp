// BorrowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "library.h"
#include "BorrowDlg.h"
#include "afxdialogex.h"

#include "QueryDlg.h"


// BorrowDlg 对话框

IMPLEMENT_DYNAMIC(BorrowDlg, CDialog)

BorrowDlg::BorrowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BORROW_BOOK, pParent)
	, m_bookNum(_T(""))
	, m_cardNum(_T(""))
{

}

BorrowDlg::~BorrowDlg()
{
}

void BorrowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOOKNUM1, m_bookNum);
	DDX_Text(pDX, IDC_CARDNUM1, m_cardNum);
	DDX_Control(pDX, IDC_LIST_DETAIL2, m_listDetail);
	DDX_Control(pDX, IDC_LIST_RESULT2, m_listResult);
}


BEGIN_MESSAGE_MAP(BorrowDlg, CDialog)
	ON_BN_CLICKED(IDC_HAVE_BORROWED1, &BorrowDlg::OnClickedHaveBorrowed1)
	ON_LBN_SELCHANGE(IDC_LIST_RESULT2, &BorrowDlg::OnSelchangeListResult2)
	ON_BN_CLICKED(IDOK, &BorrowDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// BorrowDlg 消息处理程序

// query books borrowed by the card
void BorrowDlg::OnClickedHaveBorrowed1()
{
	UpdateData();
	m_listResult.ResetContent();
	m_listDetail.ResetContent();

	// identify the card number
	if (m_cardSet.IsOpen() == false) {
		m_cardSet.Open();
	}
	m_cardSet.m_strFilter.Format("number = '%s'", m_cardNum);
	m_cardSet.Requery();
	if (m_cardSet.IsEOF()) {
		AfxMessageBox("卡号不存在");
		return;
	}

	// query
	if (m_borrowSet.IsOpen() == false) {
		m_borrowSet.Open();
	}
	// query in borrow relation, get book id
	m_borrowSet.m_strFilter.Format("card = '%s'", m_cardNum);
	m_borrowSet.Requery();
	if (m_borrowSet.IsEOF()) {
		AfxMessageBox("你没有已借的书");
		return;
	}
	if (!m_bookSet.IsOpen()) {
		m_bookSet.Open();
	}
	while (!m_borrowSet.IsEOF()) {
		// query in book relation, get book name
		m_bookSet.m_strFilter.Format("id = '%s'", m_borrowSet.m_id);
		m_bookSet.Requery();
		m_listResult.AddString(m_bookSet.m_name); // print
		m_borrowSet.MoveNext();
	}
	AfxMessageBox("查询完毕");
}


void BorrowDlg::OnSelchangeListResult2()
{
	// titles
	CString  title[9];
	title[0] = "书号：		";
	title[1] = "类别：		";
	title[2] = "书名：		";
	title[3] = "出版社：		";
	title[4] = "年份：		";
	title[5] = "作者：		";
	title[6] = "价格：		";
	title[7] = "藏书总量：	";
	title[8] = "库存：		";

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


void BorrowDlg::OnBnClickedOk()
{
	UpdateData();
	if (!m_bookSet.IsOpen()) {
		m_bookSet.Open();
	}
	m_bookSet.m_strFilter.Format("id='%s'", m_bookNum);
	m_bookSet.Requery();
	if (m_bookSet.IsEOF()) {
		AfxMessageBox("该书不存在");
		return;
	}
	if (m_bookSet.m_stock == 0) {
		// 输出最近的还书时间
		if (m_borrowSet.IsOpen() == false) {
			m_borrowSet.Open();
		}
		// m_borrowSet.m_strFilter.Format("id = '%s' order by return_date asc", m_bookSet.m_id);
		m_borrowSet.m_strFilter.Format("id = '%s' order by return_date asc", m_bookSet.m_id);
		AfxMessageBox(m_borrowSet.m_strFilter);
		m_borrowSet.Requery();
		AfxMessageBox("库存为零\n最近的还书时间:2017-05-01");
		return;
	}
	else {
		//将book表中的藏书总量－1
		m_bookSet.Edit();
		m_bookSet.m_stock--;
		m_bookSet.Update();

		//在borrow表中增加一条借书记录
		CTimeSpan span(30, 0, 0, 0);//30天的时间间隔
		CTime nextMonth = CTime::GetCurrentTime() + span;//30天后的日期
		if (!m_borrowSet.IsOpen()) {
			m_borrowSet.Open();
		}
		m_borrowSet.AddNew();
		m_borrowSet.m_id = m_bookNum;
		m_borrowSet.m_card = m_cardNum;
		m_borrowSet.m_borrow_date = CTime::GetCurrentTime().Format("%Y-%m-%d");
		m_borrowSet.m_return_date = nextMonth.Format("%Y-%m-%d");
		m_borrowSet.m_admin = "3150104890";
		m_borrowSet.Update();
		m_borrowSet.Requery();
		AfxMessageBox("借书成功");
	}
}
