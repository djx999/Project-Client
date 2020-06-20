#ifndef  _TCPNET_H
#define _TCPNET_H

#include"TCPKernel.h"
#include"INet.h"
#include"IKernel.h"


enum NetType{NT_ACCEPT,NT_READ};
struct SockEx
{
	OVERLAPPED  m_olp; //�¼� -- ��֪ͨ��
	SOCKET      m_sock;
	NetType     m_Type;//�����¼�
	char        m_szbuffer[1024];
};
class TCPNet : public INet
{
public:
	TCPNet(IKernel *pKernel);  //ͨ������ָ��ķ�ʽ  �������������Kernel��ָ�� ����dealdata
	virtual ~TCPNet();
public:
	bool InitNetWork();
	void UnInitNetWork();
	bool SendData(SOCKET sock,char* szbuf,int nlen);
public:
	//static unsigned __stdcall ThreadAccept( void * lpvoid);
	//static  unsigned _stdcall ThreadRecv ( void * );
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);

private:
	SOCKET m_sockListen;
	std::list<HANDLE> m_lsthThreadRecv;
	HANDLE m_hThreadAccept;
	static bool   m_bFlagQuit;
	static IKernel *m_pKernel;
	HANDLE  m_Iocp;
	std::list<SockEx*> m_lstsock;
public:
	bool PostAccept();
	bool PostRecv(SockEx* pSock);
};
#endif

/*std::list<HANDLE> m_lsthThreadRecv;
	HANDLE m_hThreadAccept;
	static bool   m_bFlagQuit;*/
	/*HANDLE m_aryEvent[MAX_NUM];
	SOCKET m_arySocket[MAX_NUM];
	int m_nEventNum;*/