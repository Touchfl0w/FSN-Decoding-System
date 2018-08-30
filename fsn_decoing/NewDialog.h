#if !defined(AFX_NEWDIALOG_H__F36E50F7_55CE_48ED_A2A6_B72CB2812154__INCLUDED_)
#define AFX_NEWDIALOG_H__F36E50F7_55CE_48ED_A2A6_B72CB2812154__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewDialog dialog

class CNewDialog : public CDialog
{
// Construction
public:
	CNewDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewDialog)
	enum { IDD = IDD_DIALOG1 };
	CString	m_guanzihao;
	CString	m_banbie;
	CString	m_riqi;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewDialog)
	afx_msg void OnSearch1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
void KmpSearch(char* s, char* p, int* nextarr);  
void GetNextval(char* p, int* nextarr); 
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWDIALOG_H__F36E50F7_55CE_48ED_A2A6_B72CB2812154__INCLUDED_)
