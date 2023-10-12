#include "pch.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
	flag = 0;
	num = 0;
	maxId = 0;

	flag2 = 0;
	num2 = 0;
	maxId2 = 0;

	m_pCon.CreateInstance(__uuidof(Connection));
	m_pRcd.CreateInstance(__uuidof(Recordset));
	m_pCom.CreateInstance(__uuidof(Command));


	try
	{
		m_pCon->Open("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=./file/data.mdb;", "", "", 0);
	}
	catch (_com_error   e)
	{          //捕捉异常
		CString str;
		str.Format(TEXT("连接失败!\r\n错误信息:%s"), e.ErrorMessage());

		AfxMessageBox(str);
		return;
	}
}

CInfoFile::~CInfoFile()
{
}

//读取登录信息
void CInfoFile::ReadLogin(CString& name, CString& pwd)
{
	m_pRcd->Open("Login", m_pCon.GetInterfacePtr(), adOpenDynamic, adLockReadOnly, adCmdTable);

	FieldsPtr flds = m_pRcd->GetFields();// 获取当前表的字段指针

	name = (CString) m_pRcd->GetCollect("Nam");
	pwd = (CString) m_pRcd->GetCollect("Pwd");

	m_pRcd->Close();
}

//修改密码
void CInfoFile::WritePwd(char* name, char* pwd)
{
	m_pRcd->Open("Login", m_pCon.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdTable);

	FieldsPtr flds = m_pRcd->GetFields();// 获取当前表的字段指针
	
	m_pRcd->PutCollect("Pwd", _variant_t(pwd));
	m_pRcd->Update();

	m_pRcd->Close();
}

//读取商品的信息
void CInfoFile::Readline()
{
	m_pRcd->Open("Stock", m_pCon.GetInterfacePtr(), adOpenDynamic, adLockReadOnly, adCmdTable);

	char buf[1024] = { 0 };
	num = 0;	//初始化商品数量为0
	ls.clear();
	
	while (!m_pRcd->adoEOF)
	{
		msg tmp;
		
		tmp.id = m_pRcd->GetCollect("ID");	//商品id
		tmp.name = m_pRcd->GetCollect("Nam");	//商品名称
		tmp.price = m_pRcd->GetCollect("Pri");	//商品价格
		tmp.num = m_pRcd->GetCollect("Num");	//商品数目

		if (tmp.id > maxId)
			maxId = tmp.id;

		ls.push_back(tmp);	//放在链表的后面
		num++;

		m_pRcd->MoveNext();
	}
	
	m_pRcd->Close();

	flag = 1;
}

//添加新商品
void CInfoFile::Addline(CString name, int price, int num)
{
	if (flag == 0)
		return;

	m_pRcd->Open("Stock", m_pCon.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdTable);

	while (!m_pRcd->adoEOF)
		m_pRcd->MoveNext();

	if (!name.IsEmpty() && num >= 0 && price >= 0)	//商品名称，库存，价格有效
	{
		msg tmp;

		tmp.id = maxId + 1;		//id自动加1
		tmp.name = name;		//商品名称
		tmp.num = num;			//库存
		tmp.price = price;		//价格

		ls.push_back(tmp);			//放在链表的后面

		maxId++;

		m_pRcd->AddNew();
		m_pRcd->PutCollect("ID", _variant_t(tmp.id));
		m_pRcd->PutCollect("Nam", _variant_t(tmp.name));
		m_pRcd->PutCollect("Pri", _variant_t(tmp.price));
		m_pRcd->PutCollect("Num", _variant_t(tmp.num));
		m_pRcd->Update();
	}

	m_pRcd->Close();
}

//删除旧商品
void CInfoFile::Delline(int id)
{
	if (flag == 0)
		return;

	m_pRcd->Open("Stock", m_pCon.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdTable);

	while (!m_pRcd->adoEOF)
	{
		if ((int)m_pRcd->GetCollect("ID") == id)
		{
			m_pRcd->Delete(adAffectCurrent);
			m_pRcd->MoveFirst();
			break;
		}

		m_pRcd->MoveNext();
	}
}

