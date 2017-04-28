// book.h : Cbook 类的实现



// Cbook 实现

// 代码生成在 2017年4月22日, 22:04

#include "stdafx.h"
#include "book.h"
IMPLEMENT_DYNAMIC(Cbook, CRecordset)

Cbook::Cbook(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = "";
	m_category = "";
	m_name = "";
	m_press = "";
	m_year = 0;
	m_author = "";
	m_price = 0.0;
	m_total = 0;
	m_stock = 0;
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
// #error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cbook::GetDefaultConnect()
{
	return _T("DSN=lab1;Description=used in 1st project;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-U0B9IKV;DATABASE=library");
}

CString Cbook::GetDefaultSQL()
{
	return _T("[dbo].[book]");
}

void Cbook::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[category]"), m_category);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[press]"), m_press);
	RFX_Long(pFX, _T("[year]"), m_year);
	RFX_Text(pFX, _T("[author]"), m_author);
	RFX_Single(pFX, _T("[price]"), m_price);
	RFX_Long(pFX, _T("[total]"), m_total);
	RFX_Long(pFX, _T("[stock]"), m_stock);

}
/////////////////////////////////////////////////////////////////////////////
// Cbook 诊断

#ifdef _DEBUG
void Cbook::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cbook::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


