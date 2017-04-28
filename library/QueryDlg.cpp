// QueryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "library.h"
#include "book.h"
#include "QueryDlg.h"
#include "afxdialogex.h"

// CQueryDlg 对话框

IMPLEMENT_DYNAMIC(CQueryDlg, CDialog)

CQueryDlg::CQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_QUERY, pParent)
	, m_condition1(_T(""))
	, m_condition2(_T(""))
	, m_condition3(_T(""))
	, m_condition4(_T(""))
	, m_condition5(_T(""))
	, m_condition6(_T(""))
	, m_AndOr1(_T(""))
	, m_AndOr2(_T(""))
	, m_AndOr3(_T(""))
	, m_AndOr4(_T(""))
	, m_AndOr5(_T(""))
	, m_keyword1(_T(""))
	, m_keyword2(_T(""))
	, m_keyword3(_T(""))
	, m_keyword4(_T(""))
	, m_keyword5(_T(""))
	, m_keyword6(_T(""))
	, m_keyword7(_T(""))
	, m_keyword8(_T(""))
	, m_orderItem(_T(""))
	, m_orderDir(_T(""))
{
}

CQueryDlg::~CQueryDlg()
{
}

void CQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, ID_CONDITION1, m_condition1);
	DDX_CBString(pDX, ID_CONDITION2, m_condition2);
	DDX_CBString(pDX, ID_CONDITION3, m_condition3);
	DDX_CBString(pDX, ID_CONDITION4, m_condition4);
	DDX_CBString(pDX, IDC_CONDITION5, m_condition5);
	DDX_CBString(pDX, IDC_CONDITION6, m_condition6);
	DDX_CBString(pDX, IDC_AND_OR1, m_AndOr1);
	DDX_CBString(pDX, IDC_AND_OR2, m_AndOr2);
	DDX_CBString(pDX, IDC_AND_OR3, m_AndOr3);
	DDX_CBString(pDX, IDC_AND_OR4, m_AndOr4);
	DDX_CBString(pDX, IDC_AND_OR5, m_AndOr5);
	DDX_Text(pDX, IDC_KEYWORD1, m_keyword1);
	DDX_Text(pDX, IDC_KEYWORD2, m_keyword2);
	DDX_Text(pDX, IDC_KEYWORD3, m_keyword3);
	DDX_Text(pDX, IDC_KEYWORD4, m_keyword4);
	DDX_Control(pDX, IDC_LIST_DETAIL, m_listDetail);
	DDX_Control(pDX, IDC_LIST_RESULT, m_listResult);
	DDX_Text(pDX, IDC_KEYWORD5, m_keyword5);
	DDX_Text(pDX, IDC_KEYWORD6, m_keyword6);
	DDX_Text(pDX, IDC_KEYWORD7, m_keyword7);
	DDX_Text(pDX, IDC_KEYWORD8, m_keyword8);
	DDX_CBString(pDX, IDC_ORDER_ITEM, m_orderItem);
	DDX_CBString(pDX, IDC_ORDER_DIR, m_orderDir);
}


BEGIN_MESSAGE_MAP(CQueryDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CQueryDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST_RESULT, &CQueryDlg::OnSelchangeListResult)
END_MESSAGE_MAP()


// CQueryDlg 消息处理程序

