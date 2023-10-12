#pragma once


// CLogin 对话框

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_pwd;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCheckPwd();
	BOOL m_checkpwd;
	virtual BOOL OnInitDialog();
	CString m_pwd2;
	afx_msg void OnBnClickedButtonReset();
};
