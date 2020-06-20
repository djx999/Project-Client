#ifndef  _INET_H
#define _INET_H

#include <Winsock2.h>
#include <process.h>
#include <list>

#include<mstcpip.h>  //����
#pragma comment(lib,"Ws2_32.lib")

#define _DEFPORT    8000


class INet
{
public:
	INet(){}
	virtual ~INet(){}
public:
	virtual bool InitNetWork() = 0;
	virtual void UnInitNetWork() = 0;
	virtual bool SendData(char* szbuf,int nlen) = 0;

	
};


#endif
