// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "SaleManageSystem.h"
#include "CSelectView.h"
#include "MainFrm.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	m_tree = &GetTreeCtrl();

	m_imgList.Create(16, 16, ILC_COLOR32, 1, 1);

	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_USER);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_USER1);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_MNG);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_MNG1);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_IFM);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_IFM1);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_ADD);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_ADD1);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_DEL);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_DEL1);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_NOTE);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_NOTE1);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_LOG);
	m_imgList.Add(icon);
	icon = AfxGetApp()->LoadIconW(IDI_ICON_LOG1);
	m_imgList.Add(icon);

	m_tree->SetImageList(&m_imgList, TVSIL_NORMAL);

	m_tree->InsertItem(TEXT("个人信息"), 0, 1, NULL);
	m_tree->InsertItem(TEXT("销售管理"), 2, 3, NULL);
	m_tree->InsertItem(TEXT("销售记录"), 10, 11, NULL);
	m_tree->InsertItem(TEXT("库存信息"), 4, 5, NULL);
	m_tree->InsertItem(TEXT("库存添加"), 6, 7, NULL);
	m_tree->InsertItem(TEXT("库存删除"), 8, 9, NULL);
	//m_tree->InsertItem(TEXT("库存日志"), 12, 13, NULL);

	// TODO: 在此添加专用代码和/或调用基类
}


void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	m_tree = &GetTreeCtrl();
	HTREEITEM item = m_tree->GetSelectedItem();
	CString txt = m_tree->GetItemText(item);

	if (txt == "个人信息")
		::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_A, WU_A, 0);
	if (txt == "销售管理")
		::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_B, WU_B, 0);
	if (txt == "销售记录")
		::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_F, WU_F, 0);
	if (txt == "库存信息")
		::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_C, WU_C, 0);
	if (txt == "库存添加")
		::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_D, WU_D, 0);
	if (txt == "库存删除")
		::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_E, WU_E, 0);
	//if (txt == "库存日志")
	//	::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WU_G, WU_G, 0);

	*pResult = 0;
}
