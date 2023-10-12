// CAddView.cpp: 实现文件
//

#include "pch.h"
#include "SaleManageSystem.h"
#include "CAddView.h"
#include "InfoFile.h"

using namespace std;
// CAddView

IMPLEMENT_DYNCREATE(CAddView, CFormView)

CAddView::CAddView()
	: CFormView(IDD_DIALOG_ADD)
	, m_pri1(0)
	, m_pri2(0)
	, m_num1(0)
	, m_num2(0)
	, m_name2(_T(""))
	, m_name1(_T(""))
{

}

CAddView::~CAddView()
{
}

void CAddView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_NAME, m_com);
	DDX_Text(pDX, IDC_EDIT_PRI1, m_pri1);
	DDX_Text(pDX, IDC_EDIT_PRI2, m_pri2);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_num1);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_num2);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name2);
	DDX_Control(pDX, IDC_SPIN_PRI1, m_sp1);
	DDX_Control(pDX, IDC_SPIN_PRI2, m_sp2);
	DDX_Control(pDX, IDC_SPIN_NUM1, m_sn1);
	DDX_Control(pDX, IDC_SPIN_NUM2, m_sn2);
	DDX_CBString(pDX, IDC_COMBO_NAME, m_name1);
}

BEGIN_MESSAGE_MAP(CAddView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_ACK1, &CAddView::OnBnClickedButtonAck)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CAddView::OnBnClickedButtonReset)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME, &CAddView::OnSelchangeCombo)
	ON_BN_CLICKED(IDC_BUTTON_ACK2, &CAddView::OnBnClickedButtonAck2)
	ON_BN_CLICKED(IDC_BUTTON_RESET2, &CAddView::OnBnClickedButtonReset2)
END_MESSAGE_MAP()


// CAddView 诊断

#ifdef _DEBUG
void CAddView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddView 消息处理程序


void CAddView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	m_name2 = "";
	m_pri2 = 0;
	m_num2 = 0;

	UpdateData(false);

	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;
	
	for (it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_name1 = it->name;
		int idx = m_com.AddString(m_name1);
		m_com.SetItemData(idx, it->id);
	}

	if (file.ls.size() > 0)
		m_com.SetCurSel(0);

	OnCbnSelchangeCombo1();

	m_sp1.SetRange(0, 32767);
	m_sp2.SetRange(0, 32767);
	m_sn1.SetRange(0, 32767);
	m_sn2.SetRange(0, 32767);
}

void CAddView::OnCbnSelchangeCombo1()
{
	UpdateData();

	int index = m_com.GetCurSel();
	int id = m_com.GetItemData(index);

	CInfoFile file;
	file.Readline();

	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
		if (it->id == id)
		{
			m_pri1 = it->price;
			m_num1 = it->num;
			break;
		}

	UpdateData(false);
}

void CAddView::OnBnClickedButtonAck()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(); 

	if (m_pri1 < 0)
	{
		MessageBox(TEXT("修改商品价格不能小于0！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_PRI1);
		pedit->SetFocus();

		return;
	}

	if (m_num1 < 0)
	{
		MessageBox(TEXT("添加商品数量不能小于0！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NUM1);
		pedit->SetFocus();

		return;
	}

	int index = m_com.GetCurSel();
	CString name;

	m_com.GetLBText(index, name);
	int id = m_com.GetItemData(index);

	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
		if (it->id == id)
		{
			if (it->price == m_pri1 && m_num1 == 0)
			{
				MessageBox(TEXT("无修改/添加！"), TEXT("警告"), MB_ICONWARNING);

				return;
			}

			CString str, str2;
			
			str = "请确认以下修改/添加信息：\n\n名    称：";
			str += m_name1;

			if (it->price != m_pri1)
			{
				str += "\n原 价 格：";
				str2.Format(TEXT("%d"), it->price);
				str += str2;

				str += "\n修改价格：";
				str2.Format(TEXT("%d"), m_pri1);
				str += str2;
			}

			if (m_num1 != 0)
			{
				str += "\n原 数 量：";
				str2.Format(TEXT("%d"), it->num);
				str += str2;

				str += "\n添加数量：";
				str2.Format(TEXT("%d"), m_num1);
				str += str2;
			}

			str += "\n\n确认无误？";

			int choice=MessageBox((CString)str, TEXT("提问"), MB_OKCANCEL|MB_ICONQUESTION);
			
			if(choice == IDOK)
			{ 
				it->price = m_pri1;
				it->num += m_num1;

				file.Updline(it->id, it->name, it->price, it->num);

				MessageBox(TEXT("修改/添加成功！"), TEXT("提示"), MB_ICONASTERISK);

				m_num1 = 0;
				UpdateData(false);
			}
			if(choice == IDCANCEL)
				MessageBox(TEXT("取消修改/添加！"), TEXT("提示"), MB_ICONASTERISK);
			
			break;
		}
}


void CAddView::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码

	OnCbnSelchangeCombo1();
}


void CAddView::OnSelchangeCombo()
{
	// TODO: 在此添加控件通知处理程序代码

	int index = m_com.GetCurSel();

	if (index == CB_ERR)
		return;

	int id = m_com.GetItemData(index);

	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
		if (it->id == id)
		{
			m_name1 = it->name;
			m_pri1 = it->price;
			m_num1 = it->num;
			break;
		}

	UpdateData(false);
}


void CAddView::OnBnClickedButtonAck2()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData();

	if (m_name2.IsEmpty())
	{
		MessageBox(TEXT("新商品名称不能为空！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
		pedit->SetFocus();

		return;
	}

	if (m_pri2 < 0)
	{
		MessageBox(TEXT("新商品价格不能小于0！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_PRI2);
		pedit->SetFocus();

		return;
	}

	if (m_num2 < 0)
	{
		MessageBox(TEXT("新商品数量不能小于0！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NUM2);
		pedit->SetFocus();

		return;
	}

	CString str, str2;

	str = "请确认以下内容：\n\n名    称：";
	str += m_name2;

	str += "\n价   格：";
	str2.Format(TEXT("%d"), m_pri2);
	str += str2;

	str += "\n数    量：";
	str2.Format(TEXT("%d"), m_num2);
	str += str2;

	str += "\n\n确认无误？";

	int choice = MessageBox(str, TEXT("提问"), MB_OKCANCEL | MB_ICONQUESTION);

	if (choice == IDOK)
	{
		CInfoFile file;
		file.Readline();

		file.Addline(m_name2, m_pri2, m_num2);

		MessageBox(TEXT("添加新商品成功！"), TEXT("提示"), MB_ICONASTERISK);

		m_com.ResetContent();
		OnInitialUpdate();
	}
	if (choice == IDCANCEL)
		MessageBox(TEXT("取消添加新商品！"), TEXT("提示"), MB_ICONASTERISK);
}


void CAddView::OnBnClickedButtonReset2()
{
	// TODO: 在此添加控件通知处理程序代码

	m_name2 = "";
	m_pri2 = 0;
	m_num2 = 0;

	UpdateData(false);
}
