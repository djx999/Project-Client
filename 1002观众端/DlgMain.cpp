// DlgMain.cpp : 实现文件
//

#include "stdafx.h"
#include "1002观众端.h"
#include "DlgMain.h"
#include "afxdialogex.h"
#include"TCPKernel.h"
#include"VideoDlg.h"
#include"TextDlg.h"


// CDlgMain 对话框
CDlgMain CDlgMain::dlg = NULL;
IMPLEMENT_DYNAMIC(CDlgMain, CDialogEx)

	CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMain::IDD, pParent)
	, m_edtLoveNum(0)
	, m_edtTitle(_T(""))
	, m_edtType(_T(""))
{
	m_userid = 0;
	m_username = _T("");
	title = _T("");
	type = _T("");
	m_isLoadFlag = 0;
}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OCX1, m_player);
	DDX_Text(pDX, IDC_EDIT1, m_edtLoveNum);
	DDX_Text(pDX, IDC_EDIT2, m_edtTitle);
	DDX_Text(pDX, IDC_EDIT3, m_edtType);
}


BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgMain::OnBnClickedButton1)
	ON_MESSAGE(UM_STREAM,&CDlgMain::OpenVideo)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgMain::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgMain::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgMain::OnBnClickedButton4)
	ON_MESSAGE(UM_WATCHVIDEO,&CDlgMain::WatchVideo)
	ON_EN_CHANGE(IDC_EDIT1, &CDlgMain::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgMain::OnBnClickedButton5)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgMain::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgMain::OnBnClickedButton7)
	ON_MESSAGE(UM_LOADPOS,&CDlgMain::OnLoadPos)
END_MESSAGE_MAP()


// CDlgMain 消息处理程序
LRESULT CDlgMain::OnLoadPos(WPARAM W,LPARAM L)
{
	m_loadPos = (int)W;
	
	return 0;
}
LRESULT CDlgMain::WatchVideo(WPARAM W,LPARAM L)
{
	this->ShowWindow(SW_SHOW);
	m_controls.play();
	return 0;
}

LRESULT CDlgMain::OpenVideo(WPARAM W,LPARAM L)
{
	videoInfo *vi = (videoInfo*)L;
	CString str1 = NULL;
	type = vi->videoType;
	title = vi->videoTitle;
	id = vi->videoId;
	count = vi->videoCount;
	m_edtLoveNum = W;
	str1.Format(_T("%d"),m_edtLoveNum);
	GetDlgItem(IDC_EDIT2)->SetWindowText(title);
	GetDlgItem(IDC_EDIT3)->SetWindowText(type);
	GetDlgItem(IDC_EDIT1)->SetWindowText(str1);
	CString str = ((TCPKernel*)theApp.m_pKernel)->m_queuest.front();
	((TCPKernel*)theApp.m_pKernel)->m_queuest.pop();
	m_setting = m_player.get_settings();
	m_setting.put_playCount(200);
	m_player.put_URL(str);
	m_controls=static_cast<CWMPControls>(m_player.get_controls());

	return 0;

}

//上传按钮
void CDlgMain::OnBnClickedButton1()
{
	UpdateData();
	m_controls.pause();
	CTextDlg dlg;
	dlg.m_userid = m_userid;
	this ->ShowWindow(SW_HIDE);
	theApp.m_pMainWnd = &dlg;
	dlg.DoModal();
	//EndDialog(IDOK);

}



//点击上一个按钮
void CDlgMain::OnBnClickedButton2()
{
	UpdateData();
	if(id == 1)
	{
		MessageBox(_T("已经是第一个了"));
		return;
	}
	STRU_WATCHVIDEO_RQ  swr;
	swr.m_nType = _DEF_PROTOCOL_WATCKVIDEO_RQ;
	swr.m_n = 1;
	theApp.m_pKernel->SendData((char*)&swr,sizeof(swr));
}

//点击下一个按钮
void CDlgMain::OnBnClickedButton3()
{
	UpdateData();
	if(id == count)
	{
		MessageBox(_T("已经是最后一个了"));
		return;
	}
	STRU_WATCHVIDEO_RQ  swr;
	swr.m_nType = _DEF_PROTOCOL_WATCKVIDEO_RQ;
	swr.m_n  = 2;
	theApp.m_pKernel->SendData((char*)&swr,sizeof(swr));
}

//录制上传按钮
void CDlgMain::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_player.close();
	m_controls.pause();
	CVideoDlg dlg;
	dlg.m_userid = m_userid;
	theApp.m_pMainWnd = &dlg;
	this ->ShowWindow(SW_HIDE);
	dlg.DoModal();
	EndDialog(IDOK);

}


void CDlgMain::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
}


void CDlgMain::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edtLoveNum++;
	//向服务器发送
	STRU_LOVENUM sl;
	sl.m_nType = _DEF_PROTOCOL_ADDLOVENUM;
	sl.m_videoId = id;
	sl.m_videoLove = m_edtLoveNum;
	theApp.m_pKernel->SendData((char*)&sl,sizeof(sl));

	CString str1 = NULL;
	str1.Format(_T("%d"),m_edtLoveNum);
	GetDlgItem(IDC_EDIT1)->SetWindowText(str1);

}


void CDlgMain::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	dlg.CloseWindow();
	CDialogEx::OnClose();
	exit(0);
}

//开始下载视频
void CDlgMain::OnBnClickedButton6()
{
	STRU_LoadRq   sdl;
	sdl.m_nType = _DEF_PROTOCOL_DOWNLOADINFO;
	sdl.m_uid = m_userid;
	sdl.m_vid = id;
	/*sdl.m_bflag1 = true;*/
	if(m_isLoadFlag == 0)
	{
		sdl.m_Flag = 0;
		sdl.m_loadPos = 0;
	}
	else
	{
		sdl.m_Flag = 1;
		sdl.m_loadPos = m_loadPos;
	}
	m_isLoadFlag = 0;
	theApp.m_pKernel->SendData((char*)&sdl,sizeof(sdl));

}

//暂停下载按钮
void CDlgMain::OnBnClickedButton7()
{
	//判断文件大小  是否下载完 
	//修改下载标记
	m_isLoadFlag = 1; //断点续传
}
