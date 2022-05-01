#pragma once
#include <iostream>
#include <vector>
//#include <memory>
#include "Product.h"

class Shelf
{
private:
	bool isUse = false; // 현재 선반을 사용하는 지에 대한 유무
	int number = 0; //선반 위에 있는 물건들의 개수
	double cur_Weight = 0.00; //현재 선반위 총 무게
	vector<Product> products; //선반위 product들 -> Product를 벡터로 push, pop
	int maxWeight = 0; //한 shelf가 버틸 수 있는 최대 무게
public:
	Shelf(); //생성자 
	Shelf(const int& num, const bool& isUse); // 생성자
	Shelf(const Shelf& arr); //복사 생성자
	Shelf(Shelf&& arr) noexcept; //이동 생성자
	~Shelf(); //소멸자
	Shelf& operator=(const Shelf& arr); //대입연산자
	Shelf& operator=(Shelf&& arr) noexcept; //이동대입연산자

	bool isEmpty(); //선반이 비었는지 확인.
	void addPro(Product product, const int& num); //입고 시 shelf에 product 추가
	void addPro(Product product); //override
	void relPro(Product product, const int& num); //출고 시 shelf에서 product 삭제
	//void relPro(Product product);
	void printPro(); //shelf안에 있는 product들을 출력.

	int getNum();
	vector<Product> getProducts();
	vector<Product*> getProducts_p();
	int getMaxWeight(); //현재 shelf의 최대 무게 반환.
	double getCurWeight(); //현재 shelf의 총 무게 반환.
	bool getIsUse(); // 현재 shelf를 사용하는 지에 대한 유무 반환.
	void setIsUse(bool isUse); // 창고를 사용하는지 유무 설정
	void modMaxWeight(int modMax);
};
