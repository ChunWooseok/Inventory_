#include "DataController.h"

vector<string> split(string input, char delimiter);

bool checkDate(string time)
{
	// ���Ἲ Ȯ��
	int count = 0;
	for (int i = 0; i < time.length(); i++)
		if (time[i] == '/')
			count++;
	if (count != 2)
		return false;

	char arr[32];
	::strcpy(arr, time.c_str());
	string s1 = strtok(arr, "/");
	string s2 = strtok(NULL, "/");
	string s3 = strtok(NULL, "/");
	int year = atoi(s1.c_str());
	int month = atoi(s2.c_str());
	int day = atoi(s3.c_str());

	if (month < 1 || month > 12) return false;

	if ((month % 2 == 1)) //odd month   
	{
		if (month <= 7)
		{
			if (day <= 0 || day > 31) return false;
			else return true;
		}
		else // month > 7   
		{
			if (day <= 0 || day > 30) return false;
			else return true;
		}
	}
	else //even month  
	{
		if (month <= 6)
		{
			if (month == 2)
			{
				if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) // leap year  
				{
					if (day <= 0 || day > 30) return false;
					else return true;
				}
				else
				{
					if (day <= 0 || day > 28) return false;
					else return true;
				}
			}
			if (day <= 0 || day > 30) return false;
			else return true;
		}
		else
		{ // month > 6  
			if (day <= 0 || day > 31) return false;
			else return true;
		}
	}
}

bool checkFourNum(string str, int start)
{
	if (str.length() != 4) return false;
	char ch[1024];
	::strcpy(ch, str.c_str());

	int index1 = ch[0] - '0';
	if (index1 < start || index1 > 9) return false;
	int index2 = ch[1] - '0';
	if (index2 < start || index2 > 9) return false;
	int index3 = ch[2] - '0';
	if (index3 < start || index3 > 9) return false;
	int index4 = ch[3] - '0';
	if (index4 < start || index4 > 9) return false;

	return true;
}

bool checkWeight(string str)
{
	//0.00�������� Ȯ��
	//15.00 1.15 3.40 ���� / .52 324 3.512 �Ұ���
	//.�� �������� ������ ���ڸ��� 
	vector<string> temp;
	temp = split(str, '.');
	bool isNotZero = false;
	double d;

	if (str.size() == 0)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}

	if (temp.size() != 2)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	if (temp[0].size() == 0)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	for (int i = 0; i < temp[0].size(); i++)
	{
		if (isdigit(temp[0][i]) == 0) //������ �ƴ� ���� ���� ���
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
		if (temp[0][i] == '0' && !isNotZero && temp[0].size() != 1) //���� ó�� �ڸ��� 0�� ���ų� 0�� �ϳ��� �ƴ� ���
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
		else
		{
			isNotZero = true;
		}
	}
	if (temp[1].size() != 2)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	for (int i = 0; i < temp[1].size(); i++)
	{
		if (isdigit(temp[1][i]) == 0) //������ �ƴ� ���� ���� ���
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
	}
	try
	{
		d = stod(str);
	}
	catch (const std::exception& expn)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	if (d == 0)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}

	return true;
}

// Location 4�ڸ� int�� (x,y,z,w) �迭�� ��ȯ
void separateLocation(int location, int* out)
{
	out[0] = location / 1000 - 1;
	out[1] = location % 1000 / 100 - 1;
	out[2] = location % 100 / 10 - 1;
	out[3] = location % 10 - 1;
}

vector<Product*> DataController::FindProduct(string lotation)
{
	vector<Product*> returnval;
	vector<Product> data;
	char arr[1024];
	::strcpy(arr, lotation.c_str());

	int index1 = arr[0] - '0';
	int index2 = arr[1] - '0';
	int index3 = arr[2] - '0';
	int index4 = arr[3] - '0';
	returnval = this->warehouses[index1 - 1].getShelfs()[index2 - 1][index3 - 1][index4 - 1].getProducts_p();

	return returnval;
}

