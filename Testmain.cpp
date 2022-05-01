#include <iostream>
#include <windows.h> // cls
#include <fstream> // file
#include <string>
#include <regex>
#include <direct.h>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>
#include <cctype>
#include "DataController.h"
using namespace std;

void setwarehouse();
void checkfile();
void printmenu();
vector<string> split(string input, char delimiter);
bool compare(tuple<string, string, string, string, string, int> a, tuple<string, string, string, string, string, int> b);
bool isNumber(const string& str);
int PrintInventory();
int menu5();
int menu6(DataController& dataController);
void removeWarehouse(DataController& dataController);
int add_Warehouses();
void ModWare(DataController& dataController);

//======����� ��� �Լ�====
void Store(DataController& dataController);
void Release(DataController& dataController);
void MoveProduct(DataController& dataController);

//======���� Ȯ�� �Լ�======
bool CheckLocationForm(string& location);
bool CheckNameForm(string& name);
bool CheckCountForm(string count);
bool CheckWeightForm(string weight);
bool CheckDateForm(string& date);
bool CheckHyphenNum(string str, int num);

//=======��Ģ Ȯ�� �Լ�=======
bool CheckNameCountLocation(string name, string count, string location, DataController& dataController);
bool CheckRealLocation(string location, DataController& dataController);
bool CheckRealName(string name, string location, DataController& dataController);
bool CheckWeightRule(string weight, string count, string location, DataController& dataController);
bool CheckDateRule(string rel_date, string str_date);
bool CheckNameWeight(string name, string weight, DataController& dataController);
bool CheckSameLocation(string rel_location, string str_location);
bool CheckSameLocationForRecord(string rel_location, string str_location);
bool CheckDateCountRule(string name, string count, string location, string date, DataController& dataController);
bool CheckMaxWeightForm(string maxWeight);
bool CheckMaxWeightForm_add(string maxWeight);
bool CheckModWeight(string location, string weight, DataController& dataController);
bool CheckModLocation(string location, DataController& dataController);


DataController& dataController = DataController::GetInstance();

void checkfile()
{

	bool flag = false; //������ �ϳ��� ������ true 

	ifstream read;
	ofstream write;

	read.open("./Inventory_Files/SettingWarehouses.txt");
	if (!read.good())
	{
		_rmdir("./Inventory_Files");
		_mkdir("./Inventory_Files");
		setwarehouse();
		cout << "SettingWarehouse.txt �б����!" << endl;
		flag = true;
	}
	read.close();

	read.open("./Inventory_Files/Record.txt");
	if (!read.good())
	{
		cout << "Record.txt �б����!" << endl;
		_rmdir("./Inventory_Files");
		_mkdir("./Inventory_Files");
		setwarehouse();
		flag = true;
	}
	read.close();

	read.open("./Inventory_Files/Product.txt");
	if (!read.good())
	{
		cout << "Product.txt �б����!" << endl;
		_rmdir("./Inventory_Files");
		_mkdir("./Inventory_Files");
		setwarehouse();
		flag = true;
	}
	read.close();

	read.open("./Inventory_Files/SettingWarehouses.txt");
	if (read.peek() == ifstream::traits_type::eof())
	{ //������ �ִµ� ����������
		_rmdir("./Inventory_Files");
		_mkdir("./Inventory_Files");
		setwarehouse();
		flag = true;
	}
	read.close();

	return;
}

void setwarehouse()
{
	string input;
	int warehouse_num, block_num, shelf_num, floor_num; //����
	int warehouse, block, shelf, floor, weight = 0, count = 0; //â�� ����
	ofstream write;
	int warehouses[10][10][10][10] = { 0, };
	vector<string> vec;

	cout << "[Inventory Management Program]" << endl;
	cout << "������ â���� ������ �Է��ϼ���." << endl << ">>";

	while (true)
	{
		getline(cin, input);
		//cout << input;
		if ('0' < input[0] && input[0] <= '9' && input.size() == 1)
		{ //â��� 0�� 9������ ���ڸ� ����
			warehouse_num = input[0] - '0';
			break;
		}
		else
		{
			system("cls");
			cout << "[Inventory Management Program]" << endl;
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
			cout << "������ â���� ������ �Է��ϼ���." << endl << ">>";
		}
	}
	system("cls");
	for (int i = 1; i <= warehouse_num; i++)
	{
		cout << i << "��° â���� â���ȣ �� �������� �Է��ϼ���" << endl << ">>";
		while (true)
		{
			getline(cin, input);
			//cout << input;
			if ('0' < input[0] && input[0] <= '9' && input.size() == 3 && '0' < input[2] && input[2] <= '9' && input[1] == ',')
			{ //â��� 0�� 9������ ���ڸ� ����
				warehouse = input[0] - '0';
				block_num = input[2] - '0';
				if (warehouses[warehouse][0][0][0] == 0)
				{
					warehouses[warehouse][0][0][0] = block_num;
					break;
				}
				else
				{
					cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
					cout << i << "��° â���� â���ȣ �� �������� �Է��ϼ���" << endl << ">>";
				}

			}
			else
			{
				//system("cls");
				//cout << "[Inventory Management Program]" << endl;
				cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
				cout << i << "��° â���� â���ȣ �� �������� �Է��ϼ���" << endl << ">>";
			}
		}

		for (int j = 1; j <= block_num; j++)
		{
			cout << "  " << j << "��° ������ ������ȣ �� ���ݰ����� �Է��ϼ���" << endl << "  >>";
			while (true)
			{
				getline(cin, input);
				//cout << input;
				if ('0' < input[0] && input[0] <= '9' && input.size() == 3 && '0' < input[2] && input[2] <= '9' && input[1] == ',')
				{ //â��� 0�� 9������ ���ڸ� ����
					block = input[0] - '0';
					shelf_num = input[2] - '0';
					if (warehouses[warehouse][block][0][0] == 0)
					{
						warehouses[warehouse][block][0][0] = shelf_num;
						break;
					}
					else
					{
						cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
						cout << "  " << j << "��° ������ ������ȣ �� ���ݰ����� �Է��ϼ���" << endl << "  >>";
					}
				}
				else
				{
					//system("cls");
					//cout << "[Inventory Management Program]" << endl;
					cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
					cout << "  " << j << "��° ������ ������ȣ �� ���ݰ����� �Է��ϼ���" << endl << "  >>";
				}
			}
			for (int k = 1; k <= shelf_num; k++)
			{
				cout << "    " << k << "��° ������ ���ݹ�ȣ �� ������ �Է��ϼ���" << endl << "    >>";
				while (true)
				{
					getline(cin, input);
					//cout << input;
					if ('0' < input[0] && input[0] < '9' && input.size() == 3 && '0' < input[2] && input[2] <= '9' && input[1] == ',')
					{ //â��� 0�� 9������ ���ڸ� ����
						shelf = input[0] - '0';
						floor_num = input[2] - '0';
						if (warehouses[warehouse][block][shelf][0] == 0)
						{
							warehouses[warehouse][block][shelf][0] = floor_num;
							break;
						}
						else
						{
							cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
							cout << "    " << k << "��° ������ ���ݹ�ȣ �� ������ �Է��ϼ���" << endl << "    >>";
						}
					}
					else
					{
						//system("cls");
						//cout << "[Inventory Management Program]" << endl;
						cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
						cout << "    " << k << "��° ������ ���ݹ�ȣ �� ������ �Է��ϼ���" << endl << "    >>";
					}
				}
				for (int e = 1; e <= floor_num; e++)
				{
					cout << "      " << e << "��° ���� ����ȣ �� ���Ը� �Է��ϼ���" << endl << "      >>";
					while (true)
					{
						getline(cin, input);
						bool flag = true;
						int size = input.size() - 2;
						//cout << size;
						//cout << input;
						if (input.size() > 3 && input.size() <= 5)
						{
							for (int a = 3; a < input.size(); a++)
							{
								if ('0' > input[a] || input[a] > '9')
								{
									//cout << "�ɸ�" << endl;
									flag = false;
								}
							}
						}

						if ('0' < input[0] && input[0] <= '9' && input.size() >= 3 && input.size() <= 5 && '0' < input[2] && input[2] <= '9' && flag && input[1] == ',')
						{ //â��� 0�� 9������ ���ڸ� ����
							//cout << input << endl;
							floor = input[0] - '0';
							//weight = input[1] - '0';
							if (size == 3)
							{
								//cout << "3" << endl;
								weight += (input[2] - '0') * 100;
								weight += (input[3] - '0') * 10;
								weight += input[4] - '0';
							}
							else if (size == 2)
							{
								//cout << "2" << endl;
								weight += (input[2] - '0') * 10;
								weight += (input[3] - '0');
							}
							else if (size == 1)
							{
								//cout << "1" << endl;
								weight = input[2] - '0';
							}
							if (warehouses[warehouse][block][shelf][floor] == 0)
							{
								warehouses[warehouse][block][shelf][floor] = weight;
								//cout << weight << endl;
								weight = 0;
								//cout << warehouse << " " << block << " " << shelf << " " << floor << " " << warehouses[warehouse][block][shelf][floor]<<endl;
								count++;
								break;
							}
							else
							{
								cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
								cout << "      " << e << "��° ���� ����ȣ �� ���Ը� �Է��ϼ���" << endl << "      >>";
							}
						}
						else
						{
							//system("cls");
							//cout << "[Inventory Management Program]" << endl;
							cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
							cout << "      " << e << "��° ���� ����ȣ �� ���Ը� �Է��ϼ���" << endl << "      >>";
						}
					}
				}
			}
		}
	}

	write.open("./Inventory_Files/SettingWarehouses.txt");

	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			for (int k = 1; k < 10; k++)
			{
				for (int e = 1; e < 10; e++)
				{
					if (warehouses[i][j][k][e] != 0)
					{
						count--;
						if (count)
							write << i << j << k << e << "-" << warehouses[i][j][k][e] << endl;
						else
							write << i << j << k << e << "-" << warehouses[i][j][k][e];
					}
				}
			}
		}
	}

	write.close();
	write.open("./Inventory_Files/Record.txt");
	write.close();
	write.open("./Inventory_Files/Product.txt");
	write.close();

	cin.clear();

	//atexit(printmenu);

}


