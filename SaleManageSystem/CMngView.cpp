// CMngView.cpp: 实现文件
//

#include "pch.h"
#include "SaleManageSystem.h"
#include "CMngView.h"
#include "InfoFile.h"


// CMngView

IMPLEMENT_DYNCREATE(CMngView, CFormView)

CMngView::CMngView()
	: CFormView(IDD_DIALOG_MNG)
	, m_num(0)
	, m_snum(0)
	, m_pri(0)
	, m_spri(0)
	, m_name(_T(""))
{

}

CMngView::~CMngView()
{
}

void CMngView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT_PRI, m_pri);
	DDX_Text(pDX, IDC_EDIT_SPRI, m_spri);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	DDX_Text(pDX, IDC_EDIT_SNUM, m_snum);
	DDX_Control(pDX, IDC_SPIN_PRI, m_sp);
	DDX_Control(pDX, IDC_SPIN_NUM, m_sn);
	DDX_Control(pDX, IDC_COMBO_NAME, m_com);
	DDX_CBString(pDX, IDC_COMBO_NAME, m_name);
}

BEGIN_MESSAGE_MAP(CMngView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_NAME, &CMngView::OnSelchangeComboName)
	ON_BN_CLICKED(IDC_BUTTON_ACK, &CMngView::OnBnClickedButtonAck)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMngView::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CMngView 诊断

#ifdef _DEBUG
void CMngView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMngView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMngView 消息处理程序



void CMngView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_name = it->name;
		int id1 = m_com.AddString(m_name);
		m_com.SetItemData(id1, it->id);
	}

	if (file.ls.size() > 0)
		m_com.SetCurSel(0);

	OnCbnSelchangeCombo1();

	m_sp.SetRange(0, 32767);
	m_sn.SetRange(0, 32767);

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
}


void CMngView::OnCbnSelchangeCombo1()
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
			m_pri = it->price;
			m_num = it->num;
			m_spri = it->price;
			m_snum = 0;

			break;
		}

	UpdateData(false);
}


void CMngView::OnSelchangeComboName()
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
			m_name = it->name;
			m_pri = it->price;
			m_num = it->num;
			m_spri = it->price;
			m_snum = 0;

			break;
		}

	UpdateData(false);
}

void CMngView::OnBnClickedButtonAck()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData();

	if (m_spri < 0)
	{
		MessageBox(TEXT("销售商品价格不能小于0！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_PRI);
		pedit->SetFocus();

		return;
	}

	if (m_snum < 0)
	{
		MessageBox(TEXT("销售商品数量不能小于0！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_SNUM);
		pedit->SetFocus();

		return;
	}

	if (m_snum == 0)
	{
		MessageBox(TEXT("销售商品数量不能等于0！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_SNUM);
		pedit->SetFocus();

		return;
	}

	if (m_snum > m_num)
	{
		MessageBox(TEXT("销售商品数量不能大于库存！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_SNUM);
		pedit->SetFocus();

		return;
	}

	CString str, str2;

	str = "请确认以下内容：\n\n名    称：";
	str += m_name;

	str += "\n原    价：";
	str2.Format(TEXT("%d"), m_pri);
	str += str2;

	str += "\n库    存：";
	str2.Format(TEXT("%d"), m_num);
	str += str2;

	str += "\n售    价：";
	str2.Format(TEXT("%d"), m_spri);
	str += str2;

	str += "\n数    量：";
	str2.Format(TEXT("%d"), m_snum);
	str += str2;

	str += "\n\n确认无误？";

	int choice = MessageBox(str, TEXT("提问"), MB_OKCANCEL | MB_ICONQUESTION);

	if (choice == IDOK)
	{
		CInfoFile file;
		file.Readlist();

		file.Addlist(m_name, m_spri, m_snum);
		
		file.Readline();
		list<msg>::iterator it;

		for (it = file.ls.begin(); it != file.ls.end(); it++)
			if (it->name == m_name)
			{
				it->num -= m_snum;

				file.Updline(it->id, it->name, it->price, it->num);
			}

		m_num -= m_snum;

		MessageBox(TEXT("添加销售记录成功！"), TEXT("提示"), MB_ICONASTERISK);

		list<msg2>::iterator it2;
		int id;

		for (it2 = file.ls2.begin(); it2 != file.ls2.end(); it2++)
			id = it2->id;

		CTime tm;
		tm = CTime::GetCurrentTime();

		int cnt = m_list.GetItemCount();

		str.Format(TEXT("%d"), id); 
		m_list.InsertItem(cnt, str);
		m_list.SetItemText(cnt, 1, m_name);
		str.Format(TEXT("%d"), m_spri); 
		m_list.SetItemText(cnt, 2, str);
		str.Format(TEXT("%d"), m_snum); 
		m_list.SetItemText(cnt, 3, str);
		str.Format(TEXT("%d"), m_spri * m_snum); 
		m_list.SetItemText(cnt, 4, str);
		str = tm.Format("%Y/%m/%d");
		m_list.SetItemText(cnt, 5, str);

		UpdateData(false);
	}
	if (choice == IDCANCEL)
		MessageBox(TEXT("取消添加销售记录！"), TEXT("提示"), MB_ICONASTERISK);
}


void CMngView::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码

	OnCbnSelchangeCombo1();
}
