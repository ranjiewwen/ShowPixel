// ShowPixelDoc.h : interface of the CShowPixelDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWPIXELDOC_H__58EDA2ED_507B_4911_9D74_29258D3D5257__INCLUDED_)
#define AFX_SHOWPIXELDOC_H__58EDA2ED_507B_4911_9D74_29258D3D5257__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CShowPixelDoc : public CDocument
{
protected: // create from serialization only
	CShowPixelDoc();
	DECLARE_DYNCREATE(CShowPixelDoc)

		// Attributes
public:
	//================================函数和变量定义========================
	int nWidth;//图像宽度
	int nHeight;//图像高度
	int nColorBits;//每个象素所占的位数
	int nColor;//图像的颜色数
	int nLen;//图像文件的大小，以字节数计
	int nByteWidth;//图像每行的字节数
	BYTE * lpBitmap;//指向图像首字节的指针
	BYTE * lpBits;//指向图像实际数据的指针
	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowPixelDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShowPixelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CShowPixelDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWPIXELDOC_H__58EDA2ED_507B_4911_9D74_29258D3D5257__INCLUDED_)
