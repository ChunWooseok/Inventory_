#pragma once
#include <iostream>
#include <string>

using namespace std;

class Record_data
{
private:
	string time;
	string kind;
	string location;
	string productID;
	string name;
	int number;

public:
	Record_data(); //생성자
	Record_data(const string& time, const string& kind, const string& loc, const string& pID, const string& name, const int& number);
	Record_data(const Record_data& arr); //복사 생성자
	Record_data(Record_data&& arr) noexcept; //이동 생성자
	~Record_data(); //소멸자
	Record_data& operator=(const Record_data& arr); //대입연산자
	Record_data& operator=(Record_data&& arr) noexcept; //이동대입연산자

	//Record_data 클래스 data들 get
	string getTime() const;
	string getKind();
	string getLoc();
	string getPID();
	string getName();
	int getNum();

	bool operator<(const Record_data& data)
	{
		return this->getTime() > data.getTime();
	}
};
