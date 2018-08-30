; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEXE3Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "EXE3.h"

ClassCount=4
Class1=CEXE3App
Class2=CEXE3Dlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_EXE3_DIALOG
Class4=CNewDialog
Resource4=IDD_DIALOG1

[CLS:CEXE3App]
Type=0
HeaderFile=EXE3.h
ImplementationFile=EXE3.cpp
Filter=N

[CLS:CEXE3Dlg]
Type=0
HeaderFile=EXE3Dlg.h
ImplementationFile=EXE3Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LINGCUN

[CLS:CAboutDlg]
Type=0
HeaderFile=EXE3Dlg.h
ImplementationFile=EXE3Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EXE3_DIALOG]
Type=1
Class=CEXE3Dlg
ControlCount=6
Control1=IDC_OPEN,button,1342242816
Control2=IDC_SEARCH,button,1342242816
Control3=IDC_LIST1,SysListView32,1350631425
Control4=IDC_GENGZHENG,button,1342242816
Control5=IDC_RESERVE,button,1342242816
Control6=IDC_LINGCUN,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=CNewDialog
ControlCount=7
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_EDIT3,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SEARCH1,button,1342242816

[CLS:CNewDialog]
Type=0
HeaderFile=NewDialog.h
ImplementationFile=NewDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SEARCH1

