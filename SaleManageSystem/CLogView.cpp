// CLogView.cpp: 实现文件
//

#include "pch.h"
#include "SaleManageSystem.h"
#include "CLogView.h"


// CLogView

IMPLEMENT_DYNCREATE(CLogView, CFormView)

CLogView::CLogView()
	: CFormView(IDD_DIALOG_LOG)
{

}

CLogView::~CLogView()
{
}

void CLogView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLogView, CFormView)
END_MESSAGE_MAP()


// CLogView 诊断

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLogView 消息处理程序
