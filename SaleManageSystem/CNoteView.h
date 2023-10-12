#pragma once



// CNoteView 窗体视图

class CNoteView : public CFormView
{
	DECLARE_DYNCREATE(CNoteView)

protected:
	CNoteView();           // 动态创建所使用的受保护的构造函数
	virtual ~CNoteView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NOTE };
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
//	COleDateTime m_date1;
//	COleDateTime m_date2;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonAck();
//	CDateTimeCtrl m_date;
	CDateTimeCtrl m_dt1;
	CDateTimeCtrl m_dt2;
	afx_msg void OnItemactivateList(NMHDR* pNMHDR, LRESULT* pResult);
};


