#pragma once
#include <iostream>
#include <memory>
#include "Shelf.h"

class Warehouse
{
private:
	bool isUse = false;
	int x1 = 0; //구역 수
	int x2 = 0; //선반 수
	int x3 = 0; //층 수
	Shelf*** shelfs; // Shelf***
public:
	Warehouse(); //default 생성자 (창고는 초기 설정 중요)
	Warehouse(const int& num1, const int& num2, const int& num3, const bool& isUse); //생성자(사전에 string을 구분해서 인자로 보내줘야 한다)
	Warehouse(const Warehouse& arr); //복사 생성자
	Warehouse(Warehouse&& arr) noexcept; //이동 생성자
	~Warehouse(); //소멸자
	Warehouse& operator=(const Warehouse& arr); //대입연산자
	Warehouse& operator=(Warehouse&& arr) noexcept; //이동대입연산자

	int confirmNumber(const int& num1, const int& num2, const int& num3); //입력한 구역, 선반, 층 개수에 대한 예외처리 함수.
	void printProduct(const int& num1, const int& num2, const int& num3);
	//shelf에 product 추가 (product만 인자로 주면, product 객체의 개수를 뽑아서 입력)
	void addProduct(const int& num1, const int& num2, const int& num3, Product product, const int& number);
	void addProduct(const int& num1, const int& num2, const int& num3, Product product); //override한 함수.
	//shelf에서 product 제거
	void relProduct(const int& num1, const int& num2, const int& num3, Product product, const int& number);

	int getX1();
	int getX2();
	int getX3();
	Shelf*** getShelfs();
	bool isEmpty(); //창고가 비었는지 확인
	bool getIsUse(); // 창고를 사용하는지 유무 반환
	void setIsUse(bool isUse); // 창고를 사용하는지 유무 설정
};
