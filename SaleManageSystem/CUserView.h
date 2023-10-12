#pragma once



// CUserView 窗体视图

class CUserView : public CFormView
{
	DECLARE_DYNCREATE(CUserView)

protected:
	CUserView();           // 动态创建所使用的受保护的构造函数
	virtual ~CUserView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_USER };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonReset2();
	CString m_user;
	CString m_id;
	CString m_opwd;
	CString m_npwd;
	CString m_npwdr;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedOk();
};