//修改商品信息
void CInfoFile::Updline(int id, CString name, int price, int num)
{
	if (flag == 0)
		return;

	m_pRcd->Open("Stock", m_pCon.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdTable);

	if (!name.IsEmpty() && price >= 0 && num >= 0)	//商品名称，库存，价格有效
		while (!m_pRcd->adoEOF)
		{
			if ((int) m_pRcd->GetCollect("ID") == id)
			{
				m_pRcd->PutCollect("Nam", _variant_t(name));
				m_pRcd->PutCollect("Pri", _variant_t(price));
				m_pRcd->PutCollect("Num", _variant_t(num));
				m_pRcd->Update();

				break;
			}

			m_pRcd->MoveNext();
		}
}

//读取销售数据
void CInfoFile::Readlist()
{
	m_pRcd->Open("SaleRec", m_pCon.GetInterfacePtr(), adOpenDynamic, adLockReadOnly, adCmdTable);

	char buf[1024] = { 0 };
	num2 = 0;	//初始化商品数量为0
	ls2.clear();

	while (!m_pRcd->adoEOF)
	{
		msg2 tmp;

		tmp.id = m_pRcd->GetCollect("ID");	//销售单号
		tmp.name = m_pRcd->GetCollect("Nam");	//商品名称
		tmp.price = m_pRcd->GetCollect("Pri");	//商品价格
		tmp.num = m_pRcd->GetCollect("SaleNum");	//销售数目
		tmp.total = m_pRcd->GetCollect("Total");	//销售总价
		tmp.date = m_pRcd->GetCollect("SaleDate");	//销售总价

		if (tmp.id > maxId2)
			maxId2 = tmp.id;

		ls2.push_back(tmp);	//放在链表的后面
		num2++;

		m_pRcd->MoveNext();
	}

	m_pRcd->Close();

	flag2 = 1;
}

//添加新商品
void CInfoFile::Addlist(CString name, int price, int num)
{
	if (flag2 == 0)
		return;

	m_pRcd->Open("SaleRec", m_pCon.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdTable);

	while (!m_pRcd->adoEOF)
		m_pRcd->MoveNext();

	if (!name.IsEmpty() && num >= 0 && price >= 0)	//商品名称，库存，价格有效
	{
		msg2 tmp;

		CTime tm;
		tm = CTime::GetCurrentTime();

		tmp.id = maxId2 + 1;		//id自动加1
		tmp.name = name;		//商品名称
		tmp.num = num;			//数量
		tmp.price = price;		//价格
		tmp.total = price * num;		//总价
		tmp.date = tm.Format("%Y/%m/%d");

		ls2.push_back(tmp);			//放在链表的后面

		maxId2++;

		m_pRcd->AddNew();
		m_pRcd->PutCollect("ID", _variant_t(tmp.id));
		m_pRcd->PutCollect("Nam", _variant_t(tmp.name));
		m_pRcd->PutCollect("Pri", _variant_t(tmp.price));
		m_pRcd->PutCollect("SaleNum", _variant_t(tmp.num));
		m_pRcd->PutCollect("Total", _variant_t(tmp.total));
		m_pRcd->PutCollect("SaleDate", _variant_t(tmp.date));
		m_pRcd->Update();
	}

	m_pRcd->Close();
}


void CInfoFile::Chelist(CString name, CString date1, CString date2)
{
	CString sql;

	if (name != "全部商品")
		sql.Format(TEXT("select * from SaleRec where Nam='%s' and (SaleDate >= '%s' and SaleDate <= '%s');"), name, date1, date2);
	else
		sql.Format(TEXT("select * from SaleRec where SaleDate >= '%s' and SaleDate <= '%s';"), date1, date2);

	CStringA sql1(sql);

	m_pRcd->Open(sql1.GetBuffer(), m_pCon.GetInterfacePtr(), adOpenDynamic, adLockReadOnly, adCmdText);

	char buf[1024] = { 0 };
	num2 = 0;	//初始化商品数量为0
	ls2.clear();

	while (!m_pRcd->adoEOF)
	{
		msg2 tmp;

		tmp.id = m_pRcd->GetCollect("ID");	//销售单号
		tmp.name = m_pRcd->GetCollect("Nam");	//商品名称
		tmp.price = m_pRcd->GetCollect("Pri");	//商品价格
		tmp.num = m_pRcd->GetCollect("SaleNum");	//销售数目
		tmp.total = m_pRcd->GetCollect("Total");	//销售总价
		tmp.date = m_pRcd->GetCollect("SaleDate");	//销售总价

		if (tmp.id > maxId2)
			maxId2 = tmp.id;

		ls2.push_back(tmp);	//放在链表的后面
		num2++;

		m_pRcd->MoveNext();
	}

	m_pRcd->Close();

	flag2 = 1;
}