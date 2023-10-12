
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "SaleManageSystem.h"
#include "CSelectView.h"
#include "CUserView.h"
#include "CMngView.h"
#include "CIfmView.h"
#include "CAddView.h"
#include "CDelView.h"
#include "CNoteView.h"
#include "CLogView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(WU_A, OnMyChange)
	ON_MESSAGE(WU_B, OnMyChange)
	ON_MESSAGE(WU_C, OnMyChange)
	ON_MESSAGE(WU_D, OnMyChange)
	ON_MESSAGE(WU_E, OnMyChange)
	ON_MESSAGE(WU_F, OnMyChange)
	ON_MESSAGE(WU_G, OnMyChange)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	SetClassLong(*this, GCL_HICON, (long)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	CTime tm;
	tm = CTime::GetCurrentTime();
	CString str = tm.Format("%Y/%m/%d");
	SetTitle(str);

	MoveWindow(0, 0, 800, 600); 
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序
afx_msg LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext context;

	if (wParam == WU_A)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CUserView);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView *)m_sw.GetPane(0, 1);

		m_sw.DeleteView(0, 1);
		m_sw.CreateView(0, 1, RUNTIME_CLASS(CUserView), CSize(600, 550), &context);
		m_sw.RecalcLayout();
		
		CUserView *pNewView = (CUserView*)m_sw.GetPane(0, 1);
		pNewView->OnInitialUpdate();
		if (i == 0)
			i++;
		else
			m_sw.SetActivePane(0, 1);
	}
	else if (wParam == WU_B)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CMngView);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_sw.GetPane(0, 1);

		m_sw.DeleteView(0, 1);
		m_sw.CreateView(0, 1, RUNTIME_CLASS(CMngView), CSize(600, 550), &context);
		m_sw.RecalcLayout();

		CMngView* pNewView = (CMngView*)m_sw.GetPane(0, 1);
		pNewView->OnInitialUpdate();
		m_sw.SetActivePane(0, 1);
	}
	else if (wParam == WU_C)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CIfmView);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_sw.GetPane(0, 1);

		m_sw.DeleteView(0, 1);
		m_sw.CreateView(0, 1, RUNTIME_CLASS(CIfmView), CSize(600, 550), &context);
		m_sw.RecalcLayout();

		CIfmView* pNewView = (CIfmView*)m_sw.GetPane(0, 1);
		pNewView->OnInitialUpdate();
		m_sw.SetActivePane(0, 1);
	}
	else if (wParam == WU_D)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CAddView);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_sw.GetPane(0, 1);

		m_sw.DeleteView(0, 1);
		m_sw.CreateView(0, 1, RUNTIME_CLASS(CAddView), CSize(600, 550), &context);
		m_sw.RecalcLayout();

		CAddView* pNewView = (CAddView*)m_sw.GetPane(0, 1);
		pNewView->OnInitialUpdate();
		m_sw.SetActivePane(0, 1);
	}
	else if (wParam == WU_E)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CDelView);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_sw.GetPane(0, 1);

		m_sw.DeleteView(0, 1);
		m_sw.CreateView(0, 1, RUNTIME_CLASS(CDelView), CSize(600, 550), &context);
		m_sw.RecalcLayout();

		CDelView* pNewView = (CDelView*)m_sw.GetPane(0, 1);
		pNewView->OnInitialUpdate();
		m_sw.SetActivePane(0, 1);
	}
	else if (wParam == WU_F)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CNoteView);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_sw.GetPane(0, 1);

		m_sw.DeleteView(0, 1);
		m_sw.CreateView(0, 1, RUNTIME_CLASS(CNoteView), CSize(600, 550), &context);
		m_sw.RecalcLayout();

		CNoteView* pNewView = (CNoteView*)m_sw.GetPane(0, 1);
		pNewView->OnInitialUpdate();
		m_sw.SetActivePane(0, 1);
	}/*
	else if (wParam == WU_G)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CLogView);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_sw.GetPane(0, 1);

		m_sw.DeleteView(0, 1);
		m_sw.CreateView(0, 1, RUNTIME_CLASS(CLogView), CSize(600, 550), &context);
		m_sw.RecalcLayout();

		CLogView* pNewView = (CLogView*)m_sw.GetPane(0, 1);
		pNewView->OnInitialUpdate();
		m_sw.SetActivePane(0, 1);
	}*/

	return 0;
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	SetWindowPos(NULL, 0, 0, 800, 600, SWP_NOMOVE);
	m_sw.CreateStatic(this, 1, 2);
	m_sw.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(150, 600), pContext);
	m_sw.CreateView(0, 1, RUNTIME_CLASS(CUserView), CSize(650, 600), pContext);

	return TRUE;

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
