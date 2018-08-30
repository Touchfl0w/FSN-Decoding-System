// NewDialog.cpp : implementation file
//

#include "stdafx.h"
#include "EXE3.h"
#include "NewDialog.h"
#include<vector>
#include "guan.h"
#include "EXE3Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewDialog dialog

extern std::vector<Money_Info> Vec_MoneyInfo;
  CString b;//行号转字符
   int j=0;//行号
int i=0;

CEXE3Dlg *PDLG=0 ;


void KmpSearch(char* s, char* p, int* nextarr){  
   
   int I = 0, J = 0;  
    int sLenth = strlen(s);  
    int pLenth = strlen(p);  
    while (I < sLenth&&J< pLenth)  
    {  
      if (J == -1 || s[I] == p[J]){  
           I++, J++;  
        }  
        else{  
           J= nextarr[J];  
        }  
    }  
   if (J == pLenth){  
      //////////////////////////////////////////////////////////////////////////////////////////
	b.Format("%d", j);
					PDLG->m_list.InsertItem(j,b,0);
			     	PDLG->m_list.SetItemText(j,1,Vec_MoneyInfo[i].Id);
                	PDLG->m_list.SetItemText(j,2,Vec_MoneyInfo[i].IsReal);
	            	PDLG->m_list.SetItemText(j,3,Vec_MoneyInfo[i].Kinds);
	                PDLG->m_list.SetItemText(j,4,Vec_MoneyInfo[i].Value);
		        	PDLG->m_list.SetItemText(j,5,Vec_MoneyInfo[i].Ver);
	          		PDLG->m_list.SetItemText(j,6,Vec_MoneyInfo[i].time);
	        		PDLG->m_list.SetItemText(j,7,Vec_MoneyInfo[i].MachineSNo);
				    j++;
    }  
   else  
   {  
       cout << "None" << endl;  
    }  
}  
  
 
void GetNextval(char* p, int* nextarr){  
 
    int pLenth = strlen(p);  
    nextarr[0] = -1;  
    int k = -1;  
    int j = 0;  
    while (j < pLenth - 1)  
    {  
        if (k == -1 || p[j] == p[k]){  
            j++, k++;  
            if (p[j] != p[k]){  
                nextarr[j] = k;  
            }  
           else  
            {  
                nextarr[j] = nextarr[k];  
            }  
        }  
        else  
        {  
            k = nextarr[k];  
       }  
    }  
}  




CNewDialog::CNewDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNewDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewDialog)
	m_guanzihao = _T("");
	m_banbie = _T("");
	m_riqi = _T("");
	//}}AFX_DATA_INIT
}


void CNewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewDialog)
	DDX_Text(pDX, IDC_EDIT1, m_guanzihao);
	DDX_Text(pDX, IDC_EDIT2, m_banbie);
	DDX_Text(pDX, IDC_EDIT3, m_riqi);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewDialog, CDialog)
	//{{AFX_MSG_MAP(CNewDialog)
	ON_BN_CLICKED(IDC_SEARCH1, OnSearch1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewDialog message handlers

void CNewDialog::OnSearch1() 
{
	// TODO: Add your control notification handler code here
		UpdateData(TRUE);
		//MessageBox(Vec_MoneyInfo[0].Id);
        CEXE3Dlg *pDlg = (CEXE3Dlg *)this->GetParent();
		PDLG=pDlg;
     	pDlg->m_list.DeleteAllItems();
		
	  
		int trail;
        CString guanzihao;
		CString banbie;
		CString riqi;
		char* ppp=0;
		char* sss=0;
		j=0;
        int nextarr[10000];  //缓冲器
		if(!m_guanzihao.IsEmpty()){
			trail=1;//有冠字号
		}
		else if(!m_banbie.IsEmpty()){
			if(m_riqi.IsEmpty()){
				trail=2;//无冠字号，有版别，无日期
			}
			else{
				trail=3;//无冠字号，有版别，有日期
			}
		}
		else{
				trail=4;//仅有日期
			}
		switch(trail){
		case 1:
			{
				for( i=0;i<Vec_MoneyInfo.size();i++){
				              char *ppp =(LPSTR)(LPCTSTR)Vec_MoneyInfo[i].Id;
							  char *sss =(LPSTR)(LPCTSTR)m_guanzihao;
							  GetNextval(ppp, nextarr);  
                              KmpSearch(ppp, sss, nextarr);
				  
				   }
			}
				   break;
		case 2:
			{ for( i=0;i<Vec_MoneyInfo.size();i++){
				    if(Vec_MoneyInfo[i].Ver==m_banbie){// && Vec_MoneyInfo[i].Ver==m_banbie && Vec_MoneyInfo[i].time==m_riqi)
					b.Format("%d", j);
					pDlg->m_list.InsertItem(j,b,0);
					pDlg->m_list.SetItemText(j,1,Vec_MoneyInfo[i].Id);
                	pDlg->m_list.SetItemText(j,2,Vec_MoneyInfo[i].IsReal);
	         		pDlg->m_list.SetItemText(j,3,Vec_MoneyInfo[i].Kinds);
	            	pDlg->m_list.SetItemText(j,4,Vec_MoneyInfo[i].Value);
		        	pDlg->m_list.SetItemText(j,5,Vec_MoneyInfo[i].Ver);
	          		pDlg->m_list.SetItemText(j,6,Vec_MoneyInfo[i].time);
	        		pDlg->m_list.SetItemText(j,7,Vec_MoneyInfo[i].MachineSNo);
				    j++;
				   }
				   }
			}
				   break;
		case 3:
			{for( i=0;i<Vec_MoneyInfo.size();i++){
				    if(Vec_MoneyInfo[i].Ver==m_banbie && Vec_MoneyInfo[i].time==m_riqi ){// && Vec_MoneyInfo[i].Ver==m_banbie && Vec_MoneyInfo[i].time==m_riqi)
					b.Format("%d", j);
					pDlg->m_list.InsertItem(j,b,0);
					pDlg->m_list.SetItemText(j,1,Vec_MoneyInfo[i].Id);
                	pDlg->m_list.SetItemText(j,2,Vec_MoneyInfo[i].IsReal);
	         		pDlg->m_list.SetItemText(j,3,Vec_MoneyInfo[i].Kinds);
	            	pDlg->m_list.SetItemText(j,4,Vec_MoneyInfo[i].Value);
		        	pDlg->m_list.SetItemText(j,5,Vec_MoneyInfo[i].Ver);
	          		pDlg->m_list.SetItemText(j,6,Vec_MoneyInfo[i].time);
	        		pDlg->m_list.SetItemText(j,7,Vec_MoneyInfo[i].MachineSNo);
				    j++;
				   }
				   }
			}
				   break;
		case 4:
			{for( i=0;i<Vec_MoneyInfo.size();i++){
				    if(Vec_MoneyInfo[i].time==m_riqi ){// && Vec_MoneyInfo[i].Ver==m_banbie && Vec_MoneyInfo[i].time==m_riqi)
					b.Format("%d", j);
					pDlg->m_list.InsertItem(j,b,0);
					pDlg->m_list.SetItemText(j,1,Vec_MoneyInfo[i].Id);
                	pDlg->m_list.SetItemText(j,2,Vec_MoneyInfo[i].IsReal);
	         		pDlg->m_list.SetItemText(j,3,Vec_MoneyInfo[i].Kinds);
	            	pDlg->m_list.SetItemText(j,4,Vec_MoneyInfo[i].Value);
		        	pDlg->m_list.SetItemText(j,5,Vec_MoneyInfo[i].Ver);
	          		pDlg->m_list.SetItemText(j,6,Vec_MoneyInfo[i].time);
	        		pDlg->m_list.SetItemText(j,7,Vec_MoneyInfo[i].MachineSNo);
				    j++;
				   }
				   }
			}
				   break;
		

		}
			       

}
