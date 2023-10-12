#pragma once



// CMngView 窗体视图

class CMngView : public CFormView
{
	DECLARE_DYNCREATE(CMngView)

protected:
	CMngView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMngView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MNG };
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
	CListCtrl m_list;
	CComboBox m_com;
	CString m_name;
	int m_pri;
	int m_spri;
	int m_num;
	int m_snum;
	CSpinButtonCtrl m_sp;
	CSpinButtonCtrl m_sn;
	virtual void OnInitialUpdate();
	void OnCbnSelchangeCombo1();
	afx_msg void OnSelchangeComboName();
	afx_msg void OnBnClickedButtonAck();
	afx_msg void OnBnClickedButtonReset();
};


