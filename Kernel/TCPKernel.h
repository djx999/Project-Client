
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
	int nVideoLen;  //�յ�����Ƶ��С
	FILE *pFile;    //�ļ�������
	int offset;
	CString m_VideoName;  //�ļ���
	std::queue<CString>m_queuest;
	int   m_VideoLove;
	CString  m_videoPath;
	char    szpath[100];
	int     m_downloadSize;  //Ҫ�����ļ���С
	FILE    *m_pLoadFile;  //Ҫ���ص��ļ�������
	char    m_loadFileName[1000];  //Ҫ���ص��ļ���
	char    m_loadFilePath[1000];   //Ҫ�洢��·��
	int     m_loadPos;      //���صĵ�ǰ��Сƫ����
};



#endif

