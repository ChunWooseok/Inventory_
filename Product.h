#pragma once
#include <iostream>
#include <string>

using namespace std;

class Product
{
private:
	string ID; //��ǰ�ڵ� > ���� �Ұ�
	string name; //��ǰ�̸� > ���� �Ұ�
	string weight; //��ǰ 1���� ���� -> ���� ��Ģ ������ string����
	string location; //��ġ > ���氡��
	int number = 0; //��ǰ ����

public:
	Product(); //default ������    //��(�Է��� �������� ���� �˼��� �� ���� ��, ��ü �����ؾ��ϱ� ����)
	Product(const string& ID, const string& name, const string& weight, const string& location, const int& number);
	Product(const Product& arr); //���� ������
	Product(Product&& arr) noexcept; //�̵� ������
	~Product(); //�Ҹ���
	Product& operator=(const Product& arr); //���Կ�����
	Product& operator=(Product&& arr) noexcept; //�̵����Կ�����

	string pData(); //Product.txt�� �� product ���� ���ڿ�
	void addNum(const int& num); //���� number ++
	void minNum(const int& num); //���� number -- (������ ���� Ȯ�� �ʼ�)
	double totalWeight(); //�� ���� ��ȯ -> weight * number
	void changeLoc(const string& loc); //��ǰ�� ����� ��ġ ����. (���� ��Ģ�� ������ �˿�)
	bool operator== (Product pro2);

	//get �Լ���
	string getID();
	string getName();
	double getWeight(); //�� �� ���Ը� ��ȯ
	string getLoc();
	int getNum(); //���� product�� ���� ��ȯ. -> ���� ������ 0 �̸� �Ǵ� ���� ����
	void setNum(const int& num);
	void setLocation(string loc);
};