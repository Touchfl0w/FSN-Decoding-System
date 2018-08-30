// EXE3Dlg.cpp : implementation file
//
#include "stdafx.h"
#include "guan.h"
#include<vector>
#include<CString>
#include "EXE3.h"
#include "EXE3Dlg.h"
#include "NewDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
extern vector<Money_Info> Vec_MoneyInfo;
extern int OFFSET;
CString pathName;


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEXE3Dlg dialog

CEXE3Dlg::CEXE3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEXE3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEXE3Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEXE3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEXE3Dlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEXE3Dlg, CDialog)
	//{{AFX_MSG_MAP(CEXE3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_GENGZHENG, OnGengzheng)
	ON_BN_CLICKED(IDC_RESERVE, OnReserve)
	ON_BN_CLICKED(IDC_LINGCUN, OnLingcun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEXE3Dlg message handlers

BOOL CEXE3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CString Field[8]={"序号","冠字号","真假","币种","面额","版别","日期","机具编号"};
    for(int i=0;i<6;i++){
		m_list.InsertColumn(i,Field[i],LVCFMT_LEFT,122);
	}
	m_list.InsertColumn(6,Field[6],LVCFMT_LEFT,200);
    m_list.InsertColumn(7,Field[7],LVCFMT_LEFT,200);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEXE3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEXE3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEXE3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CEXE3Dlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	extern int OFFSET;
	OFFSET=1544;
	CString szFilters="FSN (*.FSN)|*.FSN|CRH(*.CRH)|*.CRH|All Files(*.*)|*.*||";
	CFileDialog fileDlg(TRUE,"my","*.FSN",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,szFilters,this);
	if(fileDlg.DoModal()==IDOK){
   pathName=fileDlg.GetPathName();
		//
   
	FsnParser ftd ;
	Vec_MoneyInfo = ftd.ReadTk(pathName,0);
	
	m_list.DeleteAllItems();
	CString a;
	
    for(int i=0;i<Vec_MoneyInfo.size();i++){
    a.Format("%d", i);
        m_list.InsertItem(i,a,0);
        m_list.SetItemText(i,1,Vec_MoneyInfo[i].Id);
        m_list.SetItemText(i,2,Vec_MoneyInfo[i].IsReal);
		m_list.SetItemText(i,3,Vec_MoneyInfo[i].Kinds);
		m_list.SetItemText(i,4,Vec_MoneyInfo[i].Value);
		m_list.SetItemText(i,5,Vec_MoneyInfo[i].Ver);
		m_list.SetItemText(i,6,Vec_MoneyInfo[i].time);
		m_list.SetItemText(i,7,Vec_MoneyInfo[i].MachineSNo);

	}
        CString fileName=fileDlg.GetFileName();
		SetWindowText(fileName);
	}
}

void CEXE3Dlg::OnSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CNewDialog dlg;
	dlg.DoModal();
}

void CEXE3Dlg::OnGengzheng() 
{
	// TODO: Add your control notification handler code here

	OFFSET=1608;
	FsnParser ftd ;
	Vec_MoneyInfo = ftd.ReadTk(pathName,0);
	
	m_list.DeleteAllItems();
	CString a;
	
    for(int i=0;i<Vec_MoneyInfo.size();i++){
    a.Format("%d", i);
        m_list.InsertItem(i,a,0);
        m_list.SetItemText(i,1,Vec_MoneyInfo[i].Id);
        m_list.SetItemText(i,2,Vec_MoneyInfo[i].IsReal);
		m_list.SetItemText(i,3,Vec_MoneyInfo[i].Kinds);
		m_list.SetItemText(i,4,Vec_MoneyInfo[i].Value);
		m_list.SetItemText(i,5,Vec_MoneyInfo[i].Ver);
		m_list.SetItemText(i,6,Vec_MoneyInfo[i].time);
		m_list.SetItemText(i,7,Vec_MoneyInfo[i].MachineSNo);

	}
}

