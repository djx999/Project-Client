#pragma once
#include "afxwin.h"
#include"Myffmpeg.h"


// CVideoDlg �Ի���

class CVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoDlg)

public:
	CVideoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVideoDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture;
	BOOL m_bDesktop;
	BOOL m_bCamera;
	BOOL m_bAudio;
	Myffmpeg m_ffmpeg;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	int m_userid;
	CString m_username;
	afx_msg void OnBnClickedButton3();
	LRESULT RecvVideoInfo(WPARAM W,LPARAM L);
	char m_videoPath[100];
	char m_videoName[100];
	int m_yule;
	int m_chibo;
	int m_jianshen;
	int m_other;
	afx_msg void OnBnClickedButton4();

	int m_flag;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio1();
	CString m_edtTitle;
	char m_videoszTitle[100];
	int flag;   //�л������
	afx_msg void OnBnClickedButton5();
};
