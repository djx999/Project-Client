
// 1002���ڶ�Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1002���ڶ�.h"
#include "1002���ڶ�Dlg.h"
#include "afxdialogex.h"
#include"DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy1002���ڶ�Dlg �Ի���



CMy1002���ڶ�Dlg::CMy1002���ڶ�Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy1002���ڶ�Dlg::IDD, pParent)
	, m_userid(1)
	, m_username(_T("1"))
	, m_userpassword(_T("1"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1002���ڶ�Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userid);
	DDX_Text(pDX, IDC_EDIT2, m_username);
	DDX_Text(pDX, IDC_EDIT3, m_userpassword);
}

BEGIN_MESSAGE_MAP(CMy1002���ڶ�Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_EDIT3, &CMy1002���ڶ�Dlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy1002���ڶ�Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy1002���ڶ�Dlg::OnBnClickedButton2)
	ON_MESSAGE(UM_LOGINMSG,&CMy1002���ڶ�Dlg::LoginMsg)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy1002���ڶ�Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMy1002���ڶ�Dlg ��Ϣ�������

BOOL CMy1002���ڶ�Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	theApp.m_pKernel->Open();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy1002���ڶ�Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy1002���ڶ�Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy1002���ڶ�Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CMy1002���ڶ�Dlg::OnEnChangeEdit3()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//#1015
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}


void CMy1002���ڶ�Dlg::OnBnClickedButton1() //ע��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	STRU_REGISTER_RQ srr;
	srr.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
	srr.m_userid = m_userid;
	//WideCharToMultiByte(CP_ACP,0,m_userid,-1,srr.m_userid,sizeof(srr.m_userid),0,0);
	WideCharToMultiByte(CP_ACP,0,m_username,-1,srr.m_szName,sizeof(srr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_userpassword,-1,srr.m_szPassword,sizeof(srr.m_szPassword),0,0);

	
	theApp.m_pKernel->SendData((char*)&srr,sizeof(srr));


}
//��¼��ť
void CMy1002���ڶ�Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	STRU_LOGIN_RQ srr;
	srr.m_nType = _DEF_PROTOCOL_LOGIN_RQ;
	srr.m_userid = m_userid;
	WideCharToMultiByte(CP_ACP,0,m_username,-1,srr.m_szName,sizeof(srr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_userpassword,-1,srr.m_szPassword,sizeof(srr.m_szPassword),0,0);

	theApp.m_pKernel->SendData((char*)&srr,sizeof(srr));

}
LRESULT CMy1002���ڶ�Dlg::LoginMsg(WPARAM W,LPARAM L )//��
{
	UpdateData(TRUE);
	/*CDlgMain dlg;*/
	CDlgMain::dlg.m_userid = m_userid;
	theApp.m_pMainWnd = &CDlgMain::dlg;
	EndDialog(IDOK);
	CDlgMain::dlg.DoModal();  //�����¶Ի���
	

	return 0;
}

void CMy1002���ڶ�Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
