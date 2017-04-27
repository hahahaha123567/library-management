// admin.h : Cadmin ���ʵ��



// Cadmin ʵ��

// ���������� 2017��4��22��, 13:59

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
// #error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[id]"), m_id);
	RFX_Text(pFX, _T("[password]"), m_password);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[contact]"), m_contact);

}
/////////////////////////////////////////////////////////////////////////////
// Cadmin ���

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


