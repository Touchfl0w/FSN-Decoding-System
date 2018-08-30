// EXE3Dlg.h : header file
//

#if !defined(AFX_EXE3DLG_H__5CE2B372_80A0_4DA1_8AF8_0BCD100CCEF3__INCLUDED_)
#define AFX_EXE3DLG_H__5CE2B372_80A0_4DA1_8AF8_0BCD100CCEF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEXE3Dlg dialog

class CEXE3Dlg : public CDialog
{
// Construction
public:
	CEXE3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEXE3Dlg)
	enum { IDD = IDD_EXE3_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEXE3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEXE3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnOpen();
	afx_msg void OnSearch();
	afx_msg void OnGengzheng();
	afx_msg void OnReserve();
	afx_msg void OnLingcun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXE3DLG_H__5CE2B372_80A0_4DA1_8AF8_0BCD100CCEF3__INCLUDED_)
