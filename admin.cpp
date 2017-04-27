// admin.h : Cadmin 类的实现



// Cadmin 实现

// 代码生成在 2017年4月22日, 13:59

#include "stdafx.h"
#include "admin.h"
IMPLEMENT_DYNAMIC(Cadmin, CRecordset)

Cadmin::Cadmin(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = "";
	m_password = "";
	m_name = "";
	m_contact = "";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
// #error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cadmin::GetDefaultConnect()
{
	return _T("DSN=lab1;Description=used in 1st project;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-U0B9IKV;DATABASE=library");
}

CString Cadmin::GetDefaultSQL()
{
	return _T("[dbo].[admin]");
}

void Cadmin::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[password]"), m_password);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[contact]"), m_contact);

}
/////////////////////////////////////////////////////////////////////////////
// Cadmin 诊断

#ifdef _DEBUG
void Cadmin::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cadmin::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


