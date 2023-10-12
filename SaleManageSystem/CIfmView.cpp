// CIfmView.cpp: 实现文件
//

#include "pch.h"
#include "SaleManageSystem.h"
#include "CIfmView.h"
#include "InfoFile.h"


// CIfmView

IMPLEMENT_DYNCREATE(CIfmView, CFormView)

CIfmView::CIfmView()
	: CFormView(IDD_DIALOG_IFM)
	, m_name(_T(""))
	, m_pri(0)
	, m_num(0)
	, m_id(0)
{

}

CIfmView::~CIfmView()
{
}

void CIfmView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_PRI, m_pri);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
}

BEGIN_MESSAGE_MAP(CIfmView, CFormView)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST1, &CIfmView::OnItemactivateList)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CIfmView::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_ACK, &CIfmView::OnBnClickedButtonAck)
END_MESSAGE_MAP()


// CIfmView 诊断

#ifdef _DEBUG
void CIfmView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIfmView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIfmView 消息处理程序


void CIfmView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	m_list.InsertColumn(0, TEXT("编号"));
	m_list.InsertColumn(1, TEXT("商品"));
	m_list.InsertColumn(2, TEXT("价格"));
	m_list.InsertColumn(3, TEXT("数量"));

	m_list.SetColumnWidth(0, 60);//设置列宽
	m_list.SetColumnWidth(1, 120);
	m_list.SetColumnWidth(2, 60);
	m_list.SetColumnWidth(3, 60);

	ListUpdata();
}


void CIfmView::ListUpdata()
{
	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;
	CString str;

	m_list.DeleteAllItems();

	for (it = file.ls.begin(); it != file.ls.end(); it++)
	{
		int cnt = m_list.GetItemCount();
		str.Format(TEXT("%d"), it->id);
		m_list.InsertItem(cnt, str);

		m_list.SetItemText(cnt, 1, it->name);
		str.Format(TEXT("%d"), it->price);
		m_list.SetItemText(cnt, 2, str);
		str.Format(TEXT("%d"), it->num);
		m_list.SetItemText(cnt, 3, str);
	}
}


void CIfmView::OnItemactivateList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
		if (it->id == pNMIA->iItem + 1)
		{
			m_id = it->id;
			m_name = it->name;
			m_pri = it->price;
			m_num = it->num;
		}

	UpdateData(false);

	*pResult = 0;
}


void CIfmView::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_id = 0;
	m_name = "";
	m_pri = 0;
	m_num = 0;

	UpdateData(false);
}


void CIfmView::OnBnClickedButtonAck()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	if (m_name.IsEmpty())
	{
		MessageBox(TEXT("修改商品名称不能为空！"), TEXT("警告"), MB_ICONWARNING);

		CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
		pedit->SetFocus();

		return;
	}

	CInfoFile file;
	file.Readline();
	list<msg>::iterator it;

	for (it = file.ls.begin(); it != file.ls.end(); it++)
		if (it->id == m_id)
		{
			CString str, str2;

			str = "请确认以下内容：\n\n编    号：";
			str2.Format(TEXT("%d"), m_id);
			str += str2;

			str += "\n原 名 称：";
			str += it->name;

			str += "\n更改名称：";
			str += m_name;

			str += "\n\n确认无误？";
			it->name = m_name;

			int choice = MessageBox(str, TEXT("提问"), MB_OKCANCEL | MB_ICONQUESTION);

			if (choice == IDOK)
			{
				file.Updline(it->id, it->name, it->price, it->num);

				MessageBox(TEXT("修改商品名称成功！"), TEXT("提示"), MB_ICONASTERISK);

				ListUpdata();
				OnBnClickedButtonReset();
			}
			if (choice == IDCANCEL)
				MessageBox(TEXT("取消修改商品名称！"), TEXT("提示"), MB_ICONASTERISK);
		}
}
