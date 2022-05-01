#pragma once
#include <iostream>
#include <vector>
//#include <memory>
#include "Product.h"

class Shelf
{
private:
	bool isUse = false; // ���� ������ ����ϴ� ���� ���� ����
	int number = 0; //���� ���� �ִ� ���ǵ��� ����
	double cur_Weight = 0.00; //���� ������ �� ����
	vector<Product> products; //������ product�� -> Product�� ���ͷ� push, pop
	int maxWeight = 0; //�� shelf�� ��ƿ �� �ִ� �ִ� ����
public:
	Shelf(); //������ 
	Shelf(const int& num, const bool& isUse); // ������
	Shelf(const Shelf& arr); //���� ������
	Shelf(Shelf&& arr) noexcept; //�̵� ������
	~Shelf(); //�Ҹ���
	Shelf& operator=(const Shelf& arr); //���Կ�����
	Shelf& operator=(Shelf&& arr) noexcept; //�̵����Կ�����

	bool isEmpty(); //������ ������� Ȯ��.
	void addPro(Product product, const int& num); //�԰� �� shelf�� product �߰�
	void addPro(Product product); //override
	void relPro(Product product, const int& num); //��� �� shelf���� product ����
	//void relPro(Product product);
	void printPro(); //shelf�ȿ� �ִ� product���� ���.

	int getNum();
	vector<Product> getProducts();
	vector<Product*> getProducts_p();
	int getMaxWeight(); //���� shelf�� �ִ� ���� ��ȯ.
	double getCurWeight(); //���� shelf�� �� ���� ��ȯ.
	bool getIsUse(); // ���� shelf�� ����ϴ� ���� ���� ���� ��ȯ.
	void setIsUse(bool isUse); // â�� ����ϴ��� ���� ����
	void modMaxWeight(int modMax);
};
