#pragma once


// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

public:
	
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void NormalButton(CDC* pDC);
	void PassButton(CDC* pDC);
	void LockButton(CDC* pDC);
	void DownButton(CDC* pDC);

	void SetBmp(UINT nBmpID,int nBmpIndex);
	void ShowBmp(CDC* pDC);

private:

	UINT m_nBmpID;
	int m_nBmpIndex;
	COLORREF clrMask; //透明色

	int m_nBmpSize; //图像尺寸
	int m_Jg; //图像和文本之间的间隔

	int iOffsetX;
	int iOffsetY;


	BOOL b_Flag; //按钮状态（false-正常，true-当前） 
	BOOL b_InRect; //鼠标进入按钮范围标志 
	BOOL b_Down; //鼠标是否在按钮上按下

	CString m_strText; //按钮文字 
	
	COLORREF m_ForeColor; //文本颜色 
	COLORREF m_BkColor; //背景色 
	COLORREF m_LockForeColor; //锁定按钮的文字颜色 

	CRect m_ButRect; //按钮尺寸

	CPoint m_textPt; //文字坐标（左上角）
	CPoint m_ImagePt; //图像坐标(左上角)
};


