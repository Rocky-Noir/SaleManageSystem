#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include "pch.h"

using namespace std;

struct msg
{
	int id; //商品id
	CString name; //商品名
	int price; //商品价格
	int num; //商品个数
}; 

struct msg2
{
	int id; //销售单号id
	CString name; //商品名
	int price; //商品价格
	int num; //商品个数
	int total; //销售总价
	CString date; //销售日期

};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取登录信息
	void ReadLogin(CString& name, CString& pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);

	//读取商品数据
	void Readline();

	//添加新商品
	void Addline(CString name, int price, int num);

	//删除旧商品
	void Delline(int id);

	//修改商品信息
	void Updline(int id, CString name, int price, int num);

	//读取销售数据
	void Readlist();

	//添加销售数据
	void Addlist(CString name, int price, int num);

	//删除销售数据
	void Dellist(int id);

	//修改销售数据
	void Updlist(int id, CString name, int price, int num);

	//查询销售数据
	void Chelist(CString name, CString date1, CString date2);
	
	list<msg> ls;	//存储商品的容器
	list<msg2> ls2;	//存储销售单的容器
	int num;		//用来记录商品个数
	int flag;
	int maxId;
	int num2;
	int flag2;
	int maxId2;

public:
	_ConnectionPtr m_pCon;
	_RecordsetPtr m_pRcd;
	_CommandPtr	m_pCom;
};