void printmenu()
{
	system("cls");

	int num;
	string input = "";

	cout << "[Inventory Management Program]" << endl;
	cout << "�޴��� �Է��ϼ���." << endl;
	cout << "(1) �԰� (2) ��� (3) �̵� (4) ��� ��Ȳ (5) ����� ��Ȳ (6) â���� (7) ����" << endl << ">>";
	//getline(cin, input);

	while (true)
	{

		getline(cin, input);

		if (input == "") {
			getline(cin, input);
			cout << "aaa";
		}

		if (input == "1" || input == "�԰�")
		{
			num = 1;
			break;
		}
		else if (input == "2" || input == "���")
		{
			num = 2;
			break;
		}
		else if (input == "3" || input == "�̵�")
		{
			num = 3;
			break;
		}
		else if (input == "4" || input == "��� ��Ȳ")
		{
			num = 4;
			break;
		}
		else if (input == "5" || input == "����� ��Ȳ")
		{
			num = 5;
			break;
		}
		else if (input == "6" || input == "â����")
		{
			num = 6;
			break;
		}
		else if (input == "7")
		{
			num = 7;
			break;
		}
		else
		{
			cin.clear();
			system("cls");
			cout << "[Inventory Management Program]" << endl;
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�." << endl;
			cout << "�޴��� �Է��ϼ���." << endl;
			cout << "(1) �԰� (2) ��� (3) �̵� (4) ��� ��Ȳ (5) ����� ��Ȳ (6) â���� (7) ����" << endl << ">>";
		}
	}


	switch (num)
	{
	case 1:
		//cout << "1" << endl;
		//���뿡 �� ����Լ� ������ �˴ϴ�!
		Store(dataController);
		break;
	case 2:
		//cout << "2" << endl;
		Release(dataController);
		break;
	case 3:
		//cout << "3" << endl;
		MoveProduct(dataController);
		break;
	case 4:
		PrintInventory();
		break;
	case 5:
		//cout << "5" << endl;
		menu5();
		break;
	case 6:
		//cout << "6" << endl;
		menu6(dataController);
		break;
	case 7:
		//cout << "5" << endl;
		exit(0);
		break;
	}

}

// split�ϴ� �Լ� ==> ���� : split(���ڿ�, �ɰ� ����)
vector<string> split(string input, char delimiter)
{

	vector<string> answer;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter))
	{
		answer.push_back(temp);
	}

	return answer;
}

bool compare(tuple<string, string, string, string, string, int> a, tuple<string, string, string, string, string, int> b)
{
	return get<0>(a) < get<0>(b);
}

bool isNumber(const string& str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}

int PrintInventory()
{
	atexit(printmenu);

	// ���� ����
	ifstream ifs;
	ifs.open("Inventory_Files/Product.txt");

	// ���� ���� ����
	if (!ifs)
	{
		cerr << "File Open error" << endl;
		exit(1);
	}

	// ���� ���� ����
	vector<string> s;														// ���Ͽ��� split�Ѱ� ��� vector
	tuple<string, string, string, string, string, int> s_tuple;				// split�Ѱ� tuple�� ���� �� ���� tuple
	vector<tuple<string, string, string, string, string, int>> result;		// tuple�� �ٽ� vector�� ����

	vector<string> Id;
	vector<string> Name;
	vector<string> Weight;
	vector<string> Location;
	vector<string> Number;
	int index = 0;															// ���߿� ���� ����ϱ� ���� index��

	// ���� �о vector�� tuple�� ����
	while (ifs)
	{
		string str;
		getline(ifs, str);

		// ������ ���� �� break
		if (str == "")
			break;

		s = split(str, '-');

		Id.push_back(s.at(0));
		Name.push_back(s.at(1));
		Weight.push_back(s.at(2));
		Location.push_back(s.at(3));
		Number.push_back(s.at(4));

		s_tuple = make_tuple(s.at(0), s.at(1), s.at(2), s.at(3), s.at(4), index);
		result.emplace_back(s_tuple);

		index++;
	}

	// result ID �������� ����
	sort(result.begin(), result.end(), compare);

	// �ߺ� ǰ�� ���� ��, �׸�ŭ ���� �߰�
	for (int i = 0; i < result.size(); i++)
	{

		for (int j = 0; j < result.size() - 1; j++)
		{

			if (get<0>(result[j]) == get<0>(result[j + 1]))
			{
				int now = stoi(get<4>(result[j]));
				int number = now + stoi(Number.at(get<5>(result[j + 1])));
				get<4>(result[j]) = to_string(number);
				result.erase(result.begin() + (j + 1));
				j--;
			}
		}
	}

	string choice;
	while (1)
	{
		cout << "\n[Inventory Management Program]" << endl;

		// [ID_1] | [�̸�1] | [a1]�� ���
		for (int i = 0; i < result.size(); i++)
		{
			cout << "(" << i + 1 << ") " << get<0>(result[i]) << " | " << get<1>(result[i]) << " | " << get<4>(result[i]) << "��" << endl;
		}

		cout << "\n================================================================\n" << endl;
		if (Id.size() == 0)
		{
			cout << "�� ����! �ƹ��� ��ǰ�� ��ϵǾ����� �ʽ��ϴ�." << endl;
		}
		else
			cout << "��ȣ�� �ش��ϴ� ����� �� ������ ���� �ʹٸ� ��ȣ�� �Է��ϼ���." << endl;

		cout << "(�޴��� ���ư����� 'q'�� �Է��ϼ���)" << endl;
		cout << ">>";
		getline(cin, choice);

		// q�Է� �� menu�� ���ư�
		if (choice == "q")
		{
			cin.clear();
			return 0;
		}

		// choice�� ���
		else if (isNumber(choice))
		{
			try
			{
				if ((stoi(choice) > static_cast<int>(result.size())) || (stoi(choice) == 0))
				{
					cout << "�� ����! ������ ��� ��ȣ�Դϴ�." << endl;
				}
				else
				{
					int choice_int = stoi(choice);

					cout << "[Inventory Management Program]" << endl;
					cout << get<0>(result[choice_int - 1]) << " | " << get<1>(result[choice_int - 1]) << " | " << get<4>(result[choice_int - 1]) << "��" << endl;

					// â�� ��ǰ ���
					int count = 1;
					for (int i = 0; i < Id.size(); i++)
					{
						if ((get<0>(result[choice_int - 1]) == Id[i]))
						{
							cout << fixed;
							cout.precision(2);
							cout << "\t" << "(" << count << ") " << Location[i] << " | " << Number[i] << " | " << stof(Weight[i]) * stoi(Number[i]) << " (kg)" << endl;
							count++;
						}
					}

					cout << "\n================================================================\n" << endl;
					cout << "(��� ��Ȳ���� ���ư����� 'q'�� �Է��ϼ���.)" << endl;

					while (1)
					{
						cout << ">>";
						getline(cin, choice);
						if (choice == "q")
							break;
						else
							cout << "�� ����! �ùٸ� �Է��� ���ּ���." << endl;
					}
				}
			}
			catch (const std::exception& expn)
			{
				cout << "�� ����! ������ ��� ��ȣ�Դϴ�." << endl;
			}
			catch (...)
			{
				cout << "�� ����! �ùٸ� �Է��� ���ּ���." << endl;
			}
		}

		// choice�� �����ų� �ٸ� ����
		else
		{
			cout << "�� ����! �ùٸ� �Է��� ���ּ���." << endl;
		}
	}
	cin.clear();
}

