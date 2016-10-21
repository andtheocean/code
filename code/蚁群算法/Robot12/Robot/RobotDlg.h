// RobotDlg.h : 头文件
//

#pragma once
#include "MapView.h"
#include "DlgNewMap.h"
#include "MyButton.h"
#include "tsp.h"
#include "afxwin.h"

// CRobotDlg 对话框
class CRobotDlg : public CDialog
{
// 构造
public:
	CRobotDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ROBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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


	void SetButtonText(); //设置按钮文本
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

	void ReSize(); //尺寸改变，调整控件位置

	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_btnCheck;
	CStatic m_stView;
	CButton m_btnCurve;
	afx_msg void OnBnClickedCheckCurve();
};