void CQueryDlg::OnBnClickedOk()
{
	// load the input into the corresponding variables
	UpdateData();
	if (!m_bookSet.IsOpen()) {
		m_bookSet.Open();
	}

	// put the value of variables into arrays
	CString * inputCondition[7]; // condition that user choose (in chinese)
	inputCondition[0] = &m_orderItem;
	inputCondition[1] = &m_condition1;
	inputCondition[2] = &m_condition2;
	inputCondition[3] = &m_condition3;
	inputCondition[4] = &m_condition4;
	inputCondition[5] = &m_condition5;
	inputCondition[6] = &m_condition6;
	CString condition[7]; // condition that used in sql query (in english)
	for (int i = 0; i <= 6; i++) {
		if (!inputCondition[i]->Compare(_T("类别"))) {
			condition[i] = "category";
			continue;
		}
		if (!inputCondition[i]->Compare(_T("书名"))) {
			condition[i] = "name";
			continue;
		}
		if (!inputCondition[i]->Compare(_T("出版社"))) {
			condition[i] = "press";
			continue;
		}
		if (!inputCondition[i]->Compare(_T("作者"))) {
			condition[i] = "author";
			continue;
		}
		if (!inputCondition[i]->Compare(_T("年份"))) {
			condition[i] = "year";
			continue;
		}
		if (!inputCondition[i]->Compare(_T("价格"))) {
			condition[i] = "price";
			continue;
		}
		if (!inputCondition[i]->Compare(_T("书号"))) {
			condition[i] = "id";
			continue;
		}
		if (!inputCondition[i]->Compare(_T("年份"))) {
			condition[i] = "year";
			continue;
		}
		if (!inputCondition[i]->Compare(_T("数量"))) {
			condition[i] = "total";
			continue;
		}
	}
	CString * strKey[8]; // key words that user input
	strKey[0] = &m_keyword1;
	strKey[1] = &m_keyword2;
	strKey[2] = &m_keyword3;
	strKey[3] = &m_keyword4;
	strKey[4] = &m_keyword5;
	strKey[5] = &m_keyword6;
	strKey[6] = &m_keyword7;
	strKey[7] = &m_keyword8;
	CString * andOr[5]; // "and" or "or" that user choose
	andOr[0] = &m_AndOr1;
	andOr[1] = &m_AndOr2;
	andOr[2] = &m_AndOr3;
	andOr[3] = &m_AndOr4;
	andOr[4] = &m_AndOr5;

	// compose a query statement
	CString str; // temp str
	CString strFilter; // final str
	for (int i = 1; i <= 6; ++i) {
		if (condition[i] == "") {
			continue;
		}
		// first 4 conditions
		if (i <= 4) {
			str.Format(_T("%s = '%s'"), condition[i], *strKey[i-1]);
		}
		// last 2 conditions
		else if (condition[i] == "year"){
			int temp1 = atoi(*strKey[i*2-6]);
			int temp2 = atoi(*strKey[i*2-5]);
			str.Format(_T("%s > %d and %s < %d"), condition[i], temp1, condition[i], temp2);
		}
		else {
			float temp1 = atof(*strKey[i*2-6]);
			float temp2 = atof(*strKey[i*2-5]);
			str.Format(_T("%s > %f and %s < %f"), condition[i], temp1, condition[i], temp2);
		}
		strFilter += str;
		if (i <= 4 && *andOr[i-1] != "") {
			strFilter += " ";
			strFilter += *andOr[i-1];
			strFilter += " ";
		}
	}
	// customized order
	if (condition[0] != "") {
		strFilter += " order by " + condition[0];
		if (m_orderDir == "升序") {
			strFilter += " asc";
		}
		else {
			strFilter += " desc";
		}
	}
	// default order
	else {
		strFilter += " order by name asc";
	}
	// AfxMessageBox(strFilter); // to dubug

	// query
	m_bookSet.m_strFilter = strFilter;
	m_bookSet.Requery();

	// show answer
	// clear screen
	m_listResult.ResetContent();
	m_listDetail.ResetContent();
	if (m_bookSet.IsEOF()) {
		AfxMessageBox(_T("查无此书"));
		return;
	}
	int i = 0;
	while (m_bookSet.IsEOF() == false) {
		CString tempStr;
		tempStr = m_bookSet.m_name;
		// InsertString vs AddString
		// InsertString: insert in order
		m_listResult.InsertString(i, tempStr);
		m_bookSet.MoveNext();
		i++;
	}
	AfxMessageBox("查询完毕");
}


void CQueryDlg::OnSelchangeListResult()
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
	static CString tempStr;
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