int main()
{
	checkfile();
	if (!dataController.LoadData()) setwarehouse();

	printmenu();

	dataController.SaveData();

	return 0;
}

bool sortRecordByDate(vector<string> v1, vector<string> v2)
{
	// menu5_2()���� record �����ϴ� �Լ�
	if (v1[0] > v2[0])
	{
		return true;
	}
	return false;
}

int menu5()
{
	atexit(printmenu);  // q�� �Է¹����� ���θ޴��� ���ư��� ��

	ifstream ifs;
	ifs.open("Inventory_Files/Record.txt");

	if (!ifs)
	{    // ���� ���� ����
		cerr << "Record.txt ���� ����" << endl;
		exit(1);
	}

	vector<vector<string>> data;
	while (ifs)
	{
		string str;
		getline(ifs, str);

		if (str == "")
		{    // ������ �ҷ���
			break;
		}
		vector<string> temp;
		temp = split(str, '-');
		data.push_back(temp);
	}
	ifs.close();

	cout << "[Inventory Management Program]" << '\n';
	cout << "����� ��Ȳ�� Ȯ���� ��� �̸��� �Է��ϼ���" << '\n';
	cout << "(�޴��� ���ư����� 'q'�� �Է��ϼ���)" << '\n';

	vector<vector<string>> result;
	string input;
	do
	{
		vector<vector<string>>().swap(result);  // result �ʱ�ȭ

		cout << ">>";
		getline(cin, input);
		input.erase(remove(input.begin(), input.end(), ' '), input.end());

		for (int i = 0; i < data.size(); i++)
		{
			if (data[i][4] == input)
			{
				result.push_back(data[i]);
			}
		}

		if (result.size() == 0)
		{   // �Է¿� ���� ��ǰ�� ���ٸ�
			cout << "[Inventory Management Program]" << '\n';
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n";
		}

		sort(result.begin(), result.end(), sortRecordByDate);   // ��¥ ������ ����
		for (int i = result.size() - 1; i >= 0; i--)
		{
			// ����� ��Ȳ ���
			cout << "(" << result.size() - i << ") " << result[i][0] << " | " << result[i][1] << " | " << result[i][5] << " | " << result[i][2] << '\n';
		}

	} while (input != "q");   // �Է¿� ���� ��ǰ�� ���� �� �ٽ� �Է��� �޵��� �ݺ�

	cin.clear();
	return 1;
}

void Store(DataController& dataController)//�԰� �Լ�
{
	atexit(printmenu);
	string inData;
	vector<string> inDataVec; // 0:�̸�, 1:����, 2:����, 3:��ġ, 4:��¥
	Product product;
	Shelf* shelf;

	while (1)
	{
		cout << "�԰��� ����� ������ ����, ��ġ, �԰� ��¥�� �Է��ϼ���." << endl;
		cout << "(�̸�-����-����-��ġ-�԰� ��¥)\n(�޴��� ���ư����� 'q'�� �Է��ϼ���)" << endl;
		getline(cin, inData);
		cin.clear();
		if (!CheckHyphenNum(inData, 4))
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			continue;
		}
		inDataVec = split(inData, '-');
		if (inDataVec.size() == 1)
		{
			if (inDataVec[0].compare("q") == 0)//q�� �Է��ϸ� ����
			{
				return;
			}
		}
		if (inDataVec.size() != 5)
		{
			cout << "�� ����! �Էµ� �������� ������ Ʋ���ϴ�.\n" << endl;
			continue;
		}
		if (!CheckNameForm(inDataVec[0])) continue; //�̸� ������ ���� ���� ���
		if (!CheckWeightForm(inDataVec[1])) continue; //���� ������ ���� ���� ���
		if (!CheckCountForm(inDataVec[2])) continue; //���� ������ ���� ���� ���
		if (!CheckLocationForm(inDataVec[3])) continue; //��ġ ������ ���� ���� ���
		if (!CheckDateForm(inDataVec[4])) continue; //��¥ ������ ���� ���� ���



		if (!CheckModLocation(inDataVec[3], dataController)) continue; //�Է��� ��ġ�� �������� ���� ���
		if (!CheckWeightRule(inDataVec[1], inDataVec[2], inDataVec[3], dataController)) continue; //���� ���Ը� �ʰ��ϴ� ���

		if (CheckRealName(inDataVec[0], inDataVec[3], dataController)) //�Է��� ��ǰ�� �̹� �ִ� ��ǰ�� ���
		{
			if (!CheckNameWeight(inDataVec[0], inDataVec[1], dataController))  continue; //��ǰ�� ������ ��ϵ� ������ �ٸ� ���
			vector<Product*> data = dataController.FindProduct(inDataVec[0], 0);
			string cur_productID = data[0]->getID();
			product = Product::Product(cur_productID, inDataVec[0], inDataVec[1], inDataVec[3], stoi(inDataVec[2]));
		}
		else //�������� ���� ��ǰ�� ��� ���ο� id�ο�
		{
			string newID = dataController.getNewPID();
			if (newID.compare("FULL") == 0)
			{
				cout << "�� ����! ���� ���α׷����� �����ϴ� ��ǰ�� ������ �ʹ� �����ϴ�." << endl;
				cout << "�� �̻� ǰ���ڵ带 �߰��� �� �����ϴ�.\n" << endl;
				system("PAUSE");
				return;
			}
			product = Product::Product(dataController.getNewPID(), inDataVec[0], inDataVec[1], inDataVec[3], stoi(inDataVec[2]));
		}

		shelf = dataController.FindShelf(inDataVec[3]);

		shelf->addPro(product);
		//�԰� ��� 

		//������ ���� �� ���� �� ����
		Record_data record = Record_data::Record_data(inDataVec[4], "�԰�", product.getLoc(), product.getID(), product.getName(), product.getNum());
		dataController.addRecord(record);
		dataController.SaveData();

		break;
	}
	cout << "�԰� ����" << endl;
	system("PAUSE");
	return;
}

