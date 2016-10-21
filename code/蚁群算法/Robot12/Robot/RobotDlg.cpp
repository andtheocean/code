// RobotDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Robot.h"
#include "RobotDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRobotDlg �Ի���




CRobotDlg::CRobotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRobotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pMapView=NULL;
}

void CRobotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_BARRER, m_btnBarrier);
	DDX_Control(pDX, IDC_BTN_CLEAR, m_btnClearBarrier);
	DDX_Control(pDX, IDC_BTN_START, m_btnStart);
	DDX_Control(pDX, IDC_BTN_END, m_btnEnd);
	DDX_Control(pDX, IDC_BTN_NEWMAP, m_btnNewMap);
	DDX_Control(pDX, IDC_BTN_SAVEMAP, m_btnSaveMap);
	DDX_Control(pDX, IDC_BTN_SEARCH, m_btnSearch);
	DDX_Control(pDX, IDOK, m_btnExit);
	DDX_Control(pDX, IDC_CHECK_XY, m_btnCheck);
	DDX_Control(pDX, IDC_ST_VIEW, m_stView);
	DDX_Control(pDX, IDC_CHECK_CURVE, m_btnCurve);
}

BEGIN_MESSAGE_MAP(CRobotDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CRobotDlg::OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_BTN_BARRER, &CRobotDlg::OnBnClickedBtnBarrer)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CRobotDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_START, &CRobotDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_END, &CRobotDlg::OnBnClickedBtnEnd)
	ON_BN_CLICKED(IDC_BTN_SAVEMAP, &CRobotDlg::OnBnClickedBtnSavemap)
	ON_BN_CLICKED(IDOK, &CRobotDlg::OnBnClickedOk)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_NEWMAP, &CRobotDlg::OnBnClickedBtnNewmap)
	ON_BN_CLICKED(IDC_CHECK_XY, &CRobotDlg::OnBnClickedCheckXy)
	ON_WM_SIZE()

	ON_MESSAGE(WM_USER+100,OnShowProcess)

	ON_BN_CLICKED(IDC_CHECK_CURVE, &CRobotDlg::OnBnClickedCheckCurve)
END_MESSAGE_MAP()


// CRobotDlg ��Ϣ�������


BOOL CRobotDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	srand((unsigned)time( NULL));

	//���õ�ͼ���ݡ���ʼ�㡢������
	g_pMapAry=Create2DArray<int>(N_MAX_MAP_WIDTH,N_MAX_MAP_HEIGHT);
	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			if ((i*j==100) || (i*j==120) || (i*j==130) || (i*j==140) || (i*j==150) || (i*j==90) || (i*j==1200) || (i*j==1100) || (i*j==1000)  || (i*j==900) || (i+j==126))
			{
				g_pMapAry[i][j]=BARRIER;
			}
			else
			{
				g_pMapAry[i][j]=NIL;
			}

			if ((i*j>600) && (i*j<636))
			{
				g_pMapAry[i][j]=BARRIER;
			}

		}
	}

	g_ptStart.x=0;
	g_ptStart.y=0;

	g_ptEnd.x=N_MAP_WIDTH-1;
	g_ptEnd.y=N_MAP_HEIGHT-1;

	g_pMapAry[g_ptStart.x][g_ptStart.y]=START;
	g_pMapAry[g_ptEnd.x][g_ptEnd.y]=END;

	LoadMap();
	//'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	//������ͼ
	CCreateContext cc;
	ZeroMemory(&cc, sizeof(cc));

	if (m_pMapView==NULL)
	{
		m_pMapView=(CMapView*)RUNTIME_CLASS(CMapView)->CreateObject();
		m_pMapView->Create(NULL, NULL, WS_CHILD |WS_VISIBLE, CRect(1, 1,1,1), this,9991, &cc);

	}


	//����λ��
	CRect rc;
	((CWnd*)GetDlgItem(IDC_ST_VIEW))->GetWindowRect(&rc );
	ScreenToClient(&rc );
	m_pMapView->MoveWindow(rc.left+1,rc.top+1,rc.Width()-2,rc.Height()-2,1);


	m_btnBarrier.SetBmp(IDB_BMP_BTN,1);
	m_btnClearBarrier.SetBmp(IDB_BMP_BTN,2);
	m_btnStart.SetBmp(IDB_BMP_BTN,3);
	m_btnEnd.SetBmp(IDB_BMP_BTN,4);
	m_btnNewMap.SetBmp(IDB_BMP_BTN,5);
	m_btnSaveMap.SetBmp(IDB_BMP_BTN,6);
	m_btnSearch.SetBmp(IDB_BMP_BTN,7);
	m_btnExit.SetBmp(IDB_BMP_BTN,8);


	((CButton*)GetDlgItem(IDC_CHECK_XY))->SetCheck(1);

	ReSize();

	g_hwnd=this->m_hWnd;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

LRESULT CRobotDlg::OnShowProcess(WPARAM wParam, LPARAM lParam)
{
	int nPos=((int)wParam+1)*100/N_IT_COUNT;
	CString str="";
	str.Format("%d%%",nPos);
	m_btnSearch.SetWindowTextA(str);

	DoEvents();

	return 0;
}