vector<Product*> DataController::FindProduct(string data, int type)
{
	vector<Product*> returnval;

	for (int w = 0; w < MAX_WAHEHOUSE_NUM; w++)
	{
		for (int x = 0; x < MAX_WAHEHOUSE_NUM; x++)
		{
			for (int y = 0; y < MAX_WAHEHOUSE_NUM; y++)
			{
				for (int z = 0; z < MAX_WAHEHOUSE_NUM; z++)
				{
					if (this->warehouses[w].getIsUse() && this->warehouses[w].getShelfs()[x][y][z].getIsUse() && !this->warehouses[w].getShelfs()[x][y][z].isEmpty())
					{
						// ��ġ(w,x,y,z)�� Product ���� �ϴ� ���
						vector<Product*> products = this->warehouses[w].getShelfs()[x][y][z].getProducts_p();
						for (int i = 0; i < products.size(); i++)
						{
							if (type == 0 && data == products[i]->getName() || type == 1 && data == products[i]->getID())
								returnval.push_back(products[i]);
						}
					}
				}
			}
		}
	}

	return returnval;
}

Product* DataController::FindProduct(string lotation, string data, int type)
{
	Product* returnval = NULL;
	vector<Product*> products = FindProduct(lotation);

	for (int i = 0; i < products.size(); i++)
	{
		if (type == 0 && data == products[i]->getName() || type == 1 && data == products[i]->getID())
			returnval = products[i];
	}

	return returnval;
}

vector<Record_data*> DataController::FindRecord(string data, int type)
{
	vector<Record_data*> records;

	for (int i = 0; i < this->records.size(); i++)
	{
		if (type == 0 && this->records[i].getName() == data || type == 1 && this->records[i].getPID() == data)
			records.push_back(&this->records[i]);
	}

	return records;
}

Shelf* DataController::FindShelf(Product product)
{
	Shelf* returnval = NULL;

	for (int w = 0; w < MAX_WAHEHOUSE_NUM; w++)
	{
		for (int x = 0; x < MAX_WAHEHOUSE_NUM; x++)
		{
			for (int y = 0; y < MAX_WAHEHOUSE_NUM; y++)
			{
				for (int z = 0; z < MAX_WAHEHOUSE_NUM; z++)
				{
					if (this->warehouses[w].getIsUse() && this->warehouses[w].getShelfs()[x][y][z].getIsUse() && !this->warehouses[w].getShelfs()[x][y][z].isEmpty())
					{
						// ��ġ(w,x,y,z)�� Product ���� �ϴ� ���
						vector<Product*> products = this->warehouses[w].getShelfs()[x][y][z].getProducts_p();
						for (int i = 0; i < products.size(); i++)
						{
							if (product.getName() == products[i]->getName() && product.getLoc() == products[i]->getLoc())
							{
								returnval = &this->warehouses[w].getShelfs()[x][y][z];
								break;
							}
						}
					}
				}
			}
		}
	}

	return returnval;
}

Shelf* DataController::FindShelf(string lotation)
{
	Shelf* returnval = NULL;
	char arr[256];
	::strcpy(arr, lotation.c_str());

	int index1 = arr[0] - '0';
	int index2 = arr[1] - '0';
	int index3 = arr[2] - '0';
	int index4 = arr[3] - '0';
	returnval = &this->warehouses[index1 - 1].getShelfs()[index2 - 1][index3 - 1][index4 - 1];

	return returnval;
}

