// VideoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1002观众端.h"
#include "VideoDlg.h"
#include "afxdialogex.h"
#include"DlgMain.h"




// CVideoDlg 对话框

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVideoDlg::IDD, pParent)
	, m_bDesktop(FALSE)
	, m_bCamera(FALSE)
	, m_bAudio(FALSE)
	, m_yule(0)
	, m_chibo(0)
	, m_jianshen(0)
	, m_other(0)
	, m_edtTitle(_T(""))
{
	m_flag = 0;
}

CVideoDlg::~CVideoDlg()
{
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Check(pDX, IDC_DESKTOP, m_bDesktop);
	DDX_Check(pDX, IDC_CAMERA, m_bCamera);
	DDX_Check(pDX, IDC_AUDIO, m_bAudio);
	DDX_Text(pDX, IDC_EDIT2, m_edtTitle);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CVideoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CVideoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CVideoDlg::OnBnClickedButton3)
	ON_MESSAGE(UM_SENDVIDEOINFO,&CVideoDlg::RecvVideoInfo)
	ON_BN_CLICKED(IDC_BUTTON4, &CVideoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_RADIO2, &CVideoDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CVideoDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CVideoDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO1, &CVideoDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON5, &CVideoDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CVideoDlg 消息处理程序
//接收视频消息
LRESULT CVideoDlg::RecvVideoInfo(WPARAM W,LPARAM L)
{
	char *szPath = (char*)W;
	char *szFileName = (char*)L;

	strcpy_s(m_videoPath,sizeof(m_videoPath),szPath);
	strcpy_s(m_videoName,sizeof(m_videoName),szFileName);
	return 0;
}
//设置参数
void CVideoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_ffmpeg.Factory(m_bDesktop,m_bCamera,m_bAudio);
}

//开始录制
void CVideoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData();
	m_ffmpeg.SetStart(m_bDesktop,m_bCamera,m_bAudio);
}

//停止录制
void CVideoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ffmpeg.SetStop(m_bDesktop,m_bCamera,m_bAudio);
}


//上传按钮
void CVideoDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	flag = 1;
	char *m_videoType = NULL; 
	WideCharToMultiByte(CP_ACP,0,m_edtTitle,-1,m_videoszTitle,sizeof(m_videoszTitle),0,0);
	switch(m_flag)
	{
	case 1:
		m_videoType = "小学";
		break;
	case 2:
		m_videoType = "中学";
		break;
	case 3:
		m_videoType = "高中";
		break;
	case 4:
		m_videoType = "其他";
		break;
	}
	theApp.m_pKernel->SendFileData(m_videoPath,m_videoName,m_videoszTitle,m_videoType,flag);
}

void CVideoDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_flag = 1;
}


void CVideoDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_flag = 2;
}


void CVideoDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_flag = 3;
}


void CVideoDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_flag = 4;
}

//查看视频按钮
void CVideoDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd = &CDlgMain::dlg;
	theApp.m_pMainWnd->PostMessage(UM_WATCHVIDEO);
}


