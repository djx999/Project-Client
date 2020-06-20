#include "stdafx.h"
#include "TCPKernel.h"
#include "TCPNet.h"
#include "1002观众端.h"
#include"DlgMain.h"
#include"1002观众端Dlg.h"
#include"VideoDlg.h"
#include"TextDlg.h"



TCPKernel::TCPKernel()
{
	m_pNet = new TCPNet(this);
	offset = 0;
	m_VideoName = "";
	nVideoLen = 0;
	pFile = NULL;
	m_downloadSize = 0;
	m_pLoadFile = NULL;
	m_loadPos = 0;
}

TCPKernel::~TCPKernel()
{
	if(m_pNet)
	{
		delete m_pNet;
		m_pNet = NULL;
	}
}

ProtocolMap m_ProtocolMapEntries[] = 
{
	{_DEF_PROTOCOL_REGISTER_RS,&TCPKernel::RegisterRs},
	{_DEF_PROTOCOL_LOGIN_RS,&TCPKernel::LoginRs},
	{_DEF_PROTOCOL_UPLOADVIDEO_RQ,&TCPKernel::RecvVideoRq},
	{_DEF_PROTOCOL_UPLOADVIDEOINFO,&TCPKernel::RecvVideoContent},
	{_DEF_PROTOCOL_VEDIO_RS,&TCPKernel::UploadVideoRs},
	{_DEF_PROTOCOL_DOWNLOADSIZE,&TCPKernel::RecvDownloadSize},
	{_DEF_PROTOCOL_CONTENT,&TCPKernel::RecvContent},
	{0,0}
};
//接收服务器发过来的内容
void TCPKernel::RecvContent(char *szbuf)
{
	fopen_s(&m_pLoadFile,m_loadFilePath,"ab+");
	STRU_CONTENT *scl = (STRU_CONTENT*)szbuf;
	int nReadReadNum;
	nReadReadNum = fwrite(scl->m_nContent,sizeof(char),scl->m_nSize,m_pLoadFile);
	m_loadPos+=nReadReadNum;
	if(m_loadPos != m_downloadSize)
	{
		fclose(m_pLoadFile);
		if(((CDlgMain*)theApp.m_pMainWnd)->m_isLoadFlag == 0) 
		{
			//向服务器发送要接收内容请求
			STRU_FILECONTENT sss;
			sss.m_nType = _DEF_PROTOCOL_DOWNLOADCONTENT;
			sss.m_uid = DLG->m_userid;
			m_pNet->SendData((char*)&sss,sizeof(sss));
		}
		else
		{
			theApp.m_pMainWnd->SendMessage(UM_LOADPOS,m_loadPos);
			return;
		}
	}
	else
	{
		fclose(m_pLoadFile);
		STRU_FILECONTENT sss;
		sss.m_nType = _DEF_PROTOCOL_DOWNLOADCONTENT;
		sss.m_uid = DLG->m_userid;
		m_pNet->SendData((char*)&sss,sizeof(sss));
		/*m_downloadSize = 0;
		m_loadPos = 0;*/
		return;
	}

}
//接收要下载文件的总大小
void TCPKernel::RecvDownloadSize(char *szbuf)
{
	STRU_FILESIZE *sfl = (STRU_FILESIZE*)szbuf;
	m_downloadSize = sfl->m_nFileSize;
	strcpy_s(m_loadFileName,sizeof(m_loadFileName),sfl->m_nFileName);
	//指定目录存文件
	strcpy_s(m_loadFilePath,"C:\\Users\\lenovo\\Desktop\\下载\\");
	strcat_s(m_loadFilePath,m_loadFileName);
	//向服务器发送要接收内容请求
	STRU_FILECONTENT sss;
	sss.m_nType = _DEF_PROTOCOL_DOWNLOADCONTENT;
	sss.m_uid = DLG->m_userid;
	m_pNet->SendData((char*)&sss,sizeof(sss));
}

//接收视频大小
void TCPKernel::RecvVideoRq(char* szbuf)
{
	STRU_UPLOAD_RQ *sur = (STRU_UPLOAD_RQ*)szbuf;
	m_videoPath = "C:\\Users\\lenovo\\Desktop\\Linux\\";
	nVideoLen = sur->m_VideoSize;
	m_VideoName = sur->m_VideoName;
	//char szpath[100];
	WideCharToMultiByte(CP_ACP,0,m_videoPath,-1,szpath,sizeof(szpath),0,0);
	strcat_s(szpath,sur->m_VideoName); 
	fopen_s(&pFile,szpath,"wb");
	//pFile = _wfsopen((const wchar_t*)szpath, _T("wb"), _SH_DENYRD);
	//pFile = _fsopen( szpath, "wb+", _SH_DENYNO);
	m_videoPath = m_videoPath+m_VideoName;
}
//接收视频内容
void TCPKernel::RecvVideoContent(char* szbuf)
{
	STRU_UPLOADINFO_RQ *svr = (STRU_UPLOADINFO_RQ*)szbuf;
	videoInfo vi;
	m_VideoLove = svr->m_VideoLove;
	strcpy_s(vi.videoType,sizeof(vi.videoType),svr->m_VideoType);
	strcpy_s(vi.videoTitle,sizeof(vi.videoTitle),svr->m_VideoTitle);
	vi.videoId= svr->m_VideoId;
	vi.videoCount = svr->m_VideoCount;
	int nRealReadNum;
	nRealReadNum = fwrite(svr->m_VideoContent,sizeof(char),svr->m_VideoSize,pFile);
	offset+=nRealReadNum;
	if(offset == nVideoLen)
	{
		fclose(pFile);
		pFile = NULL;
		offset = 0;
		nVideoLen = 0;
		//播放;
		m_queuest.push(m_videoPath);
		theApp.m_pMainWnd->SendMessage(UM_STREAM,m_VideoLove,(LPARAM)&vi);   //用postmessage不好使 第二个参数获取不到？
		return;
	}
}
void TCPKernel::RegisterRs(char* szbuf)
{
	STRU_REGISTER_RS *psrr = (STRU_REGISTER_RS*)szbuf;
	TCHAR *pSzResult = _T("register_fail");
	if(psrr->m_szResult == register_success)
		pSzResult = _T("register_success");

	AfxMessageBox(pSzResult);

}

