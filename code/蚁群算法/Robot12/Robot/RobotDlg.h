// RobotDlg.h : ͷ�ļ�
//

#pragma once
#include "MapView.h"
#include "DlgNewMap.h"
#include "MyButton.h"
#include "tsp.h"
#include "afxwin.h"

// CRobotDlg �Ի���
class CRobotDlg : public CDialog
{
// ����
public:
	CRobotDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ROBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	bool DoEvents();

	CMapView* m_pMapView;

	CTsp m_tsp;

public:
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedBtnBarrer();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnEnd();
	afx_msg void OnBnClickedBtnSavemap();

	void LoadMap();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnNewmap();


	void SetButtonText(); //���ð�ť�ı�
	LRESULT OnShowProcess(WPARAM wParam, LPARAM lParam);	

	CMyButton m_btnBarrier;
	CMyButton m_btnClearBarrier;
	CMyButton m_btnStart;
	CMyButton m_btnEnd;
	CMyButton m_btnNewMap;
	CMyButton m_btnSaveMap;
	CMyButton m_btnSearch;
	CMyButton m_btnExit;

	afx_msg void OnBnClickedCheckXy();

	void ReSize(); //�ߴ�ı䣬�����ؼ�λ��

	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_btnCheck;
	CStatic m_stView;
	CButton m_btnCurve;
	afx_msg void OnBnClickedCheckCurve();
};
