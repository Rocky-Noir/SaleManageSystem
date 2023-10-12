#pragma once



// CAddView 窗体视图

class CAddView : public CFormView
{
	DECLARE_DYNCREATE(CAddView)

protected:
	CAddView();           // 动态创建所使用的受保护的构造函数
	virtual ~CAddView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
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
	virtual void OnInitialUpdate();
	void OnCbnSelchangeCombo1();
	CComboBox m_com;
	int m_pri1;
  	int m_pri2;
	int m_num1;
	int m_num2;
	CString m_name2;
	afx_msg void OnBnClickedButtonAck();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnSelchangeCombo();
	CSpinButtonCtrl m_sp1;
	CSpinButtonCtrl m_sp2;
	CSpinButtonCtrl m_sn1;
	CSpinButtonCtrl m_sn2;
	CString m_name1;
	afx_msg void OnBnClickedButtonAck2();
	afx_msg void OnBnClickedButtonReset2();
};