void CEXE3Dlg::OnReserve() 
{
	// TODO: Add your control notification handler code here
char buf[26];
	//char* buf=0;
		CString szFilters="Word文档(*.doc)|*.doc|CRH(*.CRH)|*.CRH|All Files(*.*)|*.*||";
	CFileDialog fileDlg(FALSE,"my","*.doc",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,szFilters,this);
	if(fileDlg.DoModal()==IDOK){

		/**********************
CString m_saveFileName=fileDlg.GetFileName();
CString m_exeFileName=fileDlg.GetFileExt();
if(m_exeFileName=="doc"){
	CFile* pfilename=new CFile(m_saveFileName,CFile::modeCreate|CFile::modeWrite);
	CArchive archive(pfilename,CArchive::store|CArchive::bNoFlushOnDelete);
	//file.SeekToBegin();
cout<<"1234";
cout<<'1';
archive.Close();
pfilename->Close();
delete pfilename;
	//for(int i=0;i<Vec_MoneyInfo.size();i++){
			//for(int j=0;i<8;j++){
**************************************************************/
CString m_saveFileName=fileDlg.GetFileName();
CString m_exeFileName=fileDlg.GetFileExt();
if(m_exeFileName=="doc"){
	CFile file(m_saveFileName,CFile::modeCreate|CFile::modeWrite);
    file.SeekToBegin();
file.Write("冠字号",6);
		file.Write("      ",6);
		file.Write("真假",4);
		file.Write("  ",2);
		file.Write("币种",4);
		file.Write("    ",4);
		file.Write("面额",4);
		file.Write(" ",1);
		file.Write("日期",4);
		file.Write("               ",15);
		file.Write("机具编号",8);
		file.Write("\r\n",2);
    for(int i=0;i<Vec_MoneyInfo.size();i++){
       //char *p =(LPSTR)(LPCTSTR)Vec_MoneyInfo[i].Id;

	//	buf=p;
		//	memset(buf, 0, 26);
		//	sprintf(tmpbuf, "%d", Vec_MoneyInfo);
		
		    memset(buf, 0, 26);
            strcpy(buf, Vec_MoneyInfo[i].Id);
			file.Write(buf,10);
			file.Write("  ",2);
			memset(buf, 0, 26);
            strcpy(buf, Vec_MoneyInfo[i].IsReal);
			file.Write(buf,4);
			file.Write("  ",2);

			memset(buf, 0, 26);
            strcpy(buf, Vec_MoneyInfo[i].Kinds);
			file.Write(buf,6);
			file.Write("  ",2);

			memset(buf, 0, 26);
            strcpy(buf, Vec_MoneyInfo[i].Value);
			file.Write(buf,3);
			file.Write("  ",2);

			memset(buf, 0, 26);
            strcpy(buf, Vec_MoneyInfo[i].Ver);
			file.Write(buf,4);
			file.Write("  ",2);

			memset(buf, 0, 26);
            strcpy(buf, Vec_MoneyInfo[i].time);
			file.Write(buf,19);
			file.Write("  ",2);

			memset(buf, 0, 26);
            strcpy(buf, Vec_MoneyInfo[i].MachineSNo);
			file.Write(buf,19);
			
            file.Write("\r\n",2);
	}
	file.Flush();
	file.Close();


}
else{
    buf[100];
    CFile file(pathName,CFile::modeRead);
    CFile fileTemp(m_saveFileName,CFile::modeCreate|CFile::modeWrite);
    file.SeekToBegin();
	file.Read(buf,32);
	fileTemp.Write(buf,32);

    for(int i=0;i<Vec_MoneyInfo.size();i++){
		file.Read(buf,100);
		fileTemp.Write(buf,100);
		file.Seek(1544,CFile::current);
	}
    file.Flush();
	file.Close();
    fileTemp.Flush();
	fileTemp.Close();



    //
	}
}
}

void CEXE3Dlg::OnLingcun() 
{
	// TODO: Add your control notification handler code here
	char buf[100];
	char buf1[1544];
	CString szFilters="Word文档(*.doc)|*.doc|FSN(*.FSN)|*.FSN|CRH(*.CRH)|*.CRH|All Files(*.*)|*.*||";
	CFileDialog fileDlg(FALSE,"my","*.doc",OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,szFilters,this);
	if(fileDlg.DoModal()==IDOK){
	CString m_saveFileName=fileDlg.GetFileName();
    CFile file(pathName,CFile::modeRead);
    CFile fileTemp(m_saveFileName,CFile::modeCreate|CFile::modeWrite);
    file.SeekToBegin();
	file.Read(buf,32);
	fileTemp.Write(buf,32);

    for(int i=0;i<Vec_MoneyInfo.size();i++){
		file.Read(buf,100);
		fileTemp.Write(buf,100);
		file.Seek(64,CFile::current);
		file.Read(buf,1544);
		fileTemp.Write(buf,1544);
	}
    file.Flush();
	file.Close();
    fileTemp.Flush();
	fileTemp.Close();
	}

}
