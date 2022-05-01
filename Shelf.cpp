#include "Shelf.h"
#include <iostream>

Shelf::Shelf()
{
}

Shelf::Shelf(const int& num, const bool& isUse)
{
	this->maxWeight = num; this->isUse = isUse;
}

//���� ������
Shelf::Shelf(const Shelf& arr)
	:Shelf(arr.maxWeight, arr.isUse)
{
	//cout << "Shelf ���� ������" << endl;
}

//�̵� ������
Shelf::Shelf(Shelf&& arr) noexcept
	:isUse(arr.isUse), number(arr.number), cur_Weight(arr.cur_Weight), maxWeight(arr.maxWeight), products(move(arr.products))
{
	//cout << "Shelf �̵� ������" << endl;
}

//�Ҹ���
Shelf::~Shelf()
{
}

//���� ������
Shelf& Shelf::operator=(const Shelf& arr)
{
	if (this == &arr) {
		return *this;
	}
	this->number = arr.number;
	this->maxWeight = arr.maxWeight;
	this->cur_Weight = arr.cur_Weight;
	this->isUse = arr.isUse;

	auto it = arr.products.begin();
	while (it != arr.products.end()) {
		products.push_back(*it);
		++it;
	}

	return *this;
}

//�̵� ���� ������
Shelf& Shelf::operator=(Shelf&& arr) noexcept
{
	this->number = arr.number;
	this->maxWeight = arr.maxWeight;
	this->cur_Weight = arr.cur_Weight;
	this->isUse = arr.isUse;
	products = move(arr.products);

	return *this;
}

int Shelf::getNum()
{
	return number;
}

vector<Product> Shelf::getProducts()
{
	return this->products;
}

vector<Product*> Shelf::getProducts_p()
{
	vector<Product*> returnval;
	for (int i = 0; i < this->products.size(); i++)
		returnval.push_back(&this->products[i]);

	return returnval;
}

int Shelf::getMaxWeight()
{
	return this->maxWeight;
}

//���� ���Ը� ��ȯ.
double Shelf::getCurWeight()
{
	//cout << cur_Weight << endl;
	return cur_Weight;
}

bool Shelf::getIsUse()
{
	return this->isUse;
}

//��� �� shelf���� product ����.
void Shelf::relPro(Product product, const int& num)
{
	auto it = products.begin();
	while (it != products.end()) {
		if (product == *it) {
			//��ǰ�� �����ϰ�, ����Ϸ��� �������� �����ϴ� ������ ������
			if (it->getNum() - num > 0) {
				it->minNum(num);
				cur_Weight -= num * it->getWeight();
				return;
			}
			//��ǰ�� �����ϰ�, ���� ��� ������ ���������Ҷ�
			else if (it->getNum() - num == 0) {
				cur_Weight -= num * it->getWeight();
				products.erase(it);
				return;
			}
			//��ǰ�� �����ϳ�, ����Ϸ��� ������ �����ϴ� �������� ������
			else {
				cout << "����Ϸ��� �������� �����ϴ� ��ǰ�� ���� �����ϴ�. ����!!" << endl;
				return;
			}
		}
		it++;
	}
	//��ǰ�� shelf�� �ƿ� �������� ������
	cout << "�Է��Ͻ� ��ǰ�� �ش� shelf�� �����ϴ�. ����!!" << endl;
}

//�ӽ�
void Shelf::printPro()
{
	auto it = products.begin();
	while (it != products.end()) {
		cout << it->pData() << endl;
		it++;
	}
}

//�԰� �� shelf�� product �߰�.
void Shelf::addPro(Product product, const int& num)
{
	//products�� ��������� �׳� �߰�.
	if (products.empty()) {
		products.emplace_back(move(product));
		cur_Weight += num * product.getWeight();
		products.begin()->setNum(num);
		return;
	}
	auto it = products.begin();
	while (it != products.end()) {
		//��ǰ�� �����ϸ�, ���� ��ǰ�� �߰�
		if (product == *it) {
			//cout << "������ �߰�" << endl;
			it->addNum(num);
			cur_Weight += num * it->getWeight();
			return; //��ǰ�� �����ϸ� ������ �԰� ������ŭ ���ϱ⸸ �ϰ� ��.
		}
		it++;
	}
	//��ǰ�� �������� ������ while���� ���������� ����� ���Ƿ�, ���� ��ǰ�� �߰�!
	//cout << "���ο� ��ǰ �߰�" << endl;
	products.emplace_back(move(product));
	products.back().setNum(num);
	cur_Weight += num * products.back().getWeight();
}

void Shelf::addPro(Product product)
{
	if (products.empty()) {
		products.emplace_back(move(product));
		cur_Weight += product.getNum() * product.getWeight();
		return;
	}
	auto it = products.begin();
	while (it != products.end()) {
		//��ǰ�� �����ϸ�, ���� ��ǰ�� �߰�
		if (product == *it) {
			//cout << "������ �߰�" << endl;
			it->addNum(product.getNum());
			cur_Weight += product.getNum() * it->getWeight();
			return; //��ǰ�� �����ϸ� ������ �԰� ������ŭ ���ϱ⸸ �ϰ� ��.
		}
		it++;
	}
	//��ǰ�� �������� ������ while���� ���������� ����� ���Ƿ�, ���� ��ǰ�� �߰�!
	//cout << "���ο� ��ǰ �߰�" << endl;
	products.emplace_back(move(product));
	cur_Weight += product.getNum() * products.back().getWeight();
}

bool Shelf::isEmpty()
{
	//cout << "Current Shelf is Empty!" << endl;
	return (number == 0) && (cur_Weight == 0.00);
}
void Shelf::setIsUse(bool isUse)
{
	this->isUse = isUse;
}

//���� shelf�� �� �ִ� ���� ����.
void Shelf::modMaxWeight(int modMax)
{
	this->maxWeight = modMax;
}