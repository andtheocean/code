#pragma once
#include "afxwin.h"
#include "MyButton.h"

// CDlgNewMap �Ի���

class CDlgNewMap : public CDialog
{
	DECLARE_DYNAMIC(CDlgNewMap)

public:
	CDlgNewMap(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgNewMap();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	int m_nMapWidth;
	int m_nMapHeight;

	CComboBox m_cmbWidth;
	CComboBox m_cmbHeight;
	virtual BOOL OnInitDialog();

	CMyButton m_btnOK;
	CMyButton m_btnCancel;
};
