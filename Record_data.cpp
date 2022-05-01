#include "Record_data.h"

Record_data::Record_data()
	:time(""), kind(""), location("0000"), productID("0.00"), name(""), number(0)
{
}

//생성자
Record_data::Record_data(const string& time, const string& kind, const string& loc, const string& pID, const string& name, const int& number)
	: time(time), kind(kind), location(loc), productID(pID), name(name), number(number)
{
	//cout << "생성자" << endl;
}

//복사 생성자
Record_data::Record_data(const Record_data& arr)
	:Record_data(arr.time, arr.kind, arr.location, arr.productID, arr.name, arr.number)
{
	//cout << "복사 생성자" << endl;
}

//이동 생성자
Record_data::Record_data(Record_data&& arr) noexcept
	:time(arr.time), kind(arr.kind), location(arr.location), productID(arr.productID), name(arr.name), number(arr.number)
{
	//cout << "이동 생성자" << endl;
}

//소멸자 -> 딱히 할거 없다.
Record_data::~Record_data()
{
}

//대입 연산자
Record_data& Record_data::operator=(const Record_data& arr)
{
	if (this == &arr) {
		return *this;
	}

	this->time = arr.time;
	this->kind = arr.kind;
	this->location = arr.location;
	this->productID = arr.productID;
	this->name = arr.name;
	this->number = arr.number;

	return *this;
}

//이동 대입 연산자
Record_data& Record_data::operator=(Record_data&& arr) noexcept
{
	this->time = arr.time;
	this->kind = arr.kind;
	this->location = arr.location;
	this->productID = arr.productID;
	this->name = arr.name;
	this->number = arr.number;

	return *this;
}

string Record_data::getTime() const
{
	return time;
}

string Record_data::getKind()
{
	return kind;
}

string Record_data::getLoc()
{
	return location;
}

string Record_data::getPID()
{
	return productID;
}

string Record_data::getName()
{
	return name;
}

int Record_data::getNum()
{
	return number;
}
