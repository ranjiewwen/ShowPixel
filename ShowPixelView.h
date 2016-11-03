// ShowPixelView.h : interface of the CShowPixelView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWPIXELVIEW_H__19A2CBC1_E971_4D27_A753_F4DBC5000A57__INCLUDED_)
#define AFX_SHOWPIXELVIEW_H__19A2CBC1_E971_4D27_A753_F4DBC5000A57__INCLUDED_
class CShowPixDoc;
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define  WIDTH 25
#define  HEIGHT 16

class CPixelDlg;//这个很重要的好像！！！！！！！！！！！！！！
class CDlgTest;

class CShowPixelDoc;
class CShowPixelView : public CView
{
protected: // create from serialization only
	CShowPixelView();
	DECLARE_DYNCREATE(CShowPixelView)

// Attributes
public:
	CShowPixelDoc* GetDocument();

	CPoint point1;//点击空白的开始坐标
	BOOL m_bClickEmpty; //判断是否点击了空白的地方，以实现拖动选择
	CPoint   end_Point;
	BOOL m_bCaptured;
public:
	static GLfloat fShininess;
	static GLfloat glfMatEmission[4];
	static GLfloat glfMatSpecular[4];
	static GLfloat glfMatDiffuse[4];
	static GLfloat glfMatAmbient[4];
	GLfloat m_fxAngle,m_fzAngle;

	HGLRC m_hRC;

	void drawPixel(CPoint pos);

private:
	BYTE* pGrayData;
	int nWidth,nHeight,nBitCount,nWidthBytes;
// Operations
public:
	BOOL b_Created;
	BOOL b_Static;
	CPixelDlg* m_pDlg;
	CDlgTest* m_testDlg;
	CRect pre_rect;
	int row;
	int col;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowPixelView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void Test();
	virtual ~CShowPixelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShowPixelView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ShowPixelView.cpp
inline CShowPixelDoc* CShowPixelView::GetDocument()
   { return (CShowPixelDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWPIXELVIEW_H__19A2CBC1_E971_4D27_A753_F4DBC5000A57__INCLUDED_)
