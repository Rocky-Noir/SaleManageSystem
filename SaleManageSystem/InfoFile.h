#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include "pch.h"

using namespace std;

struct msg
{
	int id; //��Ʒid
	CString name; //��Ʒ��
	int price; //��Ʒ�۸�
	int num; //��Ʒ����
}; 

struct msg2
{
	int id; //���۵���id
	CString name; //��Ʒ��
	int price; //��Ʒ�۸�
	int num; //��Ʒ����
	int total; //�����ܼ�
	CString date; //��������

};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//��ȡ��¼��Ϣ
	void ReadLogin(CString& name, CString& pwd);

	//�޸�����
	void WritePwd(char* name, char* pwd);

	//��ȡ��Ʒ����
	void Readline();

	//�������Ʒ
	void Addline(CString name, int price, int num);

	//ɾ������Ʒ
	void Delline(int id);

	//�޸���Ʒ��Ϣ
	void Updline(int id, CString name, int price, int num);

	//��ȡ��������
	void Readlist();

	//�����������
	void Addlist(CString name, int price, int num);

	//ɾ����������
	void Dellist(int id);

	//�޸���������
	void Updlist(int id, CString name, int price, int num);

	//��ѯ��������
	void Chelist(CString name, CString date1, CString date2);
	
	list<msg> ls;	//�洢��Ʒ������
	list<msg2> ls2;	//�洢���۵�������
	int num;		//������¼��Ʒ����
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