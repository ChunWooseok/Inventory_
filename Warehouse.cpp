#include "Warehouse.h"
#include <iostream>

//default ������
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
	//cout << "Warehouse default ������." << endl;
}

//������
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
	//cout << "Warehouse ������" << endl;
}

//���� ������
Warehouse::Warehouse(const Warehouse& arr)
	:Warehouse(arr.x1, arr.x2, arr.x3, arr.isUse)
{
	//cout << "Warehouse ���� ������." << endl;
}

//�̵� ������
Warehouse::Warehouse(Warehouse&& arr) noexcept
	:x1(arr.x1), x2(arr.x2), x3(arr.x3), isUse(arr.isUse), shelfs(arr.shelfs)
{
	//cout << "Warehouse �̵� ������." << endl;
}

//�Ҹ���
Warehouse::~Warehouse()
{

}

//���� ������
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
		cout << "������ ������ " << x1 << "�� �Դϴ�. �ùٸ� ������ �Է��ϼ���." << endl;
		return 0;
	}
	if (num2 > x2 || num2 < 1) {
		cout << "������ ������ " << x2 << "�� �Դϴ�. �ùٸ� ������ �Է��ϼ���." << endl;
		return 0;
	}
	if (num3 > x3 || num3 < 1) {
		cout << "���� ���� ������ " << x3 << "�� �Դϴ�. �ùٸ� ���� ���� �Է��ϼ���." << endl;
		return 0;
	}
	return 1;
}

//â�� �ȿ� �ִ� product�� ���~
void Warehouse::printProduct(const int& num1, const int& num2, const int& num3)
{
	if (confirmNumber(num1, num2, num3) == 0)
		return;

	this->shelfs[num1 - 1][num2 - 1][num3 - 1].printPro();
}

//shelf�� product �߰�
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

//shelf���� product ����
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

//â�� ������� Ȯ��
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