#include "Product.h"
#include <iostream>
#include <string>

//기본 생성자
Product::Product()
	:ID(" "), name(" "), weight("0.00"), location(" "), number(0)
{
}

//생성자
Product::Product(const string& ID, const string& name, const string& weight, const string& location, const int& number)
{
	this->ID = ID;
	this->name = name;
	this->weight = weight;
	this->location = location;
	this->number = number;
	//cout << "Product 생성자" << endl;
}

//복사 생성자
Product::Product(const Product& arr)
	:Product(arr.ID, arr.name, arr.weight, arr.location, arr.number)
{
	//cout << "Product 복사 생성자" << endl;
}

//이동 생성자
Product::Product(Product&& arr) noexcept
	:ID(arr.ID), name(arr.name), weight(arr.weight), location(arr.location), number(arr.number)
{
	//cout << "Product 이동 생성자" << endl;
}

//소멸자 -> 딱히 할거 없다.
Product::~Product()
{
}

//대입 연산자
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

//이동 대입 연산자
Product& Product::operator=(Product&& arr) noexcept
{
	this->ID = arr.ID;
	this->name = arr.name;
	this->weight = arr.weight;
	this->location = arr.location;
	this->number = arr.number;

	return *this;
}

//Product.txt에 쓸 product 정보 문자열.
string Product::pData()
{
	return ID + "-" + name + "-" + weight + "-" + location + "-" + to_string(number);
}

//출고시 number ++
void Product::addNum(const int& num)
{
	number += num;
}

//출고시 number --
void Product::minNum(const int& num)
{
	number -= num;
}

//총 무게 반환 -> weight * number
double Product::totalWeight()
{
	return stod(weight) * number;
}

//물품이 저장된 위치 변경. (문법 규칙은 사전에 검열)
void Product::changeLoc(const string& loc)
{
	location = loc;
}

//두 product 비교 operator== 오버로드
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
	//double로 반환 주의.
	return stod(weight);
}