// book.h : Cbook ���ʵ��



// Cbook ʵ��

// ���������� 2017��4��22��, 22:04

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
// #error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
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
// Cbook ���

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


