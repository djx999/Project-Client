
#ifndef  _TCPKERNEL_H
#define _TCPKERNEL_H

#include "IKernel.h"
#include<queue>
#include "Packdef.h"
class TCPKernel;
typedef  void (TCPKernel::*PFUN)(char*);
struct ProtocolMap
{
	PackType m_nType;
	PFUN     m_npfun;
};

struct videoInfo
{
	char videoType[100];
	char videoTitle[100];
	int  videoId;
	int  videoCount;
};

class TCPKernel :public IKernel
{
public:
	TCPKernel();
	virtual ~TCPKernel();
public:
	 bool Open() ;
	 void Close();
	 bool DealData(char* szbuf);
	 bool SendData(char* szbuf,int nlen);
public:
	 void RegisterRs(char* szbuf);
	 void LoginRs(char* szbuf);
	 void GetAuthorListRs(char* szbuf); 
	 void RecvVideoRq(char* szbuf);
	 void RecvVideoContent(char* szbuf);
	 void UploadVideoRs(char *szbuf);
	 void RecvDownloadSize(char *szbuf);
	 void RecvContent(char *szbuf);
public:
	 void SendFileData(char*szpath,char *szFileName,char *szTitle,char* szType,int nflag);
public:
	int nVideoLen;  //收到的视频大小
	FILE *pFile;    //文件描述符
	int offset;
	CString m_VideoName;  //文件名
	std::queue<CString>m_queuest;
	int   m_VideoLove;
	CString  m_videoPath;
	char    szpath[100];
	int     m_downloadSize;  //要下载文件大小
	FILE    *m_pLoadFile;  //要下载的文件描述符
	char    m_loadFileName[1000];  //要下载的文件名
	char    m_loadFilePath[1000];   //要存储得路径
	int     m_loadPos;      //下载的当前大小偏移量
};



#endif

