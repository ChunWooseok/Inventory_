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
	Warehouse* warehouses; // â�� ����
	vector<Record_data> records; // ����� ��Ȳ ����
	DataController() { warehouses = new Warehouse[MAX_WAHEHOUSE_NUM]; }
	~DataController() {}
public:
	static DataController& GetInstance() // �̱��� ����
	{
		static DataController* instance = new DataController();
		return *instance;
	}
	vector<Product*> FindProduct(string lotation); // ��ġ ����(����)�� ��ġ�� Product �迭�� ��ȯ
	vector<Product*> FindProduct(string nameOrCode, int type); // ��� â�� Ž���Ͽ� <�̸� �� �ڵ�>�� ���� Product �迭�� ��ȯ
	Product* FindProduct(string lotation, string nameOrCode, int type); // ��ġ ����(����)�� ��ġ�� <�̸� �� �ڵ�>�� ���� Product�� ��ȯ
	vector<Record_data*> FindRecord(string productNameOrCode, int type); // <�̸� �� �ڵ�>�� ���� Product�� ��� ����� ��Ȳ�� ��ȯ
	Shelf* FindShelf(Product product); // product�� �����ϴ� shelf�� ��ȯ
	Shelf* FindShelf(string lotation); // location(��ġ)�� �ش��ϴ� shelf�� ��ȯ
	bool LoadData(); // txt ������ ������ �����ͷ� �ҷ�����
	void SaveData(); // �����͸� txt ���Ϸ� ����
	Warehouse* getWarehouses() const; // ��� â�� ���� ��ȯ
	vector<Record_data> getRecords() const; // ��� ����� ��Ȳ ��ȯ
	string getNewPID(); // ���� ��밡���� PID�� ��ȯ
	void addRecord(Record_data record); // Record �߰�
};