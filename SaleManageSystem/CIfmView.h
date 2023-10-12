#pragma once



// CIfmView 窗体视图

class CIfmView : public CFormView
{
	DECLARE_DYNCREATE(CIfmView)

protected:
	CIfmView();           // 动态创建所使用的受保护的构造函数
	virtual ~CIfmView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IFM };
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
	CString m_name;
	int m_pri;
	int m_num;
	virtual void OnInitialUpdate();
	afx_msg void OnItemactivateList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonAck();
	void ListUpdata();
	int m_id;
};


