#pragma once
#include <iostream>
#include <string>

using namespace std;

class Product
{
private:
	string ID; //물품코드 > 변경 불가
	string name; //물품이름 > 변경 불가
	string weight; //물품 1개당 무게 -> 문법 규칙 때문에 string으로
	string location; //위치 > 변경가능
	int number = 0; //물품 개수

public:
	Product(); //default 생성자    //↓(입력할 정보들을 사전 검수를 꼭 끝낸 후, 객체 생성해야하기 때문)
	Product(const string& ID, const string& name, const string& weight, const string& location, const int& number);
	Product(const Product& arr); //복사 생성자
	Product(Product&& arr) noexcept; //이동 생성자
	~Product(); //소멸자
	Product& operator=(const Product& arr); //대입연산자
	Product& operator=(Product&& arr) noexcept; //이동대입연산자

	string pData(); //Product.txt에 쓸 product 정보 문자열
	void addNum(const int& num); //출고시 number ++
	void minNum(const int& num); //출고시 number -- (사전에 개수 확인 필수)
	double totalWeight(); //총 무게 반환 -> weight * number
	void changeLoc(const string& loc); //물품이 저장된 위치 변경. (문법 규칙은 사전에 검열)
	bool operator== (Product pro2);

	//get 함수들
	string getID();
	string getName();
	double getWeight(); //한 개 무게를 반환
	string getLoc();
	int getNum(); //현재 product의 갯수 반환. -> 출고시 개수가 0 미만 되는 것을 방지
	void setNum(const int& num);
	void setLocation(string loc);
};