void Release(DataController& dataController)//��� �Լ�
{
	atexit(printmenu);
	string inData;
	vector<string> inDataVec; // 0:�̸�, 1:����, 2:��ġ, 3:��� ��¥
	Product* product;
	Shelf* shelf;

	while (true)
	{
		cout << "����� ����� �̸��� ����, ��ġ, ��� ��¥�� �Է��ϼ���." << endl;
		cout << "(�̸�-����-��ġ-��� ��¥)\n(�޴��� ���ư����� 'q'�� �Է��ϼ���)" << endl;
		getline(cin, inData);
		cin.clear();
		if (!CheckHyphenNum(inData, 3))
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			continue;
		}
		inDataVec = split(inData, '-');
		if (inDataVec.size() == 1)
		{
			if (inDataVec[0].compare("q") == 0)//q�� �Է��ϸ� ����
			{
				return;
			}
		}
		if (inDataVec.size() != 4)
		{
			cout << "�Էµ� �������� ������ Ʋ���ϴ�." << endl;
			continue;
		}

		if (!CheckNameForm(inDataVec[0])) continue; //�̸� ������ ���� ���� ���
		if (!CheckCountForm(inDataVec[1])) continue; //���� ������ ���� ���� ���
		if (!CheckLocationForm(inDataVec[2])) continue; //��ġ ������ ���� ���� ���
		if (!CheckDateForm(inDataVec[3])) continue; //��¥ ������ ���� ���� ���

		if (!CheckModLocation(inDataVec[2], dataController)) continue; //�Է��� ��ġ�� �������� ���� ���
		if (!CheckNameCountLocation(inDataVec[0], inDataVec[1], inDataVec[2], dataController)) continue; //�ش� ��ġ�� ��ǰ�� ������ ������� ���� ���
		if (!CheckDateCountRule(inDataVec[0], inDataVec[1], inDataVec[2], inDataVec[3], dataController)) continue; //�Է��� ��¥�� �������� �� ������ �ش� ��ġ�� ��ǰ������ ������� Ȯ��

		product = dataController.FindProduct(inDataVec[2], inDataVec[0], 0);
		shelf = dataController.FindShelf(product->getLoc());

		Product temp_product;
		temp_product = Product::Product(*product);
		Record_data record(inDataVec[3], "���", product->getLoc(), product->getID(), product->getName(), stoi(inDataVec[1]));
		shelf->relPro(*product, stoi(inDataVec[1])); //������ŭ �ش� ���ݿ��� ���

		//��� ���

		dataController.addRecord(record);
		dataController.SaveData();
		break;
	}
	cout << "��� ����" << endl;
	system("PAUSE");
	return;
}

void MoveProduct(DataController& dataController)//�̵� �Լ�
{
	atexit(printmenu);
	string inData, locationData;
	vector<string> inDataVec; // 0:�̸�, 1:����, 2:��ġ, 3:��¥
	Product* product = NULL;
	Product temp_product;
	Shelf* shelf;

	while (true)
	{
		cout << "�̵��� ����� �̸��� ����, ��ġ, ��¥�� �Է��ϼ���." << endl;
		cout << "(�̸�-����-��ġ-��¥)\n(�޴��� ���ư����� 'q'�� �Է��ϼ���)" << endl;
		getline(cin, inData);
		cin.clear();
		if (!CheckHyphenNum(inData, 3))
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			continue;
		}
		inDataVec = split(inData, '-');
		if (inDataVec.size() == 1)
		{
			if (inDataVec[0].compare("q") == 0)//q�� �Է��ϸ� ����
			{
				return;
			}
		}
		if (inDataVec.size() != 4)
		{
			cout << "�Էµ� �������� ������ Ʋ���ϴ�." << endl;
			continue;
		}
		if (!CheckNameForm(inDataVec[0])) continue; //�̸� ������ ���� ���� ���
		if (!CheckCountForm(inDataVec[1])) continue; //���� ������ ���� ���� ���
		if (!CheckLocationForm(inDataVec[2])) continue; //��ġ ������ ���� ���� ���
		if (!CheckDateForm(inDataVec[3])) continue; //��¥ ������ ���� ���� ���

		if (!CheckModLocation(inDataVec[2], dataController)) continue; //�Է��� ��ġ�� �������� ���� ���
		if (!CheckNameCountLocation(inDataVec[0], inDataVec[1], inDataVec[2], dataController)) continue; //�ش� ��ġ�� ��ǰ�� ������ ������� ���� ���
		if (!CheckDateCountRule(inDataVec[0], inDataVec[1], inDataVec[2], inDataVec[3], dataController)) continue; //�Է��� ��¥�� �������� �� ������ �ش� ��ġ�� ��ǰ������ ������� Ȯ��

		product = dataController.FindProduct(inDataVec[2], inDataVec[0], 0);

		vector<Product*> tempVec = dataController.FindProduct(inDataVec[0], 0);


		for (int i = 0; i < tempVec.size(); i++)
		{
			if (tempVec[i]->getLoc().compare(inDataVec[2]) == 0)
			{
				product = tempVec[i];
			}
		}

		shelf = dataController.FindShelf(product->getLoc());

		string product_weight = to_string(product->getWeight()); //�ش� ��ǰ�� ���� ������ ������

		cout << "�ش���� �̵��� ��ġ�� �Է��ϼ���." << endl;
		getline(cin, locationData);
		cin.clear();
		if (!CheckLocationForm(locationData)) continue; //�̵��� ��ġ ������ ���� ���� ���

		if (!CheckSameLocation(inDataVec[2], locationData)) continue; //�̵��� ��ġ�� ���� ��ġ�� ���� ���
		if (!CheckModLocation(locationData, dataController)) continue; //�̵��� ��ġ�� �������� ���� ���
		if (!CheckWeightRule(product_weight, inDataVec[1], locationData, dataController)) continue; //���� ���Ը� �ʰ��ϴ� ���

		//product = dataController.FindProduct(inDataVec[2], inDataVec[0], 0);

		temp_product = Product::Product(*product);

		shelf->relPro(*product, stoi(inDataVec[1])); //�ش� ��ǰ�� ���ݿ��� ����

		shelf = dataController.FindShelf(locationData);
		temp_product.setNum(stoi(inDataVec[1]));
		temp_product.setLocation(locationData);
		shelf->addPro(temp_product); //��ǰ�� �̵��ϰ��� �ϴ� ��ġ�� �԰�


		//================��� ����==================
		Record_data record_out(inDataVec[3], "���", temp_product.getLoc(), temp_product.getID(), temp_product.getName(), stoi(inDataVec[1])); //��� ���
		Record_data record_in(inDataVec[3], "�԰�", locationData, temp_product.getID(), temp_product.getName(), stoi(inDataVec[1])); //�԰� ���
		dataController.addRecord(record_out);
		dataController.addRecord(record_in);
		dataController.SaveData();
		//===========================================

		break;
	}
	cout << "�̵� ����" << endl;
	system("PAUSE");
	return;
}



//========���� Ȯ�� �Լ�==========

bool CheckLocationForm(string& location)
{
	//��ġ ������ ���� üũ 1,2,3,4 �Ǵ� 1234
	//,���� ���� �� 4�ڸ� ���� Ȯ��
	string temp = location;
	int count = 0; //,�� ������ ���� ����
	int k;
	size_t errorIndex = NULL;

	string temp_digit = temp;

	temp_digit.erase(remove(temp_digit.begin(), temp_digit.end(), ','), temp_digit.end());
	for (int i = 0; i < temp_digit.size(); i++)
	{
		if (isdigit(temp_digit[i]) == 0) //������ �ƴ� ���ڰ� ���� ���
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
	}

	if (temp.size() == 4)
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if (isdigit(temp[i]) == 0 || temp[i] == '0') //������ �ƴ� ���ڰ� ���� ���
			{
				cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
				return false;
			}
		}
	}
	else if (temp.size() == 7)
	{
		for (int i = 0; 2 * i + 1 < temp.size(); i++)
		{
			if (temp[2 * i + 1] == ',') count++;
		}
		if (count != 3) //�Էµ� ,�� ���� 3������ Ȯ��
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}

		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
	}
	else
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	try
	{
		k = stoi(temp);
	}
	catch (const std::exception& expn)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}

	if (k < 1111 || k>9999)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}

	location = temp; //�ش� ��ġ�� 1234�������� ����

	return true;
}

bool CheckNameForm(string& name)
{
	//Ư������ �Ұ�(����X), ��ҹ��� �������� ����, 1~16�� �̳�, ���� ����
	string temp = name;
	int k = 0;
	bool k_check = true;
	temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end()); //���� ����
	temp.erase(remove(temp.begin(), temp.end(), '\t'), temp.end()); //�� ����
	if (temp.size() == 0)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	for (int i = 0; i < temp.size(); i++) //�ҹ��� ��ȯ
	{
		temp[i] = tolower(temp[i]);
		if (temp.at(i) & 0x80) //�Է��� ���ڰ� �ѱ�
		{
			k++;
		}

	}
	k = k / 2;
	if ((temp.size() > 16 + k) || (temp.size() > 32))
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}

	name = temp; //�̸��� ���� ���� �� �ҹ���ȭ

	return true;
}

