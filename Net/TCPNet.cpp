
#include "TCPNet.h"
#include<Mswsock.h>

bool  TCPNet::m_bFlagQuit = true;
IKernel* TCPNet::m_pKernel = NULL;
TCPNet::TCPNet(IKernel *pKernel)
{
	m_sockListen = NULL;
	m_pKernel = pKernel;

}


TCPNet::~TCPNet(void)
{
}
bool TCPNet::InitNetWork()
{
	//1.选择种类 -- 
	 WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
       // printf("WSAStartup failed with error: %d\n", err);
        return false;
    }


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
       // printf("Could not find a usable version of Winsock.dll\n");
        UnInitNetWork();
        return false;
    }
   
        

	//2.雇佣店长 -- socket 
	m_sockListen = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,WSA_FLAG_OVERLAPPED );
	if(m_sockListen == INVALID_SOCKET )
	{
		UnInitNetWork();
		 return false;
	}
	//3.选址 --- 
	sockaddr_in  addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY/*inet_addr("192.168.3.1")*/;
	addrServer.sin_port = htons(_DEFPORT);
	if(SOCKET_ERROR ==bind(m_sockListen,(const sockaddr*)&addrServer,sizeof(addrServer)))
	{
		 UnInitNetWork();
		 return false;
	}
	//4.店长发宣传 -- 
	if(SOCKET_ERROR  == listen(m_sockListen,20))
	{
		 UnInitNetWork();
		 return false;

	}
	//创建完成端口
	m_Iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,0);
	if(m_Iocp == NULL)
	{
		 UnInitNetWork();
		 return false;
	}
	//将监听socket交给完成端口管理
	CreateIoCompletionPort((HANDLE)m_sockListen,m_Iocp,m_sockListen,NULL);

	//创建n个sockwaiter
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for(int i=0;i<si.dwNumberOfProcessors*2;i++)
	{
		//调用postaccept
		if(!PostAccept())
			continue;
	}

	//创建线程池
	QueueUserWorkItem(&ThreadProc,this,WT_EXECUTELONGFUNCTION);
	//m_hThreadAccept = (HANDLE)_beginthreadex(NULL,0,&ThreadAccept,this,0,0);  //接收客户端连接
	
	return true;
}
bool TCPNet::PostAccept()
{
	SockEx *pSock = new SockEx;
	pSock->m_Type = NT_ACCEPT;
	pSock->m_olp.hEvent = WSACreateEvent();
	pSock->m_sock =  WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,WSA_FLAG_OVERLAPPED );
	ZeroMemory(pSock->m_szbuffer,sizeof(pSock->m_szbuffer));
	DWORD dwNumberBytes;
	if(!AcceptEx(m_sockListen,pSock->m_sock,pSock->m_szbuffer,0,sizeof(sockaddr_in)+16,sizeof(sockaddr_in)+16,
		&dwNumberBytes,&pSock->m_olp))
	{
		if(WSAGetLastError() !=ERROR_IO_PENDING)
		{
			closesocket(pSock->m_sock);
			WSACloseEvent(pSock->m_olp.hEvent);
			delete pSock;
			pSock = NULL;
			return false;
		}
	}

	m_lstsock.push_back(pSock);
	return true;
}

bool TCPNet::PostRecv(SockEx* pSock)
{
	pSock->m_Type = NT_READ;
	WSABUF we;
	DWORD dwNumber;
	DWORD dflag = FALSE;
	we.buf = pSock->m_szbuffer;
	we.len = sizeof(pSock->m_szbuffer);
	if(WSARecv(pSock->m_sock,&we,1,&dwNumber,&dflag,&pSock->m_olp,NULL))
	{
		if(WSAGetLastError() != WSA_IO_PENDING )
		{
			return false;
		}
	}
	return true;
}
DWORD WINAPI TCPNet::ThreadProc(LPVOID lpvoid)
{
	TCPNet *pthis = (TCPNet*)lpvoid;
	DWORD dwNumberOfBytes;
	SOCKET sock;
	SockEx *pSock = NULL;
	bool bflag;
	while(pthis->m_bFlagQuit)
	{
		bflag = GetQueuedCompletionStatus(pthis->m_Iocp,&dwNumberOfBytes,(PULONG_PTR)&sock,(LPOVERLAPPED*)&pSock,INFINITE);
		if(!bflag)
			continue;


		if(pSock && sock)
		{
			switch (pSock->m_Type)
			{
			case NT_ACCEPT:
				{
					//1.将sockwaiter交给完成端口管理
					CreateIoCompletionPort((HANDLE)pSock->m_sock,pthis->m_Iocp,pSock->m_sock,0);
					//2.动态创建socket
					pthis->PostAccept();
					//3.
					pthis->PostRecv(pSock);
				}
				break;
			case NT_READ:
				{
					pthis->PostRecv(pSock);

					m_pKernel->DealData(pSock->m_sock,pSock->m_szbuffer);
				}
				break;
			default:
				break;
			}
		}
	}
	return 0;
}



void TCPNet::UnInitNetWork()
{
	m_bFlagQuit = false;
	if(m_hThreadAccept )
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(m_hThreadAccept,100))
			TerminateThread(m_hThreadAccept,-1);
		
		CloseHandle(m_hThreadAccept);
		m_hThreadAccept = NULL;

	
	}
	auto ite = m_lsthThreadRecv.begin();
	while(ite != m_lsthThreadRecv.end())
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(*ite,100))
		TerminateThread(*ite,-1);
		
		CloseHandle(*ite);
		*ite = NULL;
		ite++;
	}
	m_lsthThreadRecv.clear();
	WSACleanup();
	if(m_sockListen)
	{
		closesocket(m_sockListen);
		m_sockListen = NULL;
	}
}

bool TCPNet::SendData(SOCKET sock,char* szbuf,int nlen)
{
	if(send(sock,(char*)&nlen,sizeof(int),0)<0)
		return false;

	if(send(sock,szbuf,nlen,0)<0)
		return false;
	
	return true;
}