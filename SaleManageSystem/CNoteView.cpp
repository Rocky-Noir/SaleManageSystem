// CNoteView.cpp: 实现文件
//

#include "pch.h"
#include "SaleManageSystem.h"
#include "CNoteView.h"
#include "InfoFile.h"


// CNoteView

IMPLEMENT_DYNCREATE(CNoteView, CFormView)

CNoteView::CNoteView()
	: CFormView(IDD_DIALOG_NOTE)
	, m_name(_T(""))
{

}

CNoteView::~CNoteView()
{
}

void CNoteView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_COMBO, m_com);
	DDX_CBString(pDX, IDC_COMBO, m_name);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dt1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dt2);
}

BEGIN_MESSAGE_MAP(CNoteView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_ACK, &CNoteView::OnBnClickedButtonAck)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST1, &CNoteView::OnItemactivateList)
END_MESSAGE_MAP()


// CNoteView 诊断

#ifdef _DEBUG
void CNoteView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CNoteView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CNoteView 消息处理程序


void CNoteView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;

	int idx = m_com.AddString(TEXT("全部商品"));
	m_com.SetItemData(idx, 0);

	for (it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_name = it->name;
		int idx = m_com.AddString(m_name);
		m_com.SetItemData(idx, it->id);
	}

	if (file.ls.size() > 0)
		m_com.SetCurSel(0);

	m_list.InsertColumn(0, TEXT("单号"));
	m_list.InsertColumn(1, TEXT("商品"));
	m_list.InsertColumn(2, TEXT("价格"));
	m_list.InsertColumn(3, TEXT("数量"));
	m_list.InsertColumn(4, TEXT("总价"));
	m_list.InsertColumn(5, TEXT("日期"));

	m_list.SetColumnWidth(0, 42);//设置列宽
	m_list.SetColumnWidth(1, 50);
	m_list.SetColumnWidth(2, 42);
	m_list.SetColumnWidth(3, 42);
	m_list.SetColumnWidth(4, 42);
	m_list.SetColumnWidth(5, 80);
	
	file.Readlist();
	list<msg2>::iterator it2;
	CString str;

	for (it2 = file.ls2.begin(); it2 != file.ls2.end(); it2++)
	{
		int cnt = m_list.GetItemCount();

		str.Format(TEXT("%d"), it2->id);
		m_list.InsertItem(cnt, str);

		m_list.SetItemText(cnt, 1, it2->name);

		str.Format(TEXT("%d"), it2->price);
		m_list.SetItemText(cnt, 2, str);
		str.Format(TEXT("%d"), it2->num);
		m_list.SetItemText(cnt, 3, str);
		str.Format(TEXT("%d"), it2->total);
		m_list.SetItemText(cnt, 4, str);
		m_list.SetItemText(cnt, 5, it2->date);
	}
}


void CNoteView::OnBnClickedButtonAck()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	CTime tm1, tm2;
	m_dt1.GetTime(tm1);
	m_dt2.GetTime(tm2);

	CInfoFile file;
	file.Chelist(m_name, tm1.Format("%Y/%m/%d"), tm2.Format("%Y/%m/%d"));

	list<msg2>::iterator it2;
	CString str;

	m_list.DeleteAllItems();

	for (it2 = file.ls2.begin(); it2 != file.ls2.end(); it2++)
	{
		int cnt = m_list.GetItemCount();

		str.Format(TEXT("%d"), it2->id);
		m_list.InsertItem(cnt, str);
		m_list.SetItemText(cnt, 1, it2->name);
		str.Format(TEXT("%d"), it2->price);
		m_list.SetItemText(cnt, 2, str);
		str.Format(TEXT("%d"), it2->num);
		m_list.SetItemText(cnt, 3, str);
		str.Format(TEXT("%d"), it2->total);
		m_list.SetItemText(cnt, 4, str);
		m_list.SetItemText(cnt, 5, it2->date);
	}
}


void CNoteView::OnItemactivateList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CInfoFile file;
	file.Readlist();
	list<msg2>::iterator it2;

	for (it2 = file.ls2.begin(); it2 != file.ls2.end(); it2++)
		if (it2->id == pNMIA->iItem + 1)
			m_name = it2->name;

	UpdateData(false);

	*pResult = 0;
}
