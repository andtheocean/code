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
	COLORREF clrMask; //͸��ɫ

	int m_nBmpSize; //ͼ��ߴ�
	int m_Jg; //ͼ����ı�֮��ļ��

	int iOffsetX;
	int iOffsetY;


	BOOL b_Flag; //��ť״̬��false-������true-��ǰ�� 
	BOOL b_InRect; //�����밴ť��Χ��־ 
	BOOL b_Down; //����Ƿ��ڰ�ť�ϰ���

	CString m_strText; //��ť���� 
	
	COLORREF m_ForeColor; //�ı���ɫ 
	COLORREF m_BkColor; //����ɫ 
	COLORREF m_LockForeColor; //������ť��������ɫ 

	CRect m_ButRect; //��ť�ߴ�

	CPoint m_textPt; //�������꣨���Ͻǣ�
	CPoint m_ImagePt; //ͼ������(���Ͻ�)
};


