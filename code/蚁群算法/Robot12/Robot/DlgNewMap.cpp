// DlgNewMap.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Robot.h"
#include "DlgNewMap.h"


// CDlgNewMap �Ի���

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


// CDlgNewMap ��Ϣ�������

void CDlgNewMap::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}
