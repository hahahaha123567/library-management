// card.h : Ccard ���ʵ��



// Ccard ʵ��

// ���������� 2017��4��22��, 14:09

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
// #error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[number]"), m_number);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[company]"), m_company);
	RFX_Text(pFX, _T("[category]"), m_category);

}
/////////////////////////////////////////////////////////////////////////////
// Ccard ���

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


