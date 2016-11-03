// ShowPixel.h : main header file for the SHOWPIXEL application
//

#if !defined(AFX_SHOWPIXEL_H__27E2BCD3_11DF_409F_978C_782C0B938AF4__INCLUDED_)
#define AFX_SHOWPIXEL_H__27E2BCD3_11DF_409F_978C_782C0B938AF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CShowPixelApp:
// See ShowPixel.cpp for the implementation of this class
//

class CShowPixelApp : public CWinApp
{
public:
	CShowPixelApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowPixelApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CShowPixelApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWPIXEL_H__27E2BCD3_11DF_409F_978C_782C0B938AF4__INCLUDED_)