void TCPKernel::LoginRs(char* szbuf)
{
	STRU_LOGIN_RS *psrr = (STRU_LOGIN_RS*)szbuf;
	TCHAR *pSzResult = _T("login_fail");
	if(psrr->m_szResult == login_success)
	{
		//向服务器发送观看视频请求
		STRU_WATCHVIDEO_RQ  swr;
		swr.m_nType = _DEF_PROTOCOL_WATCKVIDEO_RQ;
		swr.m_userid = ((CMy1002观众端Dlg*)(theApp.m_pMainWnd))->m_userid;
		swr.m_n = 0;   //一开始上来请求的是第一个
		theApp.m_pKernel->SendData((char*)&swr,sizeof(swr));

		//向窗口发送切换主窗口的消息
		theApp.m_pMainWnd->PostMessage(UM_LOGINMSG);
		return;
		/*char *path = "../shipin/hahaha.mp4";
		char *name = "hahaha.mp4";
		char *title = "111";
		char *type = "chi";
		int nflag = 2;*/
		//SendFileData(path,name,title,type,nflag);
	}


	AfxMessageBox(pSzResult);
}

void TCPKernel::UploadVideoRs(char* szbuf)
{
	STRU_VIDEOINFO_RS *sss = (STRU_VIDEOINFO_RS*)szbuf;
	char szResult[100] = {0};
	strcpy_s(szResult,sizeof(szResult),sss->m_szResult);
	if(strcmp(szResult,sss->m_szResult) == 0)
	{
		theApp.m_pMainWnd->SendMessage(UM_UPLOADVIDEORS);
	}
	else
	{
		return;
	}


}

bool TCPKernel::Open() 
{


	if(!m_pNet->InitNetWork())
		return false;


	return true;
}


void TCPKernel::Close()
{

	m_pNet->UnInitNetWork();

}


bool TCPKernel::DealData(char* szbuf)
{
	PackType *pType =(PackType*)szbuf;
	int i = 0;
	while(1)
	{
		if(m_ProtocolMapEntries[i].m_nType == *pType)
		{
			(this->*m_ProtocolMapEntries[i].m_npfun)(szbuf);
			break;
		}
		else if(m_ProtocolMapEntries[i].m_nType == 0 && m_ProtocolMapEntries[i].m_npfun  ==0)
			break;

		i++;
	}
	//处理协议包

	return true;
}


bool TCPKernel::SendData(char* szbuf,int nlen)
{
	if(!m_pNet->SendData(szbuf,nlen))
		return false;

	return true;
}

void TCPKernel::SendFileData(char*szpath,char *szFileName,char *szTitle,char* szType,int nflag)
{
	FILE *pFile = NULL;
	fopen_s(&pFile,szpath,"rb");
	if(pFile == NULL)
		return;
	fseek(pFile,0,SEEK_END);
	int nFileSize = ftell(pFile);
	fseek(pFile,0,SEEK_SET);

	//发送文件信息（文件大小）
	STRU_VIDEOINFO su;
	su.m_nType = _DEF_PROTOCOL_VEDIO;
	if(nflag == 0)
	{
		su.u_id = DLG->m_userid; //Modify
	}
	else if(nflag == 2)
	{
		su.u_id = TID->m_userid;
		//su.u_id  = 1;
	}
	else
	{
		su.u_id = VID->m_userid;
	}
	su.m_nVedioLen = nFileSize;
	/*strcpy_s(su.m_szTitle,sizeof(su.m_szTitle),szTitle);
	strcpy_s(su.m_szType,sizeof(su.m_szType),szType);*/
	strcpy_s(su.m_szFilename,sizeof(su.m_szFilename),szFileName);
	//su.m_nLove = 0;
	m_pNet->SendData((char*)&su,sizeof(su));
	//发送文件内容
	//读文件内容并发送
	STRU_VIDEOINFO_RQ sv;
	while(1)
	{
		sv.m_nType = _DEF_PROTOCOL_VEDIO_RQ;
		//sv.u_id = ((CVideoDlg*)theApp.m_pMainWnd)->m_userid; //Modify
		if(nflag == 0)
		{
			sv.u_id = DLG->m_userid; //Modify
		}
		else if(nflag == 2)
		{
			sv.u_id = TID->m_userid;
			//sv.u_id = 1;
		}
		else
		{
			sv.u_id = VID->m_userid;
		}
		strcpy_s(sv.m_szFilename,sizeof(sv.m_szFilename),szFileName);
		strcpy_s(sv.m_szTitle,sizeof(sv.m_szTitle),szTitle);
		strcpy_s(sv.m_szType,sizeof(sv.m_szType),szType);
		sv.m_nLove = 0;
		sv.m_nVedioLen = fread_s(sv.m_szContent,sizeof(sv.m_szContent),sizeof(char),sizeof(sv.m_szContent),pFile);
		if(sv.m_nVedioLen==0)
		{
			break;
		}
		m_pNet->SendData((char*)&sv,sizeof(sv));

	}


	fclose(pFile);

}