bool DataController::LoadData()
{
	ifstream read;
	// �̹� ������ â���ΰ�?
	bool checkWarehouse[10] = { false, };
	// Shelf ����
	bool shelf[10][10][10][10] = { false, };
	// ShelfMaxWeight
	double shelfMaxWeight[10][10][10][10] = { 0.0, };

	// SettingWarehouse.txt ������ ��ȯ
	read.open("./Inventory_Files/SettingWarehouses.txt", ios_base::in);
	if (read.is_open()) // ������ ���ȴ��� Ȯ��
	{
		while (!read.eof()) // ���� ������ Ȯ��
		{
			if (read.peek() == std::ifstream::traits_type::eof()) break;

			bool checkError = false;
			// txt �� ��
			char arr[256];

			read.getline(arr, 1024); // �� �� �б�

			// ���Ἲ Ȯ��
			int count = 0;
			int length = sizeof(arr) / sizeof(arr[0]);
			for (int i = 0; i < length; i++)
			{
				if (arr[i] == '.') checkError = true;
				if (arr[i] == '-')
				{
					count++;
					if (i == 0 || (i != length - 1 && arr[i + 1] == '-'))
					{
						cout << "�� ����! SettingWarehouses.txt ������ �ùٸ��� �ʽ��ϴ�." << endl;
						_rmdir("./Inventory_Files");
						for (int i = 0; i < MAX_WAHEHOUSE_NUM; i++)
							warehouses[i].setIsUse(false);
						records.clear();
						return false;
					}
				}
			}
			if (count != 1)
			{
				cout << "�� ����! SettingWarehouses.txt ������ �ùٸ��� �ʽ��ϴ�." << endl;
				_rmdir("./Inventory_Files");
				for (int i = 0; i < MAX_WAHEHOUSE_NUM; i++)
					warehouses[i].setIsUse(false);
				records.clear();
				return false;
			}

			int location = atoi(strtok(arr, "-"));
			if (location < 1111 || location > 9999) checkError = true;
			char* maxWeight_s = strtok(NULL, "-");
			if (maxWeight_s[0] == '0') checkError = true;
			int maxWeight = atoi(maxWeight_s);
			if (maxWeight <= 0 || maxWeight > 999) checkError = true;

			if (checkError)
			{
				cout << "�� ����! SettingWarehouses.txt ������ �ùٸ��� �ʽ��ϴ�." << endl;
				_rmdir("./Inventory_Files");
				for (int i = 0; i < MAX_WAHEHOUSE_NUM; i++)
					warehouses[i].setIsUse(false);
				records.clear();
				return false;
			}

			int location_arr[4] = { 0, };
			separateLocation(location, location_arr);
			checkWarehouse[location_arr[0]] = true;
			shelf[location_arr[0]][location_arr[1]][location_arr[2]][location_arr[3]] = true;
			shelfMaxWeight[location_arr[0]][location_arr[1]][location_arr[2]][location_arr[3]] = maxWeight;
		}
	}
	else
		cout << "Failed to Open 'SettingWarehouses.txt' File" << endl;
	read.close();

	// Setting Warehouses Datas
	for (int n = 0; n < MAX_WAHEHOUSE_NUM; n++)
	{
		if (checkWarehouse[n])
		{
			// ����, ���� �ߺ� üũ
			bool c_x1[10] = { false, };
			bool c_x2[10][10] = { false, };
			// â���� ����, ����, �� ����
			int x1 = 0; int x2 = 0; int x3 = 0;

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					for (int k = 0; k < 10; k++)
					{
						if (shelf[n][i][j][k])
						{
							if (!c_x1[i])
							{
								c_x1[i] = true;
								x1++;
							}
							if (!c_x2[i][j])
							{
								c_x2[i][j] = true;
								x2++;
							}
							x3++;
						}
					}
				}
			}

			Warehouse data(x1, x2, x3, true);

			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					for (int k = 0; k < 10; k++)
						if (shelf[n][i][j][k])
							data.getShelfs()[i][j][k] = Shelf(shelfMaxWeight[n][i][j][k], true);

			warehouses[n] = data;
		}
	}

	/*
	for (int n = 0; n < 10; n++)
	{
		cout << n << " : ��� warehouses Ž��" << endl;
		if (warehouses[n].getIsUse())
			cout << n << " : " << this->warehouses[n].getX1() << endl;

		cout << n << " : ��� Shelfs Ž��" << endl;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				for (int k = 0; k < 10; k++)
					if (warehouses[n].getIsUse() && warehouses[n].getShelfs()[i][j][k].getIsUse())
						cout << n << i << j << k << " : " << warehouses[n].getShelfs()[i][j][k].getMaxWeight() << endl;
	}
	*/

	// Product.txt ������ ��ȯ
	read.open("./Inventory_Files/Product.txt", ios_base::in);
	if (read.is_open()) // ������ ���ȴ��� Ȯ��
	{
		while (!read.eof()) // ���� ������ Ȯ��
		{
			if (read.peek() == std::ifstream::traits_type::eof()) break;

			bool checkError = false;
			char arr[1024];
			unsigned char h[1024];
			read.getline(arr, 1024); // �� �� �б�

			// ���Ἲ Ȯ��
			int count = 0;
			int length = sizeof(arr) / sizeof(arr[0]);
			for (int i = 0; i < length; i++)
			{
				if (arr[i] == '-')
				{
					count++;
					if (i != length - 1 && arr[i + 1] == '-')
					{
						cout << "�� ����! Product.txt ������ �ùٸ��� �ʽ��ϴ�." << endl;
						_rmdir("./Inventory_Files");
						for (int i = 0; i < MAX_WAHEHOUSE_NUM; i++)
							warehouses[i].setIsUse(false);
						records.clear();
						return false;
					}
				}
			}
			if (count != 4)
			{
				cout << "�� ����! Product.txt ������ �ùٸ��� �ʽ��ϴ�." << endl;
				_rmdir("./Inventory_Files");
				for (int i = 0; i < MAX_WAHEHOUSE_NUM; i++)
					warehouses[i].setIsUse(false);
				records.clear();
				return false;
			}

			string s1 = strtok(arr, "-");
			if (!checkFourNum(s1, 0)) checkError = true;
			string s2 = strtok(NULL, "-");
			strcpy((char*)h, s2.c_str());
			if (s2.length() == 0 || _mbslen(h) > 16) checkError = true;
			string s3 = strtok(NULL, "-");
			if (!checkWeight(s3)) checkError = true;
			string s4 = strtok(NULL, "-");
			if (!checkFourNum(s4, 1)) checkError = true;
			int x1 = atoi(strtok(NULL, "-"));
			if (x1 <= 0 || x1 > 9999) checkError = true;

			char lotation[1024];
			::strcpy(lotation, s4.c_str());

			int index1 = lotation[0] - '0';
			int index2 = lotation[1] - '0';
			int index3 = lotation[2] - '0';
			int index4 = lotation[3] - '0';

			if (checkError)
			{
				cout << "�� ����! Product.txt ������ �ùٸ��� �ʽ��ϴ�." << endl;
				_rmdir("./Inventory_Files");
				for (int i = 0; i < MAX_WAHEHOUSE_NUM; i++)
					warehouses[i].setIsUse(false);
				records.clear();
				return false;
			}

			Product data(s1, s2, s3, s4, x1);
			cout << index1 << index2 << index3 << index4 << " : " << endl;
			cout << warehouses[index1 - 1].getX1() << endl;
			warehouses[index1 - 1].addProduct(index2, index3, index4, data);
		}
	}
	else
		cout << "Failed to Open 'Product.txt' File" << endl;
	read.close();

	read.open("./Inventory_Files/Record.txt", ios_base::in);
	if (read.is_open()) // ������ ���ȴ��� Ȯ��
	{
		while (!read.eof()) // ���� ������ Ȯ��
		{
			if (read.peek() == std::ifstream::traits_type::eof()) break;

			bool checkError = false;
			char arr[1024];
			unsigned char h[1024];
			read.getline(arr, 1024); // �� �� �б�

			// ���Ἲ Ȯ��
			int count = 0;
			int length = sizeof(arr) / sizeof(arr[0]);
			for (int i = 0; i < length; i++)
			{
				if (arr[i] == '-')
				{
					count++;
					if (i != length - 1 && arr[i + 1] == '-')
					{
						cout << "�� ����! Record.txt ������ �ùٸ��� �ʽ��ϴ�." << endl;
						_rmdir("./Inventory_Files");
						for (int i = 0; i < MAX_WAHEHOUSE_NUM; i++)
							warehouses[i].setIsUse(false);
						records.clear();
						return false;
					}
				}
			}
			if (count != 5)
			{
				cout << "�� ����! Record.txt ������ �ùٸ��� �ʽ��ϴ�." << endl;
				_rmdir("./Inventory_Files");
				for (int i = 0; i < MAX_WAHEHOUSE_NUM; i++)
					warehouses[i].setIsUse(false);
				records.clear();
				return false;
			}

			string s1 = strtok(arr, "-");
			string s2 = strtok(NULL, "-");
			if (s2 != "�԰�" && s2 != "���") checkError = true;
			string s3 = strtok(NULL, "-");
			if (!checkFourNum(s3, 1)) checkError = true;
			string s4 = strtok(NULL, "-");
			if (!checkFourNum(s4, 0)) checkError = true;
			string s5 = strtok(NULL, "-");
			strcpy((char*)h, s5.c_str());
			if (s5.length() == 0 || _mbslen(h) > 16) checkError = true;
			int x1 = atoi(strtok(NULL, "-"));
			if (x1 <= 0 || x1 > 9999) checkError = true;
			if (!checkDate(s1)) checkError = true;

			if (checkError)
			{
				cout << "�� ����! Record.txt ������ �ùٸ��� �ʽ��ϴ�." << endl;
				_rmdir("./Inventory_Files");
				for (int i = 0; i < MAX_WAHEHOUSE_NUM; i++)
					warehouses[i].setIsUse(false);
				records.clear();
				return false;
			}

			Record_data data(s1, s2, s3, s4, s5, x1);
			this->records.push_back(data);
		}
		sort(this->records.begin(), this->records.end()); // �ð� ���� �����ϱ�
	}
	else
		cout << "Failed to Open 'Record.txt' File" << endl;
	read.close();
	return true;
}

