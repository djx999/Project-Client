#pragma once
#include "afxshelllistctrl.h"


// CTextDlg 对话框

class CTextDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDlg)

public:
	CTextDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMFCShellListCtrl m_shellList;
	afx_msg void OnNMRClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_szpath;
	afx_msg void OnBnClickedButton1();
	CString m_textTitle;
public:
	int m_userid;
	char szpath[1000]; //路径
	char textTitle[1000]; //标题
	char *szname; //名
	int m_yule;
	int m_chibo;
	int m_jianshen;
	int m_qita;
	int flag;  //多选标志
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton2();
	int n;//是否切换类标志
	afx_msg void OnBnClickedButton3();
	LRESULT uploadVideoRs(WPARAM W,LPARAM L);
};
