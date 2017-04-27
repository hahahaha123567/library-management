// card.h : Ccard 类的实现



// Ccard 实现

// 代码生成在 2017年4月22日, 14:09

#include "stdafx.h"
#include "card.h"
IMPLEMENT_DYNAMIC(Ccard, CRecordset)

Ccard::Ccard(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_number = "";
	m_name = "";
	m_company = "";
	m_category = "";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
// #error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Ccard::GetDefaultConnect()
{
	return _T("DSN=lab1;Description=used in 1st project;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-U0B9IKV;DATABASE=library");
}

CString Ccard::GetDefaultSQL()
{
	return _T("[dbo].[card]");
}

void Ccard::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[number]"), m_number);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[company]"), m_company);
	RFX_Text(pFX, _T("[category]"), m_category);

}
/////////////////////////////////////////////////////////////////////////////
// Ccard 诊断

#ifdef _DEBUG
void Ccard::AssertValid() const
{
	CRecordset::AssertValid();
}

void Ccard::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


