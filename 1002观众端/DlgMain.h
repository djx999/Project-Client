#pragma once
#include "cwmpplayer4.h"
#include"CWMPSettings.h"
#include"CWMPControls.h"

// CDlgMain 对话框

class CDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMain();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int     m_userid;
	CString m_username;
	afx_msg void OnBnClickedButton1();
	CWMPPlayer4 m_player;
	LRESULT OpenVideo(WPARAM W,LPARAM L);
	CWMPSettings  m_setting;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	static CDlgMain dlg;
	LRESULT WatchVideo(WPARAM W,LPARAM L);
	CWMPControls m_controls;
	int m_edtLoveNum;
	CString m_edtTitle;
	CString m_edtType;
	CString title;
	CString type;
	int     id;  //视频id
	int     count;//视频数
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	int    m_isLoadFlag;  //下载标记
	int    m_loadPos;//下载偏移量
	LRESULT OnLoadPos(WPARAM W,LPARAM L);
};
