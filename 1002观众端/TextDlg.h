#pragma once
#include "afxshelllistctrl.h"


// CTextDlg �Ի���

class CTextDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDlg)

public:
	CTextDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTextDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMFCShellListCtrl m_shellList;
	afx_msg void OnNMRClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_szpath;
	afx_msg void OnBnClickedButton1();
	CString m_textTitle;
public:
	int m_userid;
	char szpath[1000]; //·��
	char textTitle[1000]; //����
	char *szname; //��
	int m_yule;
	int m_chibo;
	int m_jianshen;
	int m_qita;
	int flag;  //��ѡ��־
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedButton2();
	int n;//�Ƿ��л����־
	afx_msg void OnBnClickedButton3();
	LRESULT uploadVideoRs(WPARAM W,LPARAM L);
};
