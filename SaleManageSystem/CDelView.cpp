// CDelView.cpp: 实现文件
//

#include "pch.h"
#include "SaleManageSystem.h"
#include "CDelView.h"
#include "InfoFile.h"


// CDelView

IMPLEMENT_DYNCREATE(CDelView, CFormView)

CDelView::CDelView()
	: CFormView(IDD_DIALOG_DEL)
	, m_pri1(0)
	, m_pri2(0)
	, m_num1(0)
	, m_num2(0)
	, m_name1(_T(""))
	, m_name2(_T(""))
{

}

CDelView::~CDelView()
{
}

void CDelView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN_PRI, m_sp);
	DDX_Control(pDX, IDC_SPIN_NUM, m_sn);
	DDX_Control(pDX, IDC_COMBO_NAME1, m_com1);
	DDX_Control(pDX, IDC_COMBO_NAME2, m_com2);
	DDX_Text(pDX, IDC_EDIT_PRI1, m_pri1);
	DDX_Text(pDX, IDC_EDIT_PRI2, m_pri2);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_num1);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_num2);
	DDX_CBString(pDX, IDC_COMBO_NAME1, m_name1);
	DDX_CBString(pDX, IDC_COMBO_NAME2, m_name2);
}

BEGIN_MESSAGE_MAP(CDelView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME1, &CDelView::OnSelchangeComboName1)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME2, &CDelView::OnSelchangeComboName2)
	ON_BN_CLICKED(IDC_BUTTON_ACK1, &CDelView::OnBnClickedButtonAck1)
	ON_BN_CLICKED(IDC_BUTTON_ACK2, &CDelView::OnBnClickedButtonAck2)
	ON_BN_CLICKED(IDC_BUTTON_RESET1, &CDelView::OnBnClickedButtonReset1)
END_MESSAGE_MAP()


// CDelView 诊断

#ifdef _DEBUG
void CDelView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelView 消息处理程序


void CDelView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_name1 = it->name;
		int id1 = m_com1.AddString(m_name1);
		m_com1.SetItemData(id1, it->id);

		m_name2 = it->name;
		int id2 = m_com2.AddString(m_name2);
		m_com2.SetItemData(id2, it->id);
	}

	if (file.ls.size() > 0)
	{
		m_com1.SetCurSel(0);
		m_com2.SetCurSel(0);
	}

	OnCbnSelchangeCombo1();
	OnCbnSelchangeCombo2();

	m_sp.SetRange(0, 32767);
	m_sn.SetRange(0, 32767);
}


void CDelView::OnCbnSelchangeCombo1()
{
	UpdateData();

	int index = m_com1.GetCurSel();
	int id = m_com1.GetItemData(index);

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


void CDelView::OnCbnSelchangeCombo2()
{
	UpdateData();

	int index = m_com2.GetCurSel();
	int id = m_com2.GetItemData(index);

	CInfoFile file;
	file.Readline();

	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
		if (it->id == id)
		{
			m_pri2 = it->price;
			m_num2 = it->num;
			break;
		}

	UpdateData(false);
}

void CDelView::OnSelchangeComboName1()
{
	// TODO: 在此添加控件通知处理程序代码

	int index = m_com1.GetCurSel();

	if (index == CB_ERR)
		return;

	int id = m_com1.GetItemData(index);

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


void CDelView::OnSelchangeComboName2()
{
	// TODO: 在此添加控件通知处理程序代码

	int index = m_com2.GetCurSel();

	if (index == CB_ERR)
		return;

	int id = m_com2.GetItemData(index);

	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
		if (it->id == id)
		{
			m_name2 = it->name;
			m_pri2 = it->price;
			m_num2 = it->num;
			break;
		}

	UpdateData(false);
}


void CDelView::OnBnClickedButtonAck1()
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
		MessageBox(TEXT("删除商品数量不能小于0！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NUM1);
		pedit->SetFocus();

		return;
	}

	int index = m_com1.GetCurSel();
	CString name;

	m_com1.GetLBText(index, name);
	int id = m_com1.GetItemData(index);

	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
		if (it->id == id)
		{
			if (it->price == m_pri1 && m_num1 == 0)
			{
				MessageBox(TEXT("无修改/删除！"), TEXT("警告"), MB_ICONWARNING);

				return;
			}

			if (m_num1 > it->num)
			{
				MessageBox(TEXT("删除商品数量不能大于库存数量！"), TEXT("警告"), MB_ICONWARNING);

				CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NUM1);
				pedit->SetFocus();

				return;
			}

			CString str, str2;

			str = "请确认以下修改/删除信息：\n\n名    称：";
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

				str += "\n删除数量：";
				str2.Format(TEXT("%d"), m_num1);
				str += str2;
			}

			str += "\n\n确认无误？";

			int choice = MessageBox(str, TEXT("提问"), MB_OKCANCEL | MB_ICONQUESTION);

			if (choice == IDOK)
			{
				it->price = m_pri1;
				it->num -= m_num1;

				file.Updline(it->id, it->name, it->price, it->num);

				MessageBox(TEXT("修改/删除成功！"), TEXT("提示"), MB_ICONASTERISK);

				m_com1.ResetContent();
				m_com2.ResetContent();
				OnInitialUpdate();
			}
			if (choice == IDCANCEL)
				MessageBox(TEXT("取消修改/删除！"), TEXT("提示"), MB_ICONASTERISK);

			break;
		}
}


void CDelView::OnBnClickedButtonAck2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	if (m_num2 != 0)
	{
		MessageBox(TEXT("删除商品数量不为0！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NUM2);
		pedit->SetFocus();

		return;
	}

	int index = m_com1.GetCurSel();
	CString name;

	m_com1.GetLBText(index, name);
	int id = m_com1.GetItemData(index);

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

		file.Delline(id);

		MessageBox(TEXT("删除旧商品成功！"), TEXT("提示"), MB_ICONASTERISK);

		m_com1.ResetContent();
		m_com2.ResetContent();
		OnInitialUpdate();
	}
	if (choice == IDCANCEL)
		MessageBox(TEXT("取消删除旧商品！"), TEXT("提示"), MB_ICONASTERISK);
}


void CDelView::OnBnClickedButtonReset1()
{
	// TODO: 在此添加控件通知处理程序代码

	OnCbnSelchangeCombo1();
}