//��Ӧ������Ϣ
bool CRobotDlg::DoEvents()
{ 
	MSG msg; 
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{ 
		if (msg.message==WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}

	return true;
} 

void CRobotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRobotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CRobotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRobotDlg::OnBnClickedBtnSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str="";

	m_pMapView->m_nFlag=0;
	SetButtonText();

	((CButton*)GetDlgItem(IDC_BTN_SEARCH))->EnableWindow(FALSE);
	DWORD dw1=::GetTickCount();

	m_tsp.InitData();
	m_tsp.Search();

	DWORD dw2=::GetTickCount();
	((CButton*)GetDlgItem(IDC_BTN_SEARCH))->EnableWindow(TRUE);


	//��ʾ���
	if (g_blCanSolved == true)
	{
		m_pMapView->m_bestTabuAry.RemoveAll();
		m_pMapView->m_bestTabuAry.Copy(m_tsp.m_cBestAnt.m_tabuAry);
		m_pMapView->m_dbBestLength=m_tsp.m_cBestAnt.m_dbPathLength;
		m_pMapView->m_dbTime=(dw2-dw1)/1000.0;

		this->Invalidate(FALSE);
	}
	else
	{
		m_pMapView->m_bestTabuAry.RemoveAll();
		this->Invalidate(FALSE);
		MessageBox("�޿���·����\n\n������������ǲ���","��ʾ",MB_OK+MB_ICONEXCLAMATION);
	}

	m_btnSearch.SetWindowTextA("����");


}

//���ر���ĵ�ͼ
void CRobotDlg::LoadMap()
{
	//�ļ�������
	if (::GetFileAttributes("c:\\map.txt") == -1)
	{
		return;
	}

	CStdioFile f;
	if (f.Open("c:\\map.txt",CFile::modeRead,NULL) == 0)
	{
		return;
	}

	CString str="";
	int nRow=0;
	int nValue=0;
	while (f.ReadString(str) == TRUE)
	{
		if (nRow == 0)
		{
			N_MAP_WIDTH=str.GetLength();
		}
		for (int i=0;i<str.GetLength();i++)
		{
			nValue=atoi(str.Mid(i,1));
			g_pMapAry[i][nRow]=nValue;
			if (nValue == START)
			{
				g_ptStart.x=i;
				g_ptStart.y=nRow;
			}
			else if (nValue == END)
			{
				g_ptEnd.x=i;
				g_ptEnd.y=nRow;
			}

		}
		nRow++;
	}

	f.Close();

	N_MAP_HEIGHT=nRow;

}

void CRobotDlg::OnBnClickedBtnBarrer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pMapView->m_nFlag=1;
	m_pMapView->ShowTip();
	SetButtonText();

}

void CRobotDlg::OnBnClickedBtnClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pMapView->m_nFlag=2;
	m_pMapView->ShowTip();
	SetButtonText();
}

void CRobotDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pMapView->m_nFlag=3;
	m_pMapView->ShowTip();
	SetButtonText();
}

void CRobotDlg::OnBnClickedBtnEnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pMapView->m_nFlag=4;
	m_pMapView->ShowTip();
	SetButtonText();
}

//���ð�ť�ı�
void CRobotDlg::SetButtonText()
{
	((CButton*)GetDlgItem(IDC_BTN_BARRER))->SetWindowText("���ϰ�");
	((CButton*)GetDlgItem(IDC_BTN_CLEAR))->SetWindowText("���ϰ�");
	((CButton*)GetDlgItem(IDC_BTN_START))->SetWindowText("��ʼ��");
	((CButton*)GetDlgItem(IDC_BTN_END))->SetWindowText("������");

	if (m_pMapView->m_nFlag == 1)
	{
		((CButton*)GetDlgItem(IDC_BTN_BARRER))->SetWindowText("���ϰ�*");
	}
	else if (m_pMapView->m_nFlag == 2)
	{
		((CButton*)GetDlgItem(IDC_BTN_CLEAR))->SetWindowText("���ϰ�*");
	}
	else if (m_pMapView->m_nFlag == 3)
	{	
		((CButton*)GetDlgItem(IDC_BTN_START))->SetWindowText("��ʼ��*");
	}
	else if (m_pMapView->m_nFlag == 4)
	{
		((CButton*)GetDlgItem(IDC_BTN_END))->SetWindowText("������*");
	}


}


void CRobotDlg::OnBnClickedBtnSavemap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStdioFile f;
	if (f.Open("c:\\map.txt",CFile::modeReadWrite|CFile::modeCreate) == FALSE)
	{
		MessageBox("����ʧ��!","��ʾ",MB_OK+MB_ICONEXCLAMATION);
		return;
	}

	CString str="";
	CString strA="";
	for (int j=0;j<N_MAP_HEIGHT;j++)
	{
		strA="";
		for (int i=0;i<N_MAP_WIDTH;i++)
		{
			str.Format("%d",g_pMapAry[i][j]);
			strA=strA+str;
		}
		f.WriteString(strA+"\n");
	}

	f.Close();
}

void CRobotDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (MessageBox("ȷ���˳���","��ʾ",MB_YESNO+MB_DEFBUTTON2+MB_ICONQUESTION) == IDYES)
	{
		Free2DArray(g_pMapAry,N_MAX_MAP_WIDTH);
		OnOK();
	}

}

void CRobotDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Free2DArray(g_pMapAry,N_MAX_MAP_WIDTH);

	CDialog::OnClose();
}

void CRobotDlg::OnBnClickedBtnNewmap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDlgNewMap dlg;
	if (dlg.DoModal() == IDOK)
	{
		N_MAP_WIDTH=dlg.m_nMapWidth;
		N_MAP_HEIGHT=dlg.m_nMapHeight;
	}
	else
	{
		return;
	}

	for (int i=0;i<N_MAP_WIDTH;i++)
	{
		for (int j=0;j<N_MAP_HEIGHT;j++)
		{
			g_pMapAry[i][j]=NIL;
		}
	}

	g_ptStart.x=0;
	g_ptStart.y=0;

	g_ptEnd.x=N_MAP_WIDTH-1;
	g_ptEnd.y=N_MAP_HEIGHT-1;

	g_pMapAry[g_ptStart.x][g_ptStart.y]=START;
	g_pMapAry[g_ptEnd.x][g_ptEnd.y]=END;

	m_pMapView->m_bestTabuAry.RemoveAll();

	m_pMapView->Invalidate(FALSE);
}

//�ߴ�ı䣬�����ؼ�λ��
void CRobotDlg::ReSize()
{
	CRect rc;
	this->GetClientRect(rc);

	int nW=3;
	int nMargin=12;
	int nBH=27;
	if (m_pMapView->GetSafeHwnd())
	{
		m_stView.MoveWindow(nMargin,nMargin,rc.Width()-nMargin*2,rc.Height()-nMargin*3-nBH);
		m_pMapView->MoveWindow(nMargin+1,nMargin+1,rc.Width()-nMargin*2-3,rc.Height()-nMargin*3-nBH-3);
	}

	//����ؼ�û�д������˳�
	if (m_btnBarrier.GetSafeHwnd() == NULL)
	{
		return;
	}


	int x=nMargin;
	CRect rc1;
	m_btnBarrier.GetClientRect(rc1);
	int y=rc.Height()-nMargin-rc1.Height();

	m_btnBarrier.MoveWindow(x,y,rc1.Width(),rc1.Height(),TRUE);
	x=x+rc1.Width()+nW;

	m_btnClearBarrier.GetClientRect(rc1);
	m_btnClearBarrier.MoveWindow(x,y,rc1.Width(),rc1.Height(),TRUE);
	x=x+rc1.Width()+nW;

	m_btnStart.GetClientRect(rc1);
	m_btnStart.MoveWindow(x,y,rc1.Width(),rc1.Height(),TRUE);
	x=x+rc1.Width()+nW;

	m_btnEnd.GetClientRect(rc1);
	m_btnEnd.MoveWindow(x,y,rc1.Width(),rc1.Height(),TRUE);
	x=x+rc1.Width()+nW;

	//==============================================
	x=x+2*nW;
	m_btnNewMap.GetClientRect(rc1);
	m_btnNewMap.MoveWindow(x,y,rc1.Width(),rc1.Height(),TRUE);
	x=x+rc1.Width()+nW;

	m_btnSaveMap.GetClientRect(rc1);
	m_btnSaveMap.MoveWindow(x,y,rc1.Width(),rc1.Height(),TRUE);
	x=x+rc1.Width()+nW;

	//==============================================
	m_btnCheck.GetWindowRect(rc1);
	m_btnCheck.MoveWindow(x+nW,y+(nBH-rc1.Height())/2,rc1.Width(),rc1.Height(),TRUE);
	x=x+rc1.Width()+nW;

	x=x+nW;
	m_btnCurve.GetWindowRect(rc1);
	m_btnCurve.MoveWindow(x+nW,y+(nBH-rc1.Height())/2,rc1.Width(),rc1.Height(),TRUE);
	//==============================================
	m_btnSearch.GetClientRect(rc1);
	x=rc.Width()-nMargin-2*rc1.Width()-nW;
	m_btnSearch.MoveWindow(x,y,rc1.Width(),rc1.Height(),TRUE);

	x=x+nW+rc1.Width();
	m_btnExit.MoveWindow(x,y,rc1.Width(),rc1.Height(),TRUE);

	this->Invalidate();

}

void CRobotDlg::OnBnClickedCheckXy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pMapView->m_blShowXY = !m_pMapView->m_blShowXY;
	((CButton*)GetDlgItem(IDC_CHECK_XY))->SetCheck(m_pMapView->m_blShowXY);

}

void CRobotDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	ReSize();
}

void CRobotDlg::OnBnClickedCheckCurve()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pMapView->m_blShowCurve = !m_pMapView->m_blShowCurve;
	m_btnCurve.SetCheck(m_pMapView->m_blShowCurve);
	m_pMapView->Invalidate(FALSE);

}
