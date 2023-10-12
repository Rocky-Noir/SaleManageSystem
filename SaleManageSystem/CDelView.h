#pragma once



// CDelView 窗体视图

class CDelView : public CFormView
{
	DECLARE_DYNCREATE(CDelView)

protected:
	CDelView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDelView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEL };
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
	CSpinButtonCtrl m_sp;
	CSpinButtonCtrl m_sn;
	void OnCbnSelchangeCombo1();
	void OnCbnSelchangeCombo2();
	CComboBox m_com1;
	CComboBox m_com2;
	int m_pri1;
	int m_pri2;
	int m_num1;
	int m_num2;
	afx_msg void OnSelchangeComboName1();
	afx_msg void OnSelchangeComboName2();
	afx_msg void OnBnClickedButtonAck1();
	CString m_name1;
	CString m_name2;
	afx_msg void OnBnClickedButtonAck2();
	afx_msg void OnBnClickedButtonReset1();
};


