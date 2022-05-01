#include "Warehouse.h"
#include <iostream>

//default 생성자
Warehouse::Warehouse()
{
	this->shelfs = new Shelf * *[10];
	for (int i = 0; i < 10; i++)
	{
		this->shelfs[i] = new Shelf * [10];
		for (int j = 0; j < 10; j++)
		{
			this->shelfs[i][j] = new Shelf[10];
		}
	}
	//cout << "Warehouse default 생성자." << endl;
}

//생성자
Warehouse::Warehouse(const int& num1, const int& num2, const int& num3, const bool& isUse)
{
	this->x1 = num1; this->x2 = num2; this->x3 = num3; this->isUse = isUse;
	this->shelfs = new Shelf * *[10];
	for (int i = 0; i < 10; i++) {
		this->shelfs[i] = new Shelf * [10];
		for (int j = 0; j < 10; j++) {
			this->shelfs[i][j] = new Shelf[10];
		}
	}
	//cout << "Warehouse 생성자" << endl;
}

//복사 생성자
Warehouse::Warehouse(const Warehouse& arr)
	:Warehouse(arr.x1, arr.x2, arr.x3, arr.isUse)
{
	//cout << "Warehouse 복사 생성자." << endl;
}

//이동 생성자
Warehouse::Warehouse(Warehouse&& arr) noexcept
	:x1(arr.x1), x2(arr.x2), x3(arr.x3), isUse(arr.isUse), shelfs(arr.shelfs)
{
	//cout << "Warehouse 이동 생성자." << endl;
}

//소멸자
Warehouse::~Warehouse()
{

}

//대입 연산자
Warehouse& Warehouse::operator=(const Warehouse& arr)
{
	if (this == &arr) {
		return *this;
	}
	this->x1 = arr.x1;
	this->x2 = arr.x2;
	this->x3 = arr.x3;
	this->shelfs = arr.shelfs;
	this->isUse = arr.isUse;
	return *this;
}

Warehouse& Warehouse::operator=(Warehouse&& arr) noexcept
{
	this->x1 = arr.x1;
	this->x2 = arr.x2;
	this->x3 = arr.x3;
	this->shelfs = arr.shelfs;
	this->isUse = arr.isUse;
	return *this;
}

int Warehouse::confirmNumber(const int& num1, const int& num2, const int& num3)
{
	if (num1 > x1 || num1 < 1) {
		cout << "구역의 개수는 " << x1 << "개 입니다. 올바른 구역을 입력하세요." << endl;
		return 0;
	}
	if (num2 > x2 || num2 < 1) {
		cout << "선반의 개수는 " << x2 << "개 입니다. 올바른 선반을 입력하세요." << endl;
		return 0;
	}
	if (num3 > x3 || num3 < 1) {
		cout << "선반 층의 개수는 " << x3 << "개 입니다. 올바른 선반 층을 입력하세요." << endl;
		return 0;
	}
	return 1;
}

//창고 안에 있는 product들 출력~
void Warehouse::printProduct(const int& num1, const int& num2, const int& num3)
{
	if (confirmNumber(num1, num2, num3) == 0)
		return;

	this->shelfs[num1 - 1][num2 - 1][num3 - 1].printPro();
}

//shelf에 product 추가
void Warehouse::addProduct(const int& num1, const int& num2, const int& num3, Product product, const int& number)
{
	if (confirmNumber(num1, num2, num3) == 0)
		return;

	this->shelfs[num1 - 1][num2 - 1][num3 - 1].addPro(product, number);
}

void Warehouse::addProduct(const int& num1, const int& num2, const int& num3, Product product)
{
	if (confirmNumber(num1, num2, num3) == 0)
		return;

	this->shelfs[num1 - 1][num2 - 1][num3 - 1].addPro(product);
}

//shelf에서 product 제거
void Warehouse::relProduct(const int& num1, const int& num2, const int& num3, Product product, const int& number)
{
	if (confirmNumber(num1, num2, num3) == 0)
		return;

	this->shelfs[num1 - 1][num2 - 1][num3 - 1].relPro(product, number);
}

int Warehouse::getX1()
{
	return this->x1;
}

int Warehouse::getX2()
{
	return this->x2;
}

int Warehouse::getX3()
{
	return this->x3;
}

Shelf*** Warehouse::getShelfs()
{
	return this->shelfs;
}

//창고가 비었는지 확인
bool Warehouse::isEmpty()
{
	int emp = 0;

	for (int k = 0; k < x1; k++) {
		for (int i = 0; i < x2; i++) {
			for (int j = 0; j < x3; j++) {
				if (shelfs[k][i][j].isEmpty())
					emp++;
			}
		}
	}
	if (emp == x1 * x2 * x3) {
		cout << "Empty" << endl;
		return true;
	}
	else {
		cout << "Not Empty" << endl;
		return false;
	}
}

bool Warehouse::getIsUse()
{
	return this->isUse;
}

void Warehouse::setIsUse(bool isUse)
{
	this->isUse = isUse;
}