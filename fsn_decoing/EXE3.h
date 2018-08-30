// EXE3.h : main header file for the EXE3 application
//

#if !defined(AFX_EXE3_H__2221834D_9DD9_42FA_AFB6_5860648F157E__INCLUDED_)
#define AFX_EXE3_H__2221834D_9DD9_42FA_AFB6_5860648F157E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEXE3App:
// See EXE3.cpp for the implementation of this class
//

class CEXE3App : public CWinApp
{
public:
	CEXE3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEXE3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEXE3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXE3_H__2221834D_9DD9_42FA_AFB6_5860648F157E__INCLUDED_)
