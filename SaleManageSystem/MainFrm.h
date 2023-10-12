
// MainFrm.h: CMainFrame 类的接口
//

#pragma once
#define WU_A (WM_USER+100)
#define WU_B (WM_USER+101)
#define WU_C (WM_USER+102)
#define WU_D (WM_USER+103)
#define WU_E (WM_USER+104)
#define WU_F (WM_USER+105)
#define WU_G (WM_USER+106)

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnMyChange(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

public:
	CSplitterWnd m_sw;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	int i=0;
};


