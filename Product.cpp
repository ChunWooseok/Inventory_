#include "Product.h"
#include <iostream>
#include <string>

//�⺻ ������
Product::Product()
	:ID(" "), name(" "), weight("0.00"), location(" "), number(0)
{
}

//������
Product::Product(const string& ID, const string& name, const string& weight, const string& location, const int& number)
{
	this->ID = ID;
	this->name = name;
	this->weight = weight;
	this->location = location;
	this->number = number;
	//cout << "Product ������" << endl;
}

//���� ������
Product::Product(const Product& arr)
	:Product(arr.ID, arr.name, arr.weight, arr.location, arr.number)
{
	//cout << "Product ���� ������" << endl;
}

//�̵� ������
Product::Product(Product&& arr) noexcept
	:ID(arr.ID), name(arr.name), weight(arr.weight), location(arr.location), number(arr.number)
{
	//cout << "Product �̵� ������" << endl;
}

//�Ҹ��� -> ���� �Ұ� ����.
Product::~Product()
{
}

//���� ������
Product& Product::operator=(const Product& arr)
{
	if (this == &arr) {
		return *this;
	}

	this->ID = arr.ID;
	this->name = arr.name;
	this->weight = arr.weight;
	this->location = arr.location;
	this->number = arr.number;

	return *this;
}

//�̵� ���� ������
Product& Product::operator=(Product&& arr) noexcept
{
	this->ID = arr.ID;
	this->name = arr.name;
	this->weight = arr.weight;
	this->location = arr.location;
	this->number = arr.number;

	return *this;
}

//Product.txt�� �� product ���� ���ڿ�.
string Product::pData()
{
	return ID + "-" + name + "-" + weight + "-" + location + "-" + to_string(number);
}

//���� number ++
void Product::addNum(const int& num)
{
	number += num;
}

//���� number --
void Product::minNum(const int& num)
{
	number -= num;
}

//�� ���� ��ȯ -> weight * number
double Product::totalWeight()
{
	return stod(weight) * number;
}

//��ǰ�� ����� ��ġ ����. (���� ��Ģ�� ������ �˿�)
void Product::changeLoc(const string& loc)
{
	location = loc;
}

//�� product �� operator== �����ε�
bool Product::operator==(Product pro2)
{
	if (ID == pro2.ID && name == pro2.name && location == pro2.location)
		return true;
	else
		return false;
}

string Product::getID()
{
	return ID;
}

string Product::getName()
{
	return name;
}

string Product::getLoc()
{
	return location;
}

int Product::getNum()
{
	return number;
}

void Product::setNum(const int& num)
{
	number = num;
}

void Product::setLocation(string loc)
{
	location = loc;
}

double Product::getWeight()
{
	//double�� ��ȯ ����.
	return stod(weight);
}