bool CheckCountForm(string count)
{
	//�������� Ȯ�� �� ���� Ȯ��
	bool isNotZero = false;
	int temp;

	if (count.size() == 0)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	for (int i = 0; i < count.size(); i++)
	{
		if (isdigit(count[i]) == 0) //������ �ƴ� ���ڰ� ���� ���
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
		if (count[i] == '0' && !isNotZero) //���� ó�� �ڸ��� 0�� �� ���
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
		else
		{
			isNotZero = true;
		}
	}
	try
	{
		temp = stoi(count);
	}
	catch (const std::exception& expn)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	if (temp < 1 || temp > 10000) //���� 1���� �۰ų� 10000���� Ŭ ���
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}

	return true;
}

bool CheckWeightForm(string weight)
{
	//0.00�������� Ȯ��
	//15.00 1.15 3.40 ���� / .52 324 3.512 �Ұ���
	//.�� �������� ������ ���ڸ��� 
	vector<string> temp;
	temp = split(weight, '.');
	bool isNotZero = false;
	double d;

	if (weight.size() == 0)
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
		d = stod(weight);
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

bool CheckDateForm(string& date)
{
	//2021/02/10 �Ǵ� 20210210���� Ȯ�� �� 2000��� ���� Ȯ��
	string temp = date;
	int year, month, day;

	if (temp.size() == 8)
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if (isdigit(temp[i]) == 0) //������ �ƴ� ���ڰ� ���� ���
			{
				cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
				return false;
			}
		}
	}
	else if (temp.size() == 10)
	{
		if (temp.at(4) != '/' || temp.at(7) != '/')
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
		temp.erase(remove(temp.begin(), temp.end(), '/'), temp.end());
	}
	else
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	try
	{
		year = stoi(temp.substr(0, 4));
		month = stoi(temp.substr(4, 2));
		day = stoi(temp.substr(6, 2));
	}
	catch (const std::exception& expn)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	if (year < 1 || year > 9999)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}
	if (month < 1 || month > 12)
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}

	//���� ���
	if (year % 4 == 0)
	{
		if (year % 100 != 0)
		{
			if (month == 2)
			{
				if (day < 1 || day > 29)
				{
					cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
					return false;
				}
			}
		}
		else
		{
			if (year % 400 == 0)
			{
				if (month == 2)
				{
					if (day < 1 || day > 29)
					{
						cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
						return false;
					}
				}
			}
		}
	}

	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day < 1 || day > 31)
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
	}
	else if (month == 2)
	{
		if (day < 1 || day > 28)
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
	}
	else
	{
		if (day < 1 || day > 30)
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
	}

	temp.insert(4, "/");
	temp.insert(7, "/");

	date = temp; //��¥�� 2021/10/22 �������� ����

	return true;
}

//===============================

//========��Ģ Ȯ�� �Լ�==========

bool CheckRealLocation(string location, DataController& dataController)
{
	//��ġ�� ������ �����ϴ� �� Ȯ��
	string in_location = location;
	vector<int> locationVec;
	bool isReal = false;
	in_location.erase(remove(in_location.begin(), in_location.end(), ','), in_location.end());

	for (int i = 0; i < in_location.size(); i++)
	{
		int temp = in_location.at(i) - '0';
		locationVec.push_back(temp);
	}

	if (MAX_WAHEHOUSE_NUM >= locationVec[0])
	{
		if (dataController.getWarehouses()[locationVec[0] - 1].getX1() >= locationVec[1])
		{
			if (dataController.getWarehouses()[locationVec[0] - 1].getX2() >= locationVec[2])
			{
				if (dataController.getWarehouses()[locationVec[0] - 1].getX3() >= locationVec[3])
				{
					isReal = true;
				}
			}
		}
	}

	if (!isReal) //�ش���ġ�� ���� ���� �ʴ� �ٸ�
	{
		cout << "�� ����! ���� ��ġ�� ���� ��ġ �����Դϴ�.\n" << endl;
		return false;
	}

	return true;
}

bool CheckRealName(string name, string location, DataController& dataController)
{
	//�ش� ��ġ�� ��ǰ�� �����ϴ��� Ȯ��
	string in_name = name;
	string in_location = location;

	Product* temp = dataController.FindProduct(in_location, in_name, 0);

	if (temp == NULL) //��ǰ�� �������� ���� ���
	{
		return false;
	}

	return true;
}

bool CheckNameCountLocation(string name, string count, string location, DataController& dataController)
{
	//�ش� ��ġ�� ��ǰ�� ������ ������� Ȯ��
	string in_name = name;
	string in_location = location;
	int in_count = stoi(count);
	Product* temp = NULL;

	//in_location.erase(remove(in_location.begin(), in_location.end(), ','), in_location.end());

	// = dataController.FindProduct(in_location, in_name, 0);

	vector<Product*> tempVec = dataController.FindProduct(in_name, 0);

	for (int i = 0; i < tempVec.size(); i++)
	{
		if (tempVec[i]->getLoc().compare(in_location) == 0)
		{
			temp = tempVec[i];
		}
	}

	if (temp == NULL)
	{
		cout << "�� ����! �ش� ��ġ�� ��ǰ�� �������� �ʽ��ϴ�.\n" << endl;
		return false;
	}

	if (in_count > temp->getNum()) //�������� ������ �԰�� �������� Ŭ ���
	{
		cout << "�� ����! ���� ����� ����� ������ �Ѱ���ϴ�." << endl;
		cout << "[" << in_name << "]����� ���� ���� ���� : [" << temp->getNum() << "] ��\n" << endl;
		return false;
	}

	return true;
}

bool CheckWeightRule(string weight, string count, string location, DataController& dataController)
{
	//���԰� ���� ������ �ִ�ġ�� �Ѵ��� Ȯ���ϴ� �Լ�
	string in_location = location;
	vector<int> locationVec;


	in_location.erase(remove(in_location.begin(), in_location.end(), ','), in_location.end());
	for (int i = 0; i < in_location.size(); i++)
	{
		int temp = in_location.at(i) - '0';
		locationVec.push_back(temp);
	}

	Shelf* shelf = dataController.FindShelf(location);

	double cur_weight = dataController.FindShelf(location)->getCurWeight(); //��ġ�� �������� ���� ���� ���Ը� ������
	double max_weight = dataController.FindShelf(location)->getMaxWeight(); //â�� ������ ���� �ִ� ���Ը� ������
	double sum = cur_weight + stod(weight) * stoi(count);

	if (sum > max_weight)
	{
		cout << "�� ����! �ش� ��ġ�� ���԰� �ʰ��Ͽ� �԰��� �� �����ϴ�.\n" << endl;
		return false;
	}

	return true;
}

bool CheckDateRule(string rel_date, string str_date)
{
	//�Էµ� ��¥�� �� ��¥ ���� ��¥���� Ȯ���ϴ� �Լ�
	bool isOkay = false;
	int rel_year, rel_month, rel_day;
	int str_year, str_month, str_day;

	string rel_temp, str_temp;
	rel_temp = rel_date;
	str_temp = str_date;
	rel_temp.erase(remove(rel_temp.begin(), rel_temp.end(), '/'), rel_temp.end());
	str_temp.erase(remove(str_temp.begin(), str_temp.end(), '/'), str_temp.end());

	rel_year = stoi(rel_temp.substr(0, 4));
	rel_month = stoi(rel_temp.substr(4, 2));
	rel_day = stoi(rel_temp.substr(6, 2));
	str_year = stoi(str_temp.substr(0, 4));
	str_month = stoi(str_temp.substr(4, 2));
	str_day = stoi(str_temp.substr(6, 2));

	//��� ��¥�� �԰� ��¥���� �����̸� false��ȯ

	if (rel_year > str_year) isOkay = true;
	else if (rel_year == str_year)
	{
		if (rel_month > str_month) isOkay = true;
		else if (rel_month == str_month)
		{
			if (rel_day >= str_day) isOkay = true;
		}
	}

	return isOkay;
}

