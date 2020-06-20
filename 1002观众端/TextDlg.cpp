// TextDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1002���ڶ�.h"
#include "TextDlg.h"
#include "afxdialogex.h"
#include"DlgMain.h"


// CTextDlg �Ի���

IMPLEMENT_DYNAMIC(CTextDlg, CDialogEx)

CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextDlg::IDD, pParent)
	, m_textTitle(_T(""))
	, m_yule(0)
	, m_chibo(0)
	, m_jianshen(0)
	, m_qita(0)
{
	/*m_shellTree.Expand(m_shellTree.GetRootItem(), TVE_EXPAND);
	m_shellTree.SetRelatedList(&m_shellList);
	m_shellList.EnableShellContextMenu(FALSE);*/
}

CTextDlg::~CTextDlg()
{
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCSHELLLIST1, m_shellList);
	DDX_Text(pDX, IDC_EDIT1, m_textTitle);
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_MFCSHELLLIST1, &CTextDlg::OnNMRClickMfcshelllist1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTextDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &CTextDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CTextDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CTextDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CTextDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON2, &CTextDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTextDlg::OnBnClickedButton3)
	ON_MESSAGE(UM_UPLOADVIDEORS,&CTextDlg::uploadVideoRs)
END_MESSAGE_MAP()


// CTextDlg ��Ϣ�������
LRESULT CTextDlg::uploadVideoRs(WPARAM W,LPARAM L)
{
	AfxMessageBox(_T("insert fail"));
	return 0;
}

void CTextDlg::OnNMRClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	for(int i=0; i<m_shellList.GetItemCount(); i++)  
	{  
		if( m_shellList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )  
		{  
			m_shellList.GetItemPath(m_szpath,i);
			AfxMessageBox(m_szpath);  
		}  
	}  
	*pResult = 0;
}


//����
void CTextDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	WideCharToMultiByte(CP_ACP,0,m_szpath,-1,szpath,sizeof(szpath),0,0);
	WideCharToMultiByte(CP_ACP,0,m_textTitle,-1,textTitle,sizeof(textTitle),0,0);
	char *temp = szpath;
	while(*temp++ != '\0');
	while(*--temp != '\\');
	++temp;
	szname = temp;
	
}


void CTextDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	flag = 1;
}


void CTextDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	flag =2;
}


void CTextDlg::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	flag = 3;
}


void CTextDlg::OnBnClickedRadio4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	flag = 4;
}

//���Ͱ�ť
void CTextDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	n=2;
	char *m_videoType = NULL; 
	switch(flag)
	{
	case 1:
		m_videoType = "Сѧ";
		break;
	case 2:
		m_videoType = "��ѧ";
		break;
	case 3:
		m_videoType = "����";
		break;
	case 4:
		m_videoType = "����";
		break;
	}
	theApp.m_pKernel->SendFileData(szpath,szname,textTitle,m_videoType,n);  
}


void CTextDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd = &CDlgMain::dlg;
	theApp.m_pMainWnd->PostMessage(UM_WATCHVIDEO);
}
