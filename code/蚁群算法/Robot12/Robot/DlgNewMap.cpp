// DlgNewMap.cpp : 实现文件
//

#include "stdafx.h"
#include "Robot.h"
#include "DlgNewMap.h"


// CDlgNewMap 对话框

IMPLEMENT_DYNAMIC(CDlgNewMap, CDialog)

CDlgNewMap::CDlgNewMap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewMap::IDD, pParent)
{

}

CDlgNewMap::~CDlgNewMap()
{
}

void CDlgNewMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_MAP_WIDTH, m_cmbWidth);
	DDX_Control(pDX, IDC_CMB_HEIGHT, m_cmbHeight);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CDlgNewMap, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgNewMap::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgNewMap 消息处理程序

void CDlgNewMap::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str="";
	m_cmbWidth.GetWindowTextA(str);
	m_nMapWidth=atoi(str);

	m_cmbHeight.GetWindowTextA(str);
	m_nMapHeight=atoi(str);

	OnOK();
}

BOOL CDlgNewMap::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString str="";
	for (int i=1;i<=20;i++)
	{
		str.Format("%d",i*5);
		m_cmbWidth.AddString(str);
		m_cmbHeight.AddString(str);
	}

	m_cmbWidth.SetCurSel(7);
	m_cmbHeight.SetCurSel(7);

	m_btnOK.SetBmp(IDB_BMP_BTN,9);
	m_btnCancel.SetBmp(IDB_BMP_BTN,10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