bool CheckNameWeight(string name, string weight, DataController& dataController)
{
	//product.txt�� �����Ͽ� name�� ������ ��� �� ��ǰ�� �̸��� ���Ը� �Է°��� ���Ͽ� ���� ���� ��ȯ

	//		product.txt�� �ش� ��ǰ�� �̸��� �ִ� �� Ȯ��
	//		������ ���Ը� ��
	//		���԰� �ٸ��� ��� �޽����� false��ȯ
	//		������ true ��ȯ
	string in_name = name;
	double in_weight = stod(weight);
	in_name.erase(remove(in_name.begin(), in_name.end(), ' '), in_name.end()); //���� ����

	vector<Product*> data = dataController.FindProduct(in_name, 0);
	if (&data == NULL)
	{
		return false;
	}
	else
	{
		if (data[0]->getWeight() != in_weight)
		{
			cout << "�� ����! ��ϵ� ���Կ� �Է��� ���԰� ���� �ٸ��ϴ�." << endl;
			cout << "�� ��ϵ� ����:" << data[0]->getWeight() << "\n" << endl;
			return false;
		}
	}

	return true;
}

bool CheckSameLocation(string rel_location, string str_location)
{
	//���� ��ġ�� �̵��� ��ġ�� ������ ��
	string rel_temp = rel_location;
	string str_temp = str_location;

	//rel_temp.erase(remove(rel_temp.begin(), rel_temp.end(), ','), rel_temp.end());
	//str_temp.erase(remove(str_temp.begin(), str_temp.end(), ','), str_temp.end());

	if (rel_temp.compare(str_temp) == 0)
	{
		cout << "�� ����! �̵��� ��ġ�� ���� ��ġ�Դϴ�.\n" << endl;
		return false;
	}

	return true;
}

bool CheckSameLocationForRecord(string rel_location, string str_location)
{
	//���� ��ġ�� �̵��� ��ġ�� ������ ��, ��� Ž����
	if (rel_location.compare(str_location) == 0)
	{
		return true;
	}
	return false;
}

bool CheckDateCountRule(string name, string count, string location, string date, DataController& dataController)
{
	//�ش� ��ġ�� ��ǰ�� ��� ��¥ ������ ��� ��ǰ�� �����ϴ��� Ȯ���ϴ� �Լ�
	vector<Record_data*> temp = dataController.FindRecord(name, 0);

	int in_num = stoi(count);
	string date_temp = "";
	int cur_num = 0;
	int isSame = 0;
	int isRecord = 0;
	for (int i = 0; i < temp.size(); i++)
	{
		//�� ����� Ȯ���Ͽ� ����ϰ��� �ϴ� �� ���� �� ��� ����� ������ �����Ѵ�.
		if (location.compare(temp[i]->getLoc()) == 0)
		{
			if (CheckDateRule(date, temp[i]->getTime()))
			{
				if (temp[i]->getKind().compare("�԰�") == 0)
				{
					cur_num += temp[i]->getNum();
					date_temp = temp[i]->getTime();
					isRecord++;
				}
				else cur_num -= temp[i]->getNum();
				isSame++;
			}
		}
	}
	if (isRecord == 0)
	{
		cout << "�� ����! �Է� ��¥�� ��� ��¥�� ������ �� �����ϴ�." << endl;
		cout << "�� �ش� ��¥ ������ �԰�� ����� �����ϴ�.\n" << endl;
		return false;
	}
	if (isSame == 0) return true;
	if (in_num > cur_num)
	{
		cout << "�� ����! �Է� ��¥�� ��� ��¥�� ������ �� �����ϴ�." << endl;
		cout << "[" << count << "]���� ��� ������ ���ؼ�, [" << date_temp << "] ���Ŀ��� �մϴ�.\n" << endl;
		return false;
	}

	return true;
}

void ModWare(DataController& dataController)
{
	//atexit(printmenu);
	string inData;
	vector<string> inDataVec;	// 0 : ������ â�� ��ġ, 1 : ������ �ִ� ����

	while (true)
	{
		cout << "������ â���� ��ġ�� ���� �ִ� ���Ը� �Է��ϼ���." << endl;
		cout << "(�޴��� ���ư����� 'q'�� �Է��ϼ���)" << endl;
		getline(cin, inData);
		cin.clear();
		if (!CheckHyphenNum(inData, 1))
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			continue;
		}
		inDataVec = split(inData, '-');
		if (inDataVec.size() == 1)
		{
			if (inDataVec[0].compare("q") == 0) //'q' �Է��ϸ� ����
			{
				return;
			}
		}
		if (inDataVec.size() != 2)
		{
			cout << "�Էµ� �������� ������ Ʋ���ϴ�." << endl;
			continue;
		}

		if (!CheckLocationForm(inDataVec[0])) continue; //��ġ ������ ���� ���� ���
		if (!CheckMaxWeightForm(inDataVec[1])) continue; //�� �ִ� ���� ������ ���� ���� ���
		//if (!CheckRealLocation(inDataVec[0], dataController)) continue; //�Է��� ��ġ�� �������� ���� ���
		if (!CheckModLocation(inDataVec[0], dataController)) continue; //�Է��� ��ġ�� �������� ���� ��� 2

		if (!CheckModWeight(inDataVec[0], inDataVec[1], dataController)) continue; //������ ���԰� ��Ģ ���Ŀ� ���� ���� ���

		dataController.FindShelf(inDataVec[0])->modMaxWeight(stoi(inDataVec[1]));

		dataController.SaveData();

		break;
	}
	cout << "���� ����" << endl;
	system("PAUSE");
	return;
}

bool CheckMaxWeightForm(string maxWeight)
{
	//�� �ִ� ���Դ� 1 ~ 3�ڸ� ����
	//����, ���� 0�� ������� �ʴ´�.

	if (maxWeight.size() < 1 || maxWeight.size() > 3) //1 ~ 3�ڸ��� �ƴ� ���
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}

	for (int i = 0; i < maxWeight.size(); i++)
	{
		if (isdigit(maxWeight[i]) == 0) //������ �ƴ� ���ڰ� ���� ���
		{
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			return false;
		}
	}

	if (maxWeight[0] == '0') //���� 0�� ���
	{
		cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
		return false;
	}

	return true;
}

bool CheckModLocation(string location, DataController& dataController)
{
	//��ġ�� ���� ������ ������ Ȯ��
	string in_location = location;
	vector<int> locationVec;

	for (int i = 0; i < in_location.size(); i++)
	{
		int temp = in_location.at(i) - '0';
		locationVec.push_back(temp);
	}

	//�Է��� ��ġ�� �������� ������(���� �������� ������)
	if (!dataController.getWarehouses()[locationVec[0] - 1].getIsUse())
	{
		cout << "�� ����! ���� ��ġ�� ���� ��ġ �����Դϴ�.\n" << endl;
		return false;
	}

	if (!dataController.getWarehouses()[locationVec[0] - 1].getShelfs()[locationVec[1] - 1][locationVec[2] - 1][locationVec[3] - 1].getIsUse())
	{
		cout << "�� ����! ���� ��ġ�� ���� ��ġ �����Դϴ�.\n" << endl;
		return false;
	}

	return true;
}

bool CheckModWeight(string location, string weight, DataController& dataController)
{
	//�����Ϸ��� ���԰� ���� �����ϴ� ��ǰ���� �պ��� ���� ���
	string in_location = location;
	vector<int> locationVec;
	int int_weight = stoi(weight);

	for (int i = 0; i < in_location.size(); i++)
	{
		int temp = in_location.at(i) - '0';
		locationVec.push_back(temp);
	}

	if (dataController.getWarehouses()[locationVec[0] - 1].getShelfs()[locationVec[1] - 1][locationVec[2] - 1][locationVec[3] - 1].getMaxWeight()
		== int_weight)
	{
		cout << "�� ����! �ش� ��ġ�� �ִ� ���Կ� �����մϴ�.\n" << endl;
		return false;
	}

	if (dataController.getWarehouses()[locationVec[0] - 1].getShelfs()[locationVec[1] - 1][locationVec[2] - 1][locationVec[3] - 1].getCurWeight()
	> (double)int_weight)
	{
		cout << "�� ����! ������ �ִ� ���԰� �ش� ��ġ�� ����� ��ǰ�� ���Ժ��� �۽��ϴ�.\n" << endl;
		return false;
	}

	return true;
}

