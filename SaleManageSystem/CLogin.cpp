// CLogin.cpp: 实现文件
//

#include "pch.h"
#include "SaleManageSystem.h"
#include "CLogin.h"
#include "afxdialogex.h"
#include "InfoFile.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_name(_T(""))
	, m_pwd(_T(""))
	, m_checkpwd(FALSE)
	, m_pwd2(_T(""))
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_PWD, m_pwd);
	DDX_Check(pDX, IDC_CHECK_PWD, m_checkpwd);
	DDX_Text(pDX, IDC_EDIT_PWD2, m_pwd2);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLogin::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_PWD, &CLogin::OnBnClickedCheckPwd)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CLogin::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CLogin 消息处理程序

void CLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	if (m_checkpwd == 1)
		m_pwd = m_pwd2;

	if (m_name.IsEmpty())
	{
		MessageBox(TEXT("用户名不能为空！"), TEXT("警告"), MB_ICONWARNING);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
		pedit->SetFocus();
		return;
	}
	if (m_pwd.IsEmpty())
	{
		MessageBox(TEXT("密码不能为空！"), TEXT("警告"), MB_ICONWARNING);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_PWD);
		pedit->SetFocus();
		return;
	}

	CInfoFile file;
	CString name, pwd;

	file.ReadLogin(name, pwd);
	if (m_name == name && m_pwd == pwd)
	{
		OnCancel();
	}
	else
	{
		MessageBox(TEXT("用户名或密码错误! "), TEXT("错误"), MB_ICONERROR);
		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_PWD);
		pedit->SetFocus();
	}
}


void CLogin::OnBnClickedCheckPwd()
{
	// 若在显示密码前打勾，则密码显示为明文，默认为密文（星号)
	UpdateData();

	CEdit* pedit1 = (CEdit*)GetDlgItem(IDC_EDIT_PWD);
	CEdit* pedit2 = (CEdit*)GetDlgItem(IDC_EDIT_PWD2);

	if (m_checkpwd == 1)
	{
		m_pwd2 = m_pwd;
		pedit1->ShowWindow(false);
		pedit2->ShowWindow(true);
	}
	else
	{
		m_pwd = m_pwd2;
		pedit2->ShowWindow(false);
		pedit1->ShowWindow(true);
	}
	UpdateData(false);
}


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	pedit->SetFocus();
	UpdateData();
	m_name = "admin";
	m_pwd = "123";
	UpdateData(false);
	return FALSE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLogin::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_name = "";
	m_pwd = "";
	m_pwd2 = "";
	UpdateData(false);

	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	pedit->SetFocus();
}


void CLogin::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CLogin::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
}


void CLogin::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(0);
}

