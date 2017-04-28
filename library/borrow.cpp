// borrow.h : Cborrow ���ʵ��



// Cborrow ʵ��

// ���������� 2017��4��22��, 14:08

#include "stdafx.h"
#include "borrow.h"
IMPLEMENT_DYNAMIC(Cborrow, CRecordset)

Cborrow::Cborrow(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_id = "";
	m_card = "";
	m_borrow_date = L"";
	m_return_date = L"";
	m_admin = "";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
// #error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString Cborrow::GetDefaultConnect()
{
	return _T("DSN=lab1;Description=used in 1st project;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-U0B9IKV;DATABASE=library");
}

CString Cborrow::GetDefaultSQL()
{
	return _T("[dbo].[borrow]");
}

void Cborrow::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[card]"), m_card);
	RFX_Text(pFX, _T("[borrow_date]"), m_borrow_date);
	RFX_Text(pFX, _T("[return_date]"), m_return_date);
	RFX_Text(pFX, _T("[admin]"), m_admin);

}
/////////////////////////////////////////////////////////////////////////////
// Cborrow ���

#ifdef _DEBUG
void Cborrow::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cborrow::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