int menu6(DataController& dataController) {

	int num;
	string input = "";

	atexit(printmenu);

	cout << "[Inventory Management Program]\n";
	cout << "� ������ ������ ������ �����ϼ���.\n";
	cout << "(1) �߰�   (2) ����  (3) ����\n";
	cout << "(�޴��� ���ư����� \'q\'�� �Է��ϼ���)\n";

	while (true) {
		//system("cls");
		getline(cin, input);

		if (input == "") getline(cin, input);

		if (input == "1" || input == "�߰�")
		{
			num = 1;
			break;
		}
		else if (input == "2" || input == "����")
		{
			num = 2;
			break;
		}
		else if (input == "3" || input == "����")
		{
			num = 3;
			break;
		}
		else if (input == "q") {
			num = 4;
			break;
		}
		else
		{
			cin.clear();
			system("cls");
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n";
			cout << "[Inventory Management Program]\n";
			cout << "� ������ ������ ������ �����ϼ���.\n";
			cout << "(1) �߰�   (2) ����  (3) ����\n";
			cout << "(�޴��� ���ư����� \'q\'�� �Է��ϼ���)\n";
		}
	}

	switch (num)
	{
	case 1:
		//cout << "1" << endl;
		add_Warehouses();
		break;
	case 2:
		//cout << "2" << endl;
		removeWarehouse(dataController);
		break;
	case 3:
		//cout << "3" << endl;
		ModWare(dataController);
		break;
	case 4:
		return 0;
		break;
	}

	cin.clear();
	return 0;
}

void changeFile()
{
	FILE* file;
	if ((file = fopen("./Inventory_Files/temp.txt", "r")))
	{
		fclose(file);
		remove("./Inventory_Files/SettingWarehouses.txt");
		rename("./Inventory_Files/temp.txt", "./Inventory_Files/SettingWarehouses.txt");
	}

}

void removeWarehouse(DataController& dataController) {
	//atexit(printmenu);

	string locaToRemove = "";
	while (true) {
		cout << "[Inventory Management Program]\n";
		cout << "������ â���� ��ġ�� �Է��ϼ���\n";
		cout << "(�޴��� ���ư���� \'q\'�� �Է��ϼ���)\n";
		getline(cin, locaToRemove);
		cin.clear();
		if (locaToRemove == "q") {
			return;
		}
		if (locaToRemove.length() > 4) {
			cout << "�ٽ� �Է����ּ���\n";
		}
		else {
			int flag = 1;
			for (int i6 = 0; i6 < locaToRemove.length(); i6++) {
				if (isdigit(locaToRemove[i6]) == 0 || locaToRemove[i6] == '0') {
					flag = 0;
					cout << "�ٽ� �Է����ּ���\n";
					break;
				}
			}
			if (flag == 1) {
				break;
			}
		}
	}

	//Warehouse* wh6 = dataController.getWarehouses();
	vector<int> input6(locaToRemove.length(), 0);
	for (int i6 = 0; i6 < input6.size(); i6++) {
		input6[i6] = (int)locaToRemove[i6] - 48;
	}

	if (input6.size() == 1) {
		ifstream read;
		int flag6 = 1;
		read.open("./Inventory_Files/SettingWarehouses.txt", ios_base::in);
		if (read.is_open()) {
			while (!read.eof()) {
				if (read.peek() == std::ifstream::traits_type::eof()) break;
				char arr[256];
				read.getline(arr, 1024);

				if (arr[0] == locaToRemove[0]) {
					flag6 = 0;
				}
			}
		}
		read.close();

		//ifstream read;
		int flag6_2 = 1;
		read.open("./Inventory_Files/Product.txt", ios_base::in);
		if (read.is_open()) {
			while (!read.eof()) {
				if (read.peek() == std::ifstream::traits_type::eof()) break;
				char arr[256];
				read.getline(arr, 1024);

				int count6 = 0;
				int i6 = 0;
				for (i6 = 0; i6 < 256; i6++) {
					if (arr[i6] == '-') count6++;
					if (count6 == 3) break;
				}

				if (arr[i6 + 1] == locaToRemove[0]) {
					flag6_2 = 0;
				}
			}
		}
		read.close();

		if (flag6 == 1) {
			cout << "[Inventory Management Program]\n";
			cout << "�� ����! �ش� ��ġ�� â�� �������� �ʽ��ϴ�.\n";
			removeWarehouse(dataController);
		}
		else if (flag6_2 == 0) {
			cout << "[Inventory Management Program]\n";
			cout << "�� ����! �ش� ��ġ�� ��ǰ�� ���� �� ������ �� �����ϴ�.\n";
			removeWarehouse(dataController);
		}
		else {
			string p6 = locaToRemove;
			for (int i6 = 1; i6 <= 9; i6++) {
				for (int i61 = 1; i61 <= 9; i61++) {
					for (int i62 = 1; i62 <= 9; i62++) {
						string p6 = locaToRemove + to_string(i6) + to_string(i61) + to_string(i62);
						dataController.FindShelf(p6)->setIsUse(false);
					}
				}
			}
			dataController.SaveData();


			cout << "���� ����\n";
			read.open("./Inventory_Files/SettingWarehouses.txt");
			if (read.peek() == ifstream::traits_type::eof())
			{
				setwarehouse();
			}
			read.close();
		}
	}
	else if (input6.size() == 2) {
		ifstream read;
		int flag6 = 1;
		read.open("./Inventory_Files/SettingWarehouses.txt", ios_base::in);
		if (read.is_open()) {
			while (!read.eof()) {
				if (read.peek() == std::ifstream::traits_type::eof()) break;
				char arr[256];
				read.getline(arr, 1024);

				if (arr[0] == locaToRemove[0] && arr[1] == locaToRemove[1]) {
					flag6 = 0;
				}
			}
		}
		read.close();

		//ifstream read;
		int flag6_2 = 1;
		read.open("./Inventory_Files/Product.txt", ios_base::in);
		if (read.is_open()) {
			while (!read.eof()) {
				if (read.peek() == std::ifstream::traits_type::eof()) break;
				char arr[256];
				read.getline(arr, 1024);

				int count6 = 0;
				int i6 = 0;
				for (i6 = 0; i6 < 256; i6++) {
					if (arr[i6] == '-') count6++;
					if (count6 == 3) break;
				}

				if (arr[i6 + 1] == locaToRemove[0] && arr[i6 + 2] == locaToRemove[1]) {
					flag6_2 = 0;
				}
			}
		}
		read.close();

		if (flag6 == 1) {
			cout << "[Inventory Management Program]\n";
			cout << "�� ����! �ش� ��ġ�� â�� �������� �ʽ��ϴ�.\n";
			removeWarehouse(dataController);
		}
		else if (flag6_2 == 0) {
			cout << "[Inventory Management Program]\n";
			cout << "�� ����! �ش� ��ġ�� ��ǰ�� ���� �� ������ �� �����ϴ�.\n";
			removeWarehouse(dataController);
		}
		else {
			string p6 = locaToRemove;

			for (int i61 = 1; i61 <= 9; i61++) {
				for (int i62 = 1; i62 <= 9; i62++) {
					string p6 = locaToRemove + to_string(i61) + to_string(i62);
					dataController.FindShelf(p6)->setIsUse(false);
				}
			}

			dataController.SaveData();


			cout << "���� ����\n";
			read.open("./Inventory_Files/SettingWarehouses.txt");
			if (read.peek() == ifstream::traits_type::eof())
			{
				setwarehouse();
			}
			read.close();
		}
	}
	else if (input6.size() == 3) {
		ifstream read;
		int flag6 = 1;
		read.open("./Inventory_Files/SettingWarehouses.txt", ios_base::in);
		if (read.is_open()) {
			while (!read.eof()) {
				if (read.peek() == std::ifstream::traits_type::eof()) break;
				char arr[256];
				read.getline(arr, 1024);

				if (arr[0] == locaToRemove[0] && arr[1] == locaToRemove[1] && arr[2] == locaToRemove[2]) {
					flag6 = 0;
				}
			}
		}
		read.close();

		//ifstream read;
		int flag6_2 = 1;
		read.open("./Inventory_Files/Product.txt", ios_base::in);
		if (read.is_open()) {
			while (!read.eof()) {
				if (read.peek() == std::ifstream::traits_type::eof()) break;
				char arr[256];
				read.getline(arr, 1024);

				int count6 = 0;
				int i6 = 0;
				for (i6 = 0; i6 < 256; i6++) {
					if (arr[i6] == '-') count6++;
					if (count6 == 3) break;
				}

				if (arr[i6 + 1] == locaToRemove[0] && arr[i6 + 2] == locaToRemove[1] && arr[i6 + 3] == locaToRemove[2]) {
					flag6_2 = 0;
				}
			}
		}
		read.close();

		if (flag6 == 1) {
			cout << "[Inventory Management Program]\n";
			cout << "�� ����! �ش� ��ġ�� â�� �������� �ʽ��ϴ�.\n";
			removeWarehouse(dataController);
		}
		else if (flag6_2 == 0) {
			cout << "[Inventory Management Program]\n";
			cout << "�� ����! �ش� ��ġ�� ��ǰ�� ���� �� ������ �� �����ϴ�.\n";
			removeWarehouse(dataController);
		}
		else {
			string p6 = locaToRemove;

			for (int i62 = 1; i62 <= 9; i62++) {
				string p6 = locaToRemove + to_string(i62);
				dataController.FindShelf(p6)->setIsUse(false);
			}

			dataController.SaveData();
			cout << "���� ����\n";
			read.open("./Inventory_Files/SettingWarehouses.txt");
			if (read.peek() == ifstream::traits_type::eof())
			{
				setwarehouse();
			}
			read.close();
		}
	}
	else if (input6.size() == 4) {
		ifstream read;
		int flag6 = 1;
		read.open("./Inventory_Files/SettingWarehouses.txt", ios_base::in);
		if (read.is_open()) {
			while (!read.eof()) {
				if (read.peek() == std::ifstream::traits_type::eof()) break;
				char arr[256];
				read.getline(arr, 1024);

				if (arr[0] == locaToRemove[0] && arr[1] == locaToRemove[1] && arr[2] == locaToRemove[2] && arr[3] == locaToRemove[3]) {
					flag6 = 0;
				}
			}
		}
		read.close();

		//ifstream read;
		int flag6_2 = 1;
		read.open("./Inventory_Files/Product.txt", ios_base::in);
		if (read.is_open()) {
			while (!read.eof()) {
				if (read.peek() == std::ifstream::traits_type::eof()) break;
				char arr[256];
				read.getline(arr, 1024);

				int count6 = 0;
				int i6 = 0;
				for (i6 = 0; i6 < 256; i6++) {
					if (arr[i6] == '-') count6++;
					if (count6 == 3) break;
				}

				if (arr[i6 + 1] == locaToRemove[0] && arr[i6 + 2] == locaToRemove[1] && arr[i6 + 3] == locaToRemove[2] && arr[i6 + 4] == locaToRemove[3]) {
					flag6_2 = 0;
				}
			}
		}
		read.close();

		if (flag6 == 1) {
			cout << "[Inventory Management Program]\n";
			cout << "�� ����! �ش� ��ġ�� â�� �������� �ʽ��ϴ�.\n";
			removeWarehouse(dataController);
		}
		else if (flag6_2 == 0) {
			cout << "[Inventory Management Program]\n";
			cout << "�� ����! �ش� ��ġ�� ��ǰ�� ���� �� ������ �� �����ϴ�.\n";
			removeWarehouse(dataController);
		}
		else {

			string p6 = locaToRemove;
			dataController.FindShelf(p6)->setIsUse(false);


			dataController.SaveData();
			cout << "���� ����\n";
			read.open("./Inventory_Files/SettingWarehouses.txt");
			if (read.peek() == ifstream::traits_type::eof())
			{
				setwarehouse();
			}
			read.close();
		}
	}
}

