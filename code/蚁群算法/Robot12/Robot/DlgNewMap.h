#pragma once
#include "afxwin.h"
#include "MyButton.h"

// CDlgNewMap 对话框

class CDlgNewMap : public CDialog
{
	DECLARE_DYNAMIC(CDlgNewMap)

public:
	CDlgNewMap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgNewMap();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
