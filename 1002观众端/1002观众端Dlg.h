
// 1002���ڶ�Dlg.h : ͷ�ļ�
//

#pragma once


// CMy1002���ڶ�Dlg �Ի���
class CMy1002���ڶ�Dlg : public CDialogEx
{
// ����
public:
	CMy1002���ڶ�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY1002_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_userid;
	//CString  m_userid;
	CString m_username;
	/*afx_msg void OnEnChangeEdit3();*/
	CString m_userpassword;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	LRESULT LoginMsg(WPARAM W,LPARAM L);
	afx_msg void OnBnClickedButton3();
};
