
// 1002观众端Dlg.h : 头文件
//

#pragma once


// CMy1002观众端Dlg 对话框
class CMy1002观众端Dlg : public CDialogEx
{
// 构造
public:
	CMy1002观众端Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY1002_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