void DataController::SaveData()
{
	ofstream write;

	// SettingWarehouse.txt�� ����
	string last = "0000";
	write.open("./Inventory_Files/SettingWarehouses.txt", ios_base::out);
	// last shelf Ž��
	for (int w = 0; w < MAX_WAHEHOUSE_NUM; w++)
		for (int x = 0; x < MAX_WAHEHOUSE_NUM; x++)
			for (int y = 0; y < MAX_WAHEHOUSE_NUM; y++)
				for (int z = 0; z < MAX_WAHEHOUSE_NUM; z++)
					if (this->warehouses[w].getIsUse() && this->warehouses[w].getShelfs()[x][y][z].getIsUse())
						last = to_string(w) + to_string(x) + to_string(y) + to_string(z);

	for (int w = 0; w < MAX_WAHEHOUSE_NUM; w++)
	{
		for (int x = 0; x < MAX_WAHEHOUSE_NUM; x++)
		{
			for (int y = 0; y < MAX_WAHEHOUSE_NUM; y++)
			{
				for (int z = 0; z < MAX_WAHEHOUSE_NUM; z++)
				{
					if (this->warehouses[w].getIsUse() && this->warehouses[w].getShelfs()[x][y][z].getIsUse())
					{
						string str = to_string(w + 1) + to_string(x + 1) + to_string(y + 1) + to_string(z + 1) + "-" + to_string(this->warehouses[w].getShelfs()[x][y][z].getMaxWeight());
						if (last.compare(to_string(w) + to_string(x) + to_string(y) + to_string(z)) == 1) str += "\n";
						write << str;
					}
				}
			}
		}
	}
	write.close();

	// Product.txt�� ����
	vector<Product> products;
	write.open("./Inventory_Files/Product.txt", ios_base::out);
	for (int w = 0; w < MAX_WAHEHOUSE_NUM; w++)
	{
		for (int x = 0; x < MAX_WAHEHOUSE_NUM; x++)
		{
			for (int y = 0; y < MAX_WAHEHOUSE_NUM; y++)
			{
				for (int z = 0; z < MAX_WAHEHOUSE_NUM; z++)
				{
					if (this->warehouses[w].getIsUse() && this->warehouses[w].getShelfs()[x][y][z].getIsUse() && !this->warehouses[w].getShelfs()[x][y][z].isEmpty())
					{
						// ��ġ(w,x,y,z)�� Product ���� �ϴ� ���
						vector<Product> data = this->warehouses[w].getShelfs()[x][y][z].getProducts();
						for (int i = 0; i < data.size(); i++)
							products.push_back(data[i]);
					}
				}
			}
		}
	}

	for (int i = 0; i < products.size(); i++)
	{
		string weight = to_string(products[i].getWeight());
		int count = 0;
		// �Ҽ��� �ڸ���
		for (int j = 0; j < weight.length(); j++)
		{
			if (weight[j] != '.') count++;
			else
			{
				count += 3;
				break;
			}
		}

		string str = products[i].getID() + "-" + products[i].getName() + "-" + weight.substr(0, count) + "-" + products[i].getLoc() + "-" + to_string(products[i].getNum());
		if (i != products.size() - 1) str += "\n";
		write << str;
	}
	write.close();

	// Record.txt�� ����
	write.open("./Inventory_Files/Record.txt", ios_base::out);
	for (int i = 0; i < this->records.size(); i++)
	{
		string str = this->records[i].getTime() + "-" + this->records[i].getKind() + "-" + this->records[i].getLoc() + "-" + this->records[i].getPID()
			+ "-" + this->records[i].getName() + "-" + to_string(this->records[i].getNum());
		if (i != this->records.size() - 1) str += "\n";
		write << str;
	}
	write.close();
}

