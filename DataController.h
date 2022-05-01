#pragma once
#include "Product.h"
#include "Record_data.h"
#include "Warehouse.h"
#include "Shelf.h"
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <direct.h>
#include <mbstring.h>

#define MAX_WAHEHOUSE_NUM 10

class DataController
{
private:
	Warehouse* warehouses; // 창고 정보
	vector<Record_data> records; // 입출고 현황 정보
	DataController() { warehouses = new Warehouse[MAX_WAHEHOUSE_NUM]; }
	~DataController() {}
public:
	static DataController& GetInstance() // 싱글톤 구현
	{
		static DataController* instance = new DataController();
		return *instance;
	}
	vector<Product*> FindProduct(string lotation); // 위치 정보(선반)에 위치한 Product 배열을 반환
	vector<Product*> FindProduct(string nameOrCode, int type); // 모든 창고를 탐색하여 <이름 및 코드>를 가진 Product 배열을 반환
	Product* FindProduct(string lotation, string nameOrCode, int type); // 위치 정보(선반)에 위치한 <이름 및 코드>를 가진 Product를 반환
	vector<Record_data*> FindRecord(string productNameOrCode, int type); // <이름 및 코드>를 가진 Product의 모든 입출력 현황을 반환
	Shelf* FindShelf(Product product); // product가 존재하는 shelf를 반환
	Shelf* FindShelf(string lotation); // location(위치)에 해당하는 shelf를 반환
	bool LoadData(); // txt 파일의 내용을 데이터로 불러오기
	void SaveData(); // 데이터를 txt 파일로 저장
	Warehouse* getWarehouses() const; // 모든 창고 정보 반환
	vector<Record_data> getRecords() const; // 모든 입출력 현황 반환
	string getNewPID(); // 현재 사용가능한 PID를 반환
	void addRecord(Record_data record); // Record 추가
};