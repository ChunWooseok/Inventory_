#pragma once
#include <iostream>
#include <string>

using namespace std;

class Record_data
{
private:
	string time;
	string kind;
	string location;
	string productID;
	string name;
	int number;

public:
	Record_data(); //������
	Record_data(const string& time, const string& kind, const string& loc, const string& pID, const string& name, const int& number);
	Record_data(const Record_data& arr); //���� ������
	Record_data(Record_data&& arr) noexcept; //�̵� ������
	~Record_data(); //�Ҹ���
	Record_data& operator=(const Record_data& arr); //���Կ�����
	Record_data& operator=(Record_data&& arr) noexcept; //�̵����Կ�����

	//Record_data Ŭ���� data�� get
	string getTime() const;
	string getKind();
	string getLoc();
	string getPID();
	string getName();
	int getNum();

	bool operator<(const Record_data& data)
	{
		return this->getTime() > data.getTime();
	}
};
