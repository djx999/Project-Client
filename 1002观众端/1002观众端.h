
// 1002���ڶ�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include"TCPKernel.h"


// CMy1002���ڶ�App:
// �йش����ʵ�֣������ 1002���ڶ�.cpp
//

class CMy1002���ڶ�App : public CWinApp
{
public:
	CMy1002���ڶ�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	IKernel *m_pKernel;
	virtual int ExitInstance();
};

extern CMy1002���ڶ�App theApp;