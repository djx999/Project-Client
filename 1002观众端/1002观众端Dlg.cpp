
// 1002观众端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1002观众端.h"
#include "1002观众端Dlg.h"
#include "afxdialogex.h"
#include"DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CMy1002观众端Dlg 对话框



CMy1002观众端Dlg::CMy1002观众端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy1002观众端Dlg::IDD, pParent)
	, m_userid(1)
	, m_username(_T("1"))
	, m_userpassword(_T("1"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1002观众端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userid);
	DDX_Text(pDX, IDC_EDIT2, m_username);
	DDX_Text(pDX, IDC_EDIT3, m_userpassword);
}

BEGIN_MESSAGE_MAP(CMy1002观众端Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_EDIT3, &CMy1002观众端Dlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy1002观众端Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy1002观众端Dlg::OnBnClickedButton2)
	ON_MESSAGE(UM_LOGINMSG,&CMy1002观众端Dlg::LoginMsg)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy1002观众端Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMy1002观众端Dlg 消息处理程序

BOOL CMy1002观众端Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	theApp.m_pKernel->Open();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy1002观众端Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy1002观众端Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy1002观众端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CMy1002观众端Dlg::OnEnChangeEdit3()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//#1015
//
//	// TODO:  在此添加控件通知处理程序代码
//}


void CMy1002观众端Dlg::OnBnClickedButton1() //注册
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	STRU_REGISTER_RQ srr;
	srr.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
	srr.m_userid = m_userid;
	//WideCharToMultiByte(CP_ACP,0,m_userid,-1,srr.m_userid,sizeof(srr.m_userid),0,0);
	WideCharToMultiByte(CP_ACP,0,m_username,-1,srr.m_szName,sizeof(srr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_userpassword,-1,srr.m_szPassword,sizeof(srr.m_szPassword),0,0);

	
	theApp.m_pKernel->SendData((char*)&srr,sizeof(srr));


}
//登录按钮
void CMy1002观众端Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	STRU_LOGIN_RQ srr;
	srr.m_nType = _DEF_PROTOCOL_LOGIN_RQ;
	srr.m_userid = m_userid;
	WideCharToMultiByte(CP_ACP,0,m_username,-1,srr.m_szName,sizeof(srr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_userpassword,-1,srr.m_szPassword,sizeof(srr.m_szPassword),0,0);

	theApp.m_pKernel->SendData((char*)&srr,sizeof(srr));

}
LRESULT CMy1002观众端Dlg::LoginMsg(WPARAM W,LPARAM L )//改
{
	UpdateData(TRUE);
	/*CDlgMain dlg;*/
	CDlgMain::dlg.m_userid = m_userid;
	theApp.m_pMainWnd = &CDlgMain::dlg;
	EndDialog(IDOK);
	CDlgMain::dlg.DoModal();  //弹出新对话框
	

	return 0;
}

void CMy1002观众端Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

}
