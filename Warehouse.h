#pragma once
#include <iostream>
#include <memory>
#include "Shelf.h"

class Warehouse
{
private:
	bool isUse = false;
	int x1 = 0; //���� ��
	int x2 = 0; //���� ��
	int x3 = 0; //�� ��
	Shelf*** shelfs; // Shelf***
public:
	Warehouse(); //default ������ (â��� �ʱ� ���� �߿�)
	Warehouse(const int& num1, const int& num2, const int& num3, const bool& isUse); //������(������ string�� �����ؼ� ���ڷ� ������� �Ѵ�)
	Warehouse(const Warehouse& arr); //���� ������
	Warehouse(Warehouse&& arr) noexcept; //�̵� ������
	~Warehouse(); //�Ҹ���
	Warehouse& operator=(const Warehouse& arr); //���Կ�����
	Warehouse& operator=(Warehouse&& arr) noexcept; //�̵����Կ�����

	int confirmNumber(const int& num1, const int& num2, const int& num3); //�Է��� ����, ����, �� ������ ���� ����ó�� �Լ�.
	void printProduct(const int& num1, const int& num2, const int& num3);
	//shelf�� product �߰� (product�� ���ڷ� �ָ�, product ��ü�� ������ �̾Ƽ� �Է�)
	void addProduct(const int& num1, const int& num2, const int& num3, Product product, const int& number);
	void addProduct(const int& num1, const int& num2, const int& num3, Product product); //override�� �Լ�.
	//shelf���� product ����
	void relProduct(const int& num1, const int& num2, const int& num3, Product product, const int& number);

	int getX1();
	int getX2();
	int getX3();
	Shelf*** getShelfs();
	bool isEmpty(); //â�� ������� Ȯ��
	bool getIsUse(); // â�� ����ϴ��� ���� ��ȯ
	void setIsUse(bool isUse); // â�� ����ϴ��� ���� ����
};
