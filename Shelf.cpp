#include "Shelf.h"
#include <iostream>

Shelf::Shelf()
{
}

Shelf::Shelf(const int& num, const bool& isUse)
{
	this->maxWeight = num; this->isUse = isUse;
}

//복사 생성자
Shelf::Shelf(const Shelf& arr)
	:Shelf(arr.maxWeight, arr.isUse)
{
	//cout << "Shelf 복사 생성자" << endl;
}

//이동 생성자
Shelf::Shelf(Shelf&& arr) noexcept
	:isUse(arr.isUse), number(arr.number), cur_Weight(arr.cur_Weight), maxWeight(arr.maxWeight), products(move(arr.products))
{
	//cout << "Shelf 이동 생성자" << endl;
}

//소멸자
Shelf::~Shelf()
{
}

//대입 연산자
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

//이동 대입 연산자
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

//현재 무게를 반환.
double Shelf::getCurWeight()
{
	//cout << cur_Weight << endl;
	return cur_Weight;
}

bool Shelf::getIsUse()
{
	return this->isUse;
}

//출고 시 shelf에서 product 삭제.
void Shelf::relPro(Product product, const int& num)
{
	auto it = products.begin();
	while (it != products.end()) {
		if (product == *it) {
			//제품이 존재하고, 출고하려는 개수보다 존재하는 개수가 많으면
			if (it->getNum() - num > 0) {
				it->minNum(num);
				cur_Weight -= num * it->getWeight();
				return;
			}
			//제품이 존재하고, 남은 모든 개수를 가져가려할때
			else if (it->getNum() - num == 0) {
				cur_Weight -= num * it->getWeight();
				products.erase(it);
				return;
			}
			//제품은 존재하나, 출고하려는 개수가 존재하는 개수보다 많을때
			else {
				cout << "출고하려는 개수보다 존재하는 물품의 양이 적습니다. 오류!!" << endl;
				return;
			}
		}
		it++;
	}
	//제품이 shelf에 아예 존재하지 않으면
	cout << "입력하신 제품이 해당 shelf에 없습니다. 오류!!" << endl;
}

//임시
void Shelf::printPro()
{
	auto it = products.begin();
	while (it != products.end()) {
		cout << it->pData() << endl;
		it++;
	}
}

//입고 시 shelf에 product 추가.
void Shelf::addPro(Product product, const int& num)
{
	//products가 비어있으면 그냥 추가.
	if (products.empty()) {
		products.emplace_back(move(product));
		cur_Weight += num * product.getWeight();
		products.begin()->setNum(num);
		return;
	}
	auto it = products.begin();
	while (it != products.end()) {
		//제품이 존재하면, 원래 제품에 추가
		if (product == *it) {
			//cout << "원래에 추가" << endl;
			it->addNum(num);
			cur_Weight += num * it->getWeight();
			return; //제품이 존재하면 무조건 입고 개수만큼 더하기만 하고 끝.
		}
		it++;
	}
	//제품이 존재하지 않으면 while문을 빠져나가고 여기로 오므로, 없는 제품은 추가!
	//cout << "새로운 물품 추가" << endl;
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
		//제품이 존재하면, 원래 제품에 추가
		if (product == *it) {
			//cout << "원래에 추가" << endl;
			it->addNum(product.getNum());
			cur_Weight += product.getNum() * it->getWeight();
			return; //제품이 존재하면 무조건 입고 개수만큼 더하기만 하고 끝.
		}
		it++;
	}
	//제품이 존재하지 않으면 while문을 빠져나가고 여기로 오므로, 없는 제품은 추가!
	//cout << "새로운 물품 추가" << endl;
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

//현재 shelf의 층 최대 무게 수정.
void Shelf::modMaxWeight(int modMax)
{
	this->maxWeight = modMax;
}