// CUserView.cpp: 实现文件
//

#include "pch.h"
#include "SaleManageSystem.h"
#include "CUserView.h"
#include "InfoFile.h"


// CUserView

IMPLEMENT_DYNCREATE(CUserView, CFormView)

CUserView::CUserView()
	: CFormView(IDD_DIALOG_USER)
	, m_user(_T(""))
	, m_id(_T(""))
	, m_opwd(_T(""))
	, m_npwd(_T(""))
	, m_npwdr(_T(""))
{

}

CUserView::~CUserView()
{
}

void CUserView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_OPWD, m_opwd);
	DDX_Text(pDX, IDC_EDIT_NPWD, m_npwd);
	DDX_Text(pDX, IDC_EDIT_NPWDR, m_npwdr);
}

BEGIN_MESSAGE_MAP(CUserView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_RESET2, &CUserView::OnBnClickedButtonReset2)
	ON_BN_CLICKED(IDOK, &CUserView::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserView 诊断

#ifdef _DEBUG
void CUserView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserView 消息处理程序


void CUserView::OnBnClickedButtonReset2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_opwd = "";
	m_npwd = "";
	m_npwdr = "";
	UpdateData(false);

	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_OPWD);
	pedit->SetFocus();
}


void CUserView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_user = TEXT("管理员");
	m_id = name;

	UpdateData(FALSE);
}


void CUserView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	if (m_opwd.IsEmpty())
	{
		MessageBox(TEXT("旧密码不能为空！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_OPWD);
		pedit->SetFocus();

		return;
	}
	if (m_npwd.IsEmpty())
	{
		MessageBox(TEXT("新密码不能为空！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NPWD);
		pedit->SetFocus();

		return;
	}
	if (m_npwdr.IsEmpty())
	{
		MessageBox(TEXT("确认密码不能为空！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NPWDR);
		pedit->SetFocus();

		return;
	}

	if (m_opwd != pwd)
	{
		MessageBox(TEXT("旧密码错误! "), TEXT("错误"), MB_ICONERROR);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NPWDR);
		pedit->SetFocus();

		return;
	}

	if (m_npwd != m_npwdr)
	{
		MessageBox(TEXT("新密码与确认密码不一致！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NPWDR);
		pedit->SetFocus();

		return;
	}

	if (m_opwd == m_npwd)
	{
		MessageBox(TEXT("新密码与旧密码不能相同！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NPWDR);
		pedit->SetFocus();

		return;
	}

	CStringA nname, npwd;
	nname = name;
	npwd = m_npwd;
	file.WritePwd(nname.GetBuffer(), npwd.GetBuffer());
	MessageBox(TEXT("修改成功！"), TEXT("提示"), MB_ICONASTERISK);

	m_opwd = "";
	m_npwd = "";
	m_npwdr = "";
	UpdateData(false);

	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_OPWD);
	pedit->SetFocus();
}