Warehouse* DataController::getWarehouses() const
{
	return this->warehouses;
}

vector<Record_data> DataController::getRecords() const
{
	return this->records;
}

string DataController::getNewPID()
{
	bool data[9999];
	int index = -1;
	for (int i = 0; i < sizeof(data); i++)
		data[i] = false;

	for (int w = 0; w < MAX_WAHEHOUSE_NUM; w++)
	{
		for (int x = 0; x < MAX_WAHEHOUSE_NUM; x++)
		{
			for (int y = 0; y < MAX_WAHEHOUSE_NUM; y++)
			{
				for (int z = 0; z < MAX_WAHEHOUSE_NUM; z++)
				{
					if (this->warehouses[w].getIsUse() && this->warehouses[w].getShelfs()[x][y][z].getIsUse() && !this->warehouses[w].getShelfs()[x][y][z].isEmpty())
					{
						// ��ġ(w,x,y,z)�� Product ���� �ϴ� ���
						vector<Product> products = this->warehouses[w].getShelfs()[x][y][z].getProducts();
						for (int i = 0; i < products.size(); i++)
						{
							if (!data[atoi(products[i].getID().c_str())])
								data[atoi(products[i].getID().c_str())] = true;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < sizeof(data); i++)
	{
		if (!data[i])
		{
			index = i;
			break;
		}
	}

	// ���� ������ ���� ���
	if (index == -1) return "FULL";

	string returnval = "0000";
	returnval[0] = index / 1000 + '0';
	returnval[1] = index % 1000 / 100 + '0';
	returnval[2] = index % 100 / 10 + '0';
	returnval[3] = index % 10 + '0';

	return returnval;
}

void DataController::addRecord(Record_data record)
{
	this->records.push_back(record);
}