//����
bool CheckMaxWeightForm_add(string maxWeight)
{
	//�� �ִ� ���Դ� 1 ~ 3�ڸ� ����
	//����, ���� 0�� ������� �ʴ´�.

	if (maxWeight.size() < 1 || maxWeight.size() > 3) //1 ~ 3�ڸ��� �ƴ� ���
	{
		return false;
	}

	for (int i = 0; i < maxWeight.size(); i++)
	{
		if (isdigit(maxWeight[i]) == 0) //������ �ƴ� ���ڰ� ���� ���
		{
			return false;
		}
	}

	if (maxWeight[0] == '0') //���� 0�� ���
	{
		return false;
	}

	return true;
}

// â�� �߰�, ����
int add_Warehouses()
{
	//atexit(printmenu);
	bool flag = true;

	string input;								// 'â��-�ִ� ����'�� �� ���ڿ� ����
	while (1)
	{
		try
		{
			// �Է� �ޱ�
			cout << "[Inventory Management Program]" << endl;
			cout << "�߰��� â���� ��ġ�� ���� �ִ� ���Ը� �Է��ϼ���.(��ġ-�ִ� ����)" << endl;
			cout << "(�޴��� ���ư����� 'q'�� �Է��ϼ���)" << endl;
			cout << ">>";
			getline(cin, input);

			if (input == "q")
			{
				cin.clear();
				return 0;
			}

			if (!(5 < input.length() && input.length() < 9))
			{
				cout << "\n[Inventory Management Program]" << endl;
				cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
				continue;
			}

			// â�� - �ִ� ���� ���� �˻�
			if (input[4] != '-')
			{
				cout << "\n[Inventory Management Program]" << endl;
				cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
				continue;
			}

			vector<string> output = split(input, '-'); // output = [location, weight] ��
			string location = output.at(0);
			string weight = output.at(1);

			// location, weight �Է� ��Ģ Ȯ��(weight ��Ģ �߰� �ʿ�)
			if ((flag = CheckLocationForm(location)) && (CheckMaxWeightForm_add(weight)))
			{

				int n = static_cast<int>(location.at(0)) - 48;					// â�� ��ȣ(n)
				int i = static_cast<int>(location.at(1)) - 48;					// ���� ��ȣ(i)
				int j = static_cast<int>(location.at(2)) - 48;					// ���� ��ȣ(j)
				int k = static_cast<int>(location.at(3)) - 48;					// �� ��ȣ(k)


				// �̹� â�� �����ϴ��� �ľ��ؾ���
				//if (!dataController.getWarehouses()[n - 1].getIsUse() && !(dataController.getWarehouses()[n - 1].getShelfs()[i - 1][j - 1][k - 1].getIsUse()))
				if (!(dataController.getWarehouses()[n - 1].getShelfs()[i - 1][j - 1][k - 1].getIsUse()))
				{
					ofstream ofs("Inventory_Files/SettingWarehouses.txt", ios::app);
					// SettingWarehouses ���� ����
					if (!ofs)
					{
						cerr << "SettingWarehouses open fail" << endl;
						exit(1);
					}


					dataController.getWarehouses()[n - 1].setIsUse(true);		// n�� â�� ��������� true�� ��ȯ
					dataController.getWarehouses()[n - 1].getShelfs()[i - 1][j - 1][k - 1].setIsUse(true);		// n�� â���� i���� j�� ���� k�� true�� ��ȯ
					dataController.getWarehouses()[n - 1].getShelfs()[i - 1][j - 1][k - 1].modMaxWeight(stoi(weight));
					ofs << '\n' + location + '-' + weight;
					cout << "â�� �߰� �Ϸ�\n" << endl;
					continue;
				}

				// â�� �̹� ������
				else
				{
					cout << "\n[Inventory Management Program]" << endl;
					cout << "�� ����! �ش� ��ġ�� �̹� â�� �����մϴ�.\n" << endl;
					continue;
				}
			}

			// location, weight �Է� ��Ģ ���
			else
			{
				if (flag) {
					cout << "\n[Inventory Management Program]" << endl;
					cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
				}
				continue;
			}
		}
		catch (const std::exception& expn)
		{
			cout << "\n[Inventory Management Program]" << endl;
			cout << "�� ����! ���� �� �Է� ��Ģ�� ��� �Է��Դϴ�.\n" << endl;
			continue;
		}
	}
}

bool CheckHyphenNum(string str, int num)
{
	int len = str.length();
	int cnt = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '-') cnt++;
	}
	if (cnt == 0 || cnt == num) return true;
	return false;
}