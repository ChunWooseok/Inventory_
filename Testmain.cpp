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

//======입출고 기능 함수====
void Store(DataController& dataController);
void Release(DataController& dataController);
void MoveProduct(DataController& dataController);

//======형식 확인 함수======
bool CheckLocationForm(string& location);
bool CheckNameForm(string& name);
bool CheckCountForm(string count);
bool CheckWeightForm(string weight);
bool CheckDateForm(string& date);
bool CheckHyphenNum(string str, int num);

//=======규칙 확인 함수=======
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

	bool flag = false; //파일이 하나라도 없으면 true 

	ifstream read;
	ofstream write;

	read.open("./Inventory_Files/SettingWarehouses.txt");
	if (!read.good())
	{
		_rmdir("./Inventory_Files");
		_mkdir("./Inventory_Files");
		setwarehouse();
		cout << "SettingWarehouse.txt 읽기실패!" << endl;
		flag = true;
	}
	read.close();

	read.open("./Inventory_Files/Record.txt");
	if (!read.good())
	{
		cout << "Record.txt 읽기실패!" << endl;
		_rmdir("./Inventory_Files");
		_mkdir("./Inventory_Files");
		setwarehouse();
		flag = true;
	}
	read.close();

	read.open("./Inventory_Files/Product.txt");
	if (!read.good())
	{
		cout << "Product.txt 읽기실패!" << endl;
		_rmdir("./Inventory_Files");
		_mkdir("./Inventory_Files");
		setwarehouse();
		flag = true;
	}
	read.close();

	read.open("./Inventory_Files/SettingWarehouses.txt");
	if (read.peek() == ifstream::traits_type::eof())
	{ //파일은 있는데 비어있을경우
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
	int warehouse_num, block_num, shelf_num, floor_num; //개수
	int warehouse, block, shelf, floor, weight = 0, count = 0; //창고 개수
	ofstream write;
	int warehouses[10][10][10][10] = { 0, };
	vector<string> vec;

	cout << "[Inventory Management Program]" << endl;
	cout << "설정할 창고의 개수를 입력하세요." << endl << ">>";

	while (true)
	{
		getline(cin, input);
		//cout << input;
		if ('0' < input[0] && input[0] <= '9' && input.size() == 1)
		{ //창고는 0과 9사이의 숫자만 가능
			warehouse_num = input[0] - '0';
			break;
		}
		else
		{
			system("cls");
			cout << "[Inventory Management Program]" << endl;
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
			cout << "설정할 창고의 개수를 입력하세요." << endl << ">>";
		}
	}
	system("cls");
	for (int i = 1; i <= warehouse_num; i++)
	{
		cout << i << "번째 창고의 창고번호 및 구역수를 입력하세요" << endl << ">>";
		while (true)
		{
			getline(cin, input);
			//cout << input;
			if ('0' < input[0] && input[0] <= '9' && input.size() == 3 && '0' < input[2] && input[2] <= '9' && input[1] == ',')
			{ //창고는 0과 9사이의 숫자만 가능
				warehouse = input[0] - '0';
				block_num = input[2] - '0';
				if (warehouses[warehouse][0][0][0] == 0)
				{
					warehouses[warehouse][0][0][0] = block_num;
					break;
				}
				else
				{
					cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
					cout << i << "번째 창고의 창고번호 및 구역수를 입력하세요" << endl << ">>";
				}

			}
			else
			{
				//system("cls");
				//cout << "[Inventory Management Program]" << endl;
				cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
				cout << i << "번째 창고의 창고번호 및 구역수를 입력하세요" << endl << ">>";
			}
		}

		for (int j = 1; j <= block_num; j++)
		{
			cout << "  " << j << "번째 구역의 구역번호 및 선반개수를 입력하세요" << endl << "  >>";
			while (true)
			{
				getline(cin, input);
				//cout << input;
				if ('0' < input[0] && input[0] <= '9' && input.size() == 3 && '0' < input[2] && input[2] <= '9' && input[1] == ',')
				{ //창고는 0과 9사이의 숫자만 가능
					block = input[0] - '0';
					shelf_num = input[2] - '0';
					if (warehouses[warehouse][block][0][0] == 0)
					{
						warehouses[warehouse][block][0][0] = shelf_num;
						break;
					}
					else
					{
						cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
						cout << "  " << j << "번째 구역의 구역번호 및 선반개수를 입력하세요" << endl << "  >>";
					}
				}
				else
				{
					//system("cls");
					//cout << "[Inventory Management Program]" << endl;
					cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
					cout << "  " << j << "번째 구역의 구역번호 및 선반개수를 입력하세요" << endl << "  >>";
				}
			}
			for (int k = 1; k <= shelf_num; k++)
			{
				cout << "    " << k << "번째 선반의 선반번호 및 층수를 입력하세요" << endl << "    >>";
				while (true)
				{
					getline(cin, input);
					//cout << input;
					if ('0' < input[0] && input[0] < '9' && input.size() == 3 && '0' < input[2] && input[2] <= '9' && input[1] == ',')
					{ //창고는 0과 9사이의 숫자만 가능
						shelf = input[0] - '0';
						floor_num = input[2] - '0';
						if (warehouses[warehouse][block][shelf][0] == 0)
						{
							warehouses[warehouse][block][shelf][0] = floor_num;
							break;
						}
						else
						{
							cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
							cout << "    " << k << "번째 선반의 선반번호 및 층수를 입력하세요" << endl << "    >>";
						}
					}
					else
					{
						//system("cls");
						//cout << "[Inventory Management Program]" << endl;
						cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
						cout << "    " << k << "번째 선반의 선반번호 및 층수를 입력하세요" << endl << "    >>";
					}
				}
				for (int e = 1; e <= floor_num; e++)
				{
					cout << "      " << e << "번째 층의 층번호 및 무게를 입력하세요" << endl << "      >>";
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
									//cout << "걸림" << endl;
									flag = false;
								}
							}
						}

						if ('0' < input[0] && input[0] <= '9' && input.size() >= 3 && input.size() <= 5 && '0' < input[2] && input[2] <= '9' && flag && input[1] == ',')
						{ //창고는 0과 9사이의 숫자만 가능
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
								cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
								cout << "      " << e << "번째 층의 층번호 및 무게를 입력하세요" << endl << "      >>";
							}
						}
						else
						{
							//system("cls");
							//cout << "[Inventory Management Program]" << endl;
							cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
							cout << "      " << e << "번째 층의 층번호 및 무게를 입력하세요" << endl << "      >>";
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
	cout << "메뉴를 입력하세요." << endl;
	cout << "(1) 입고 (2) 출고 (3) 이동 (4) 재고 현황 (5) 입출고 현황 (6) 창고설정 (7) 종료" << endl << ">>";
	//getline(cin, input);

	while (true)
	{

		getline(cin, input);

		if (input == "") {
			getline(cin, input);
			cout << "aaa";
		}

		if (input == "1" || input == "입고")
		{
			num = 1;
			break;
		}
		else if (input == "2" || input == "출고")
		{
			num = 2;
			break;
		}
		else if (input == "3" || input == "이동")
		{
			num = 3;
			break;
		}
		else if (input == "4" || input == "재고 현황")
		{
			num = 4;
			break;
		}
		else if (input == "5" || input == "입출고 현황")
		{
			num = 5;
			break;
		}
		else if (input == "6" || input == "창고설정")
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
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다." << endl;
			cout << "메뉴를 입력하세요." << endl;
			cout << "(1) 입고 (2) 출고 (3) 이동 (4) 재고 현황 (5) 입출고 현황 (6) 창고설정 (7) 종료" << endl << ">>";
		}
	}


	switch (num)
	{
	case 1:
		//cout << "1" << endl;
		//여깅에 각 기능함수 넣으면 됩니다!
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

// split하는 함수 ==> 사용법 : split(문자열, 쪼갤 단위)
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

	// 파일 열기
	ifstream ifs;
	ifs.open("Inventory_Files/Product.txt");

	// 파일 열기 실패
	if (!ifs)
	{
		cerr << "File Open error" << endl;
		exit(1);
	}

	// 파일 열기 성공
	vector<string> s;														// 파일에서 split한거 담는 vector
	tuple<string, string, string, string, string, int> s_tuple;				// split한거 tuple로 만든 후 담을 tuple
	vector<tuple<string, string, string, string, string, int>> result;		// tuple을 다시 vector로 담음

	vector<string> Id;
	vector<string> Name;
	vector<string> Weight;
	vector<string> Location;
	vector<string> Number;
	int index = 0;															// 나중에 값을 계산하기 위한 index값

	// 파일 읽어서 vector와 tuple에 담음
	while (ifs)
	{
		string str;
		getline(ifs, str);

		// 파일의 끝일 땐 break
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

	// result ID 오름차순 정렬
	sort(result.begin(), result.end(), compare);

	// 중복 품목 삭제 후, 그만큼 개수 추가
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

		// [ID_1] | [이름1] | [a1]개 출력
		for (int i = 0; i < result.size(); i++)
		{
			cout << "(" << i + 1 << ") " << get<0>(result[i]) << " | " << get<1>(result[i]) << " | " << get<4>(result[i]) << "개" << endl;
		}

		cout << "\n================================================================\n" << endl;
		if (Id.size() == 0)
		{
			cout << "※ 오류! 아무런 물품도 등록되어있지 않습니다." << endl;
		}
		else
			cout << "번호에 해당하는 재고의 상세 정보를 보고 싶다면 번호를 입력하세요." << endl;

		cout << "(메뉴로 돌아가려면 'q'를 입력하세요)" << endl;
		cout << ">>";
		getline(cin, choice);

		// q입력 시 menu로 돌아감
		if (choice == "q")
		{
			cin.clear();
			return 0;
		}

		// choice가 양수
		else if (isNumber(choice))
		{
			try
			{
				if ((stoi(choice) > static_cast<int>(result.size())) || (stoi(choice) == 0))
				{
					cout << "※ 오류! 범위에 벗어난 번호입니다." << endl;
				}
				else
				{
					int choice_int = stoi(choice);

					cout << "[Inventory Management Program]" << endl;
					cout << get<0>(result[choice_int - 1]) << " | " << get<1>(result[choice_int - 1]) << " | " << get<4>(result[choice_int - 1]) << "개" << endl;

					// 창고별 물품 출력
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
					cout << "(재고 현황으로 돌아가려면 'q'를 입력하세요.)" << endl;

					while (1)
					{
						cout << ">>";
						getline(cin, choice);
						if (choice == "q")
							break;
						else
							cout << "※ 오류! 올바른 입력을 해주세요." << endl;
					}
				}
			}
			catch (const std::exception& expn)
			{
				cout << "※ 오류! 범위에 벗어난 번호입니다." << endl;
			}
			catch (...)
			{
				cout << "※ 오류! 올바른 입력을 해주세요." << endl;
			}
		}

		// choice가 음수거나 다른 글자
		else
		{
			cout << "※ 오류! 올바른 입력을 해주세요." << endl;
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
	// menu5_2()에서 record 정렬하는 함수
	if (v1[0] > v2[0])
	{
		return true;
	}
	return false;
}

int menu5()
{
	atexit(printmenu);  // q를 입력받으면 메인메뉴로 돌아가게 함

	ifstream ifs;
	ifs.open("Inventory_Files/Record.txt");

	if (!ifs)
	{    // 파일 열기 실패
		cerr << "Record.txt 열기 실패" << endl;
		exit(1);
	}

	vector<vector<string>> data;
	while (ifs)
	{
		string str;
		getline(ifs, str);

		if (str == "")
		{    // 끝까지 불러옴
			break;
		}
		vector<string> temp;
		temp = split(str, '-');
		data.push_back(temp);
	}
	ifs.close();

	cout << "[Inventory Management Program]" << '\n';
	cout << "입출고 현황을 확인할 재고 이름을 입력하세요" << '\n';
	cout << "(메뉴로 돌아가려면 'q'를 입력하세요)" << '\n';

	vector<vector<string>> result;
	string input;
	do
	{
		vector<vector<string>>().swap(result);  // result 초기화

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
		{   // 입력에 대한 물품이 없다면
			cout << "[Inventory Management Program]" << '\n';
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n";
		}

		sort(result.begin(), result.end(), sortRecordByDate);   // 날짜 순으로 정렬
		for (int i = result.size() - 1; i >= 0; i--)
		{
			// 입출력 현황 출력
			cout << "(" << result.size() - i << ") " << result[i][0] << " | " << result[i][1] << " | " << result[i][5] << " | " << result[i][2] << '\n';
		}

	} while (input != "q");   // 입력에 대한 물품이 없을 때 다시 입력을 받도록 반복

	cin.clear();
	return 1;
}

void Store(DataController& dataController)//입고 함수
{
	atexit(printmenu);
	string inData;
	vector<string> inDataVec; // 0:이름, 1:무게, 2:개수, 3:위치, 4:날짜
	Product product;
	Shelf* shelf;

	while (1)
	{
		cout << "입고할 재고의 정보와 개수, 위치, 입고 날짜를 입력하세요." << endl;
		cout << "(이름-무게-개수-위치-입고 날짜)\n(메뉴로 돌아가려면 'q'를 입력하세요)" << endl;
		getline(cin, inData);
		cin.clear();
		if (!CheckHyphenNum(inData, 4))
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			continue;
		}
		inDataVec = split(inData, '-');
		if (inDataVec.size() == 1)
		{
			if (inDataVec[0].compare("q") == 0)//q를 입력하면 종료
			{
				return;
			}
		}
		if (inDataVec.size() != 5)
		{
			cout << "※ 오류! 입력된 데이터의 개수가 틀립니다.\n" << endl;
			continue;
		}
		if (!CheckNameForm(inDataVec[0])) continue; //이름 형식이 맞지 않은 경우
		if (!CheckWeightForm(inDataVec[1])) continue; //무게 형식이 맞지 않은 경우
		if (!CheckCountForm(inDataVec[2])) continue; //개수 형식이 맞지 않은 경우
		if (!CheckLocationForm(inDataVec[3])) continue; //위치 형식이 맞지 않은 경우
		if (!CheckDateForm(inDataVec[4])) continue; //날짜 형식이 맞지 않은 경우



		if (!CheckModLocation(inDataVec[3], dataController)) continue; //입력한 위치가 존재하지 않을 경우
		if (!CheckWeightRule(inDataVec[1], inDataVec[2], inDataVec[3], dataController)) continue; //선반 무게를 초과하는 경우

		if (CheckRealName(inDataVec[0], inDataVec[3], dataController)) //입력한 상품이 이미 있는 상품일 경우
		{
			if (!CheckNameWeight(inDataVec[0], inDataVec[1], dataController))  continue; //상품의 정보가 등록된 정보와 다를 경우
			vector<Product*> data = dataController.FindProduct(inDataVec[0], 0);
			string cur_productID = data[0]->getID();
			product = Product::Product(cur_productID, inDataVec[0], inDataVec[1], inDataVec[3], stoi(inDataVec[2]));
		}
		else //존재하지 않은 상품일 경우 새로운 id부여
		{
			string newID = dataController.getNewPID();
			if (newID.compare("FULL") == 0)
			{
				cout << "※ 오류! 현재 프로그램에서 관리하는 물품의 종류가 너무 많습니다." << endl;
				cout << "※ 이상 품목코드를 추가할 수 없습니다.\n" << endl;
				system("PAUSE");
				return;
			}
			product = Product::Product(dataController.getNewPID(), inDataVec[0], inDataVec[1], inDataVec[3], stoi(inDataVec[2]));
		}

		shelf = dataController.FindShelf(inDataVec[3]);

		shelf->addPro(product);
		//입고 기록 

		//데이터 수정 및 저장 후 종료
		Record_data record = Record_data::Record_data(inDataVec[4], "입고", product.getLoc(), product.getID(), product.getName(), product.getNum());
		dataController.addRecord(record);
		dataController.SaveData();

		break;
	}
	cout << "입고 성공" << endl;
	system("PAUSE");
	return;
}

void Release(DataController& dataController)//출고 함수
{
	atexit(printmenu);
	string inData;
	vector<string> inDataVec; // 0:이름, 1:개수, 2:위치, 3:출고 날짜
	Product* product;
	Shelf* shelf;

	while (true)
	{
		cout << "출고할 재고의 이름과 개수, 위치, 출고 날짜를 입력하세요." << endl;
		cout << "(이름-개수-위치-출고 날짜)\n(메뉴로 돌아가려면 'q'를 입력하세요)" << endl;
		getline(cin, inData);
		cin.clear();
		if (!CheckHyphenNum(inData, 3))
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			continue;
		}
		inDataVec = split(inData, '-');
		if (inDataVec.size() == 1)
		{
			if (inDataVec[0].compare("q") == 0)//q를 입력하면 종료
			{
				return;
			}
		}
		if (inDataVec.size() != 4)
		{
			cout << "입력된 데이터의 개수가 틀립니다." << endl;
			continue;
		}

		if (!CheckNameForm(inDataVec[0])) continue; //이름 형식이 맞지 않은 경우
		if (!CheckCountForm(inDataVec[1])) continue; //개수 형식이 맞지 않은 경우
		if (!CheckLocationForm(inDataVec[2])) continue; //위치 형식이 맞지 않은 경우
		if (!CheckDateForm(inDataVec[3])) continue; //날짜 형식이 맞지 않은 경우

		if (!CheckModLocation(inDataVec[2], dataController)) continue; //입력한 위치가 존재하지 않을 경우
		if (!CheckNameCountLocation(inDataVec[0], inDataVec[1], inDataVec[2], dataController)) continue; //해당 위치에 상품의 개수가 충분하지 않은 경우
		if (!CheckDateCountRule(inDataVec[0], inDataVec[1], inDataVec[2], inDataVec[3], dataController)) continue; //입력한 날짜를 기준으로 그 이전에 해당 위치의 상품개수가 충분한지 확인

		product = dataController.FindProduct(inDataVec[2], inDataVec[0], 0);
		shelf = dataController.FindShelf(product->getLoc());

		Product temp_product;
		temp_product = Product::Product(*product);
		Record_data record(inDataVec[3], "출고", product->getLoc(), product->getID(), product->getName(), stoi(inDataVec[1]));
		shelf->relPro(*product, stoi(inDataVec[1])); //개수만큼 해당 선반에서 출고

		//출고 기록

		dataController.addRecord(record);
		dataController.SaveData();
		break;
	}
	cout << "출고 성공" << endl;
	system("PAUSE");
	return;
}

void MoveProduct(DataController& dataController)//이동 함수
{
	atexit(printmenu);
	string inData, locationData;
	vector<string> inDataVec; // 0:이름, 1:개수, 2:위치, 3:날짜
	Product* product = NULL;
	Product temp_product;
	Shelf* shelf;

	while (true)
	{
		cout << "이동할 재고의 이름과 개수, 위치, 날짜를 입력하세요." << endl;
		cout << "(이름-개수-위치-날짜)\n(메뉴로 돌아가려면 'q'를 입력하세요)" << endl;
		getline(cin, inData);
		cin.clear();
		if (!CheckHyphenNum(inData, 3))
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			continue;
		}
		inDataVec = split(inData, '-');
		if (inDataVec.size() == 1)
		{
			if (inDataVec[0].compare("q") == 0)//q를 입력하면 종료
			{
				return;
			}
		}
		if (inDataVec.size() != 4)
		{
			cout << "입력된 데이터의 개수가 틀립니다." << endl;
			continue;
		}
		if (!CheckNameForm(inDataVec[0])) continue; //이름 형식이 맞지 않은 경우
		if (!CheckCountForm(inDataVec[1])) continue; //개수 형식이 맞지 않은 경우
		if (!CheckLocationForm(inDataVec[2])) continue; //위치 형식이 맞지 않은 경우
		if (!CheckDateForm(inDataVec[3])) continue; //날짜 형식이 맞지 않은 경우

		if (!CheckModLocation(inDataVec[2], dataController)) continue; //입력한 위치가 존재하지 않을 경우
		if (!CheckNameCountLocation(inDataVec[0], inDataVec[1], inDataVec[2], dataController)) continue; //해당 위치에 상품의 개수가 충분하지 않은 경우
		if (!CheckDateCountRule(inDataVec[0], inDataVec[1], inDataVec[2], inDataVec[3], dataController)) continue; //입력한 날짜를 기준으로 그 이전에 해당 위치의 상품개수가 충분한지 확인

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

		string product_weight = to_string(product->getWeight()); //해당 상품의 무게 정보를 가져옴

		cout << "해당재고를 이동할 위치를 입력하세요." << endl;
		getline(cin, locationData);
		cin.clear();
		if (!CheckLocationForm(locationData)) continue; //이동할 위치 형식이 맞지 않은 경우

		if (!CheckSameLocation(inDataVec[2], locationData)) continue; //이동할 위치가 현재 위치와 같을 경우
		if (!CheckModLocation(locationData, dataController)) continue; //이동할 위치가 존재하지 않을 경우
		if (!CheckWeightRule(product_weight, inDataVec[1], locationData, dataController)) continue; //선반 무게를 초과하는 경우

		//product = dataController.FindProduct(inDataVec[2], inDataVec[0], 0);

		temp_product = Product::Product(*product);

		shelf->relPro(*product, stoi(inDataVec[1])); //해당 상품을 선반에서 꺼냄

		shelf = dataController.FindShelf(locationData);
		temp_product.setNum(stoi(inDataVec[1]));
		temp_product.setLocation(locationData);
		shelf->addPro(temp_product); //상품을 이동하고자 하는 위치에 입고


		//================기록 저장==================
		Record_data record_out(inDataVec[3], "출고", temp_product.getLoc(), temp_product.getID(), temp_product.getName(), stoi(inDataVec[1])); //출고 기록
		Record_data record_in(inDataVec[3], "입고", locationData, temp_product.getID(), temp_product.getName(), stoi(inDataVec[1])); //입고 기록
		dataController.addRecord(record_out);
		dataController.addRecord(record_in);
		dataController.SaveData();
		//===========================================

		break;
	}
	cout << "이동 성공" << endl;
	system("PAUSE");
	return;
}



//========형식 확인 함수==========

bool CheckLocationForm(string& location)
{
	//위치 정보의 형식 체크 1,2,3,4 또는 1234
	//,문자 제거 후 4자리 정수 확인
	string temp = location;
	int count = 0; //,의 개수를 세는 변수
	int k;
	size_t errorIndex = NULL;

	string temp_digit = temp;

	temp_digit.erase(remove(temp_digit.begin(), temp_digit.end(), ','), temp_digit.end());
	for (int i = 0; i < temp_digit.size(); i++)
	{
		if (isdigit(temp_digit[i]) == 0) //정수가 아닌 문자가 있을 경우
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
	}

	if (temp.size() == 4)
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if (isdigit(temp[i]) == 0 || temp[i] == '0') //정수가 아닌 문자가 있을 경우
			{
				cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
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
		if (count != 3) //입력된 ,의 수가 3개인지 확인
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}

		temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
	}
	else
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	try
	{
		k = stoi(temp);
	}
	catch (const std::exception& expn)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}

	if (k < 1111 || k>9999)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}

	location = temp; //해당 위치를 1234형식으로 변경

	return true;
}

bool CheckNameForm(string& name)
{
	//특수문자 불가(구현X), 대소문자 구분하지 않음, 1~16자 이내, 공백 제거
	string temp = name;
	int k = 0;
	bool k_check = true;
	temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end()); //공백 제거
	temp.erase(remove(temp.begin(), temp.end(), '\t'), temp.end()); //탭 제거
	if (temp.size() == 0)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	for (int i = 0; i < temp.size(); i++) //소문자 변환
	{
		temp[i] = tolower(temp[i]);
		if (temp.at(i) & 0x80) //입력한 글자가 한글
		{
			k++;
		}

	}
	k = k / 2;
	if ((temp.size() > 16 + k) || (temp.size() > 32))
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}

	name = temp; //이름의 공백 제거 및 소문자화

	return true;
}

bool CheckCountForm(string count)
{
	//정수인지 확인 및 범위 확인
	bool isNotZero = false;
	int temp;

	if (count.size() == 0)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	for (int i = 0; i < count.size(); i++)
	{
		if (isdigit(count[i]) == 0) //정수가 아닌 문자가 있을 경우
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
		if (count[i] == '0' && !isNotZero) //만약 처음 자리에 0이 올 경우
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
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
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	if (temp < 1 || temp > 10000) //값이 1보다 작거나 10000보다 클 경우
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}

	return true;
}

bool CheckWeightForm(string weight)
{
	//0.00형태인지 확인
	//15.00 1.15 3.40 가능 / .52 324 3.512 불가능
	//.을 기준으로 나누고 앞자리에 
	vector<string> temp;
	temp = split(weight, '.');
	bool isNotZero = false;
	double d;

	if (weight.size() == 0)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}

	if (temp.size() != 2)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	if (temp[0].size() == 0)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	for (int i = 0; i < temp[0].size(); i++)
	{
		if (isdigit(temp[0][i]) == 0) //정수가 아닌 수가 있을 경우
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
		if (temp[0][i] == '0' && !isNotZero && temp[0].size() != 1) //만약 처음 자리에 0이 오거나 0이 하나가 아닐 경우
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
		else
		{
			isNotZero = true;
		}
	}
	if (temp[1].size() != 2)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	for (int i = 0; i < temp[1].size(); i++)
	{
		if (isdigit(temp[1][i]) == 0) //정수가 아닌 수가 있을 경우
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
	}
	try
	{
		d = stod(weight);
	}
	catch (const std::exception& expn)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	if (d == 0)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}

	return true;
}

bool CheckDateForm(string& date)
{
	//2021/02/10 또는 20210210인지 확인 및 2000년대 인지 확인
	string temp = date;
	int year, month, day;

	if (temp.size() == 8)
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if (isdigit(temp[i]) == 0) //정수가 아닌 문자가 있을 경우
			{
				cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
				return false;
			}
		}
	}
	else if (temp.size() == 10)
	{
		if (temp.at(4) != '/' || temp.at(7) != '/')
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
		temp.erase(remove(temp.begin(), temp.end(), '/'), temp.end());
	}
	else
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
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
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	if (year < 1 || year > 9999)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}
	if (month < 1 || month > 12)
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}

	//윤년 계산
	if (year % 4 == 0)
	{
		if (year % 100 != 0)
		{
			if (month == 2)
			{
				if (day < 1 || day > 29)
				{
					cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
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
						cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
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
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
	}
	else if (month == 2)
	{
		if (day < 1 || day > 28)
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
	}
	else
	{
		if (day < 1 || day > 30)
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
	}

	temp.insert(4, "/");
	temp.insert(7, "/");

	date = temp; //날짜를 2021/10/22 형식으로 변형

	return true;
}

//===============================

//========규칙 확인 함수==========

bool CheckRealLocation(string location, DataController& dataController)
{
	//위치가 실제로 존재하는 지 확인
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

	if (!isReal) //해당위치가 존재 하지 않는 다면
	{
		cout << "※ 오류! 현재 위치는 없는 위치 정보입니다.\n" << endl;
		return false;
	}

	return true;
}

bool CheckRealName(string name, string location, DataController& dataController)
{
	//해당 위치에 상품이 존재하는지 확인
	string in_name = name;
	string in_location = location;

	Product* temp = dataController.FindProduct(in_location, in_name, 0);

	if (temp == NULL) //상품이 존재하지 않을 경우
	{
		return false;
	}

	return true;
}

bool CheckNameCountLocation(string name, string count, string location, DataController& dataController)
{
	//해당 위치에 상품의 개수가 충분한지 확인
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
		cout << "※ 오류! 해당 위치에 상품이 존재하지 않습니다.\n" << endl;
		return false;
	}

	if (in_count > temp->getNum()) //꺼내려는 개수가 입고된 개수보다 클 경우
	{
		cout << "※ 오류! 현재 저장된 재고의 개수를 넘겼습니다." << endl;
		cout << "[" << in_name << "]재고의 현재 저장 개수 : [" << temp->getNum() << "] 개\n" << endl;
		return false;
	}

	return true;
}

bool CheckWeightRule(string weight, string count, string location, DataController& dataController)
{
	//무게가 현재 구역의 최대치를 넘는지 확인하는 함수
	string in_location = location;
	vector<int> locationVec;


	in_location.erase(remove(in_location.begin(), in_location.end(), ','), in_location.end());
	for (int i = 0; i < in_location.size(); i++)
	{
		int temp = in_location.at(i) - '0';
		locationVec.push_back(temp);
	}

	Shelf* shelf = dataController.FindShelf(location);

	double cur_weight = dataController.FindShelf(location)->getCurWeight(); //위치의 선반으로 부터 현재 무게를 가져옴
	double max_weight = dataController.FindShelf(location)->getMaxWeight(); //창고 정보로 부터 최대 무게를 가져옴
	double sum = cur_weight + stod(weight) * stoi(count);

	if (sum > max_weight)
	{
		cout << "※ 오류! 해당 위치의 무게가 초과하여 입고할 수 없습니다.\n" << endl;
		return false;
	}

	return true;
}

bool CheckDateRule(string rel_date, string str_date)
{
	//입력된 날짜가 비교 날짜 이후 날짜인지 확인하는 함수
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

	//출고 날짜가 입고 날짜보다 이전이면 false반환

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
	//product.txt를 참조하여 name이 존재할 경우 그 상품의 이름과 무게를 입력값과 비교하여 동일 여부 반환

	//		product.txt에 해당 상품의 이름이 있는 지 확인
	//		있으면 무게를 비교
	//		무게가 다르면 경고 메시지와 false반환
	//		없으면 true 반환
	string in_name = name;
	double in_weight = stod(weight);
	in_name.erase(remove(in_name.begin(), in_name.end(), ' '), in_name.end()); //공백 제거

	vector<Product*> data = dataController.FindProduct(in_name, 0);
	if (&data == NULL)
	{
		return false;
	}
	else
	{
		if (data[0]->getWeight() != in_weight)
		{
			cout << "※ 오류! 등록된 무게와 입력한 무게가 서로 다릅니다." << endl;
			cout << "※ 등록된 무게:" << data[0]->getWeight() << "\n" << endl;
			return false;
		}
	}

	return true;
}

bool CheckSameLocation(string rel_location, string str_location)
{
	//원래 위치와 이동할 위치가 같은지 비교
	string rel_temp = rel_location;
	string str_temp = str_location;

	//rel_temp.erase(remove(rel_temp.begin(), rel_temp.end(), ','), rel_temp.end());
	//str_temp.erase(remove(str_temp.begin(), str_temp.end(), ','), str_temp.end());

	if (rel_temp.compare(str_temp) == 0)
	{
		cout << "※ 오류! 이동할 위치가 현재 위치입니다.\n" << endl;
		return false;
	}

	return true;
}

bool CheckSameLocationForRecord(string rel_location, string str_location)
{
	//원래 위치와 이동할 위치가 같은지 비교, 기록 탐색용
	if (rel_location.compare(str_location) == 0)
	{
		return true;
	}
	return false;
}

bool CheckDateCountRule(string name, string count, string location, string date, DataController& dataController)
{
	//해당 위치의 상품이 출고 날짜 이전에 몇개의 상품이 존재하는지 확인하는 함수
	vector<Record_data*> temp = dataController.FindRecord(name, 0);

	int in_num = stoi(count);
	string date_temp = "";
	int cur_num = 0;
	int isSame = 0;
	int isRecord = 0;
	for (int i = 0; i < temp.size(); i++)
	{
		//각 기록을 확인하여 출고하고자 하는 날 이후 일 경우 입출고 개수를 종합한다.
		if (location.compare(temp[i]->getLoc()) == 0)
		{
			if (CheckDateRule(date, temp[i]->getTime()))
			{
				if (temp[i]->getKind().compare("입고") == 0)
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
		cout << "※ 오류! 입력 날짜를 출고 날짜로 설정할 수 없습니다." << endl;
		cout << "※ 해당 날짜 이전에 입고된 기록이 없습니다.\n" << endl;
		return false;
	}
	if (isSame == 0) return true;
	if (in_num > cur_num)
	{
		cout << "※ 오류! 입력 날짜를 출고 날짜로 설정할 수 없습니다." << endl;
		cout << "[" << count << "]개의 재고를 꺼내기 위해선, [" << date_temp << "] 이후여야 합니다.\n" << endl;
		return false;
	}

	return true;
}

void ModWare(DataController& dataController)
{
	//atexit(printmenu);
	string inData;
	vector<string> inDataVec;	// 0 : 수정할 창고 위치, 1 : 수정할 최대 무게

	while (true)
	{
		cout << "수정할 창고의 위치와 층의 최대 무게를 입력하세요." << endl;
		cout << "(메뉴로 돌아가려면 'q'를 입력하세요)" << endl;
		getline(cin, inData);
		cin.clear();
		if (!CheckHyphenNum(inData, 1))
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			continue;
		}
		inDataVec = split(inData, '-');
		if (inDataVec.size() == 1)
		{
			if (inDataVec[0].compare("q") == 0) //'q' 입력하면 종료
			{
				return;
			}
		}
		if (inDataVec.size() != 2)
		{
			cout << "입력된 데이터의 개수가 틀립니다." << endl;
			continue;
		}

		if (!CheckLocationForm(inDataVec[0])) continue; //위치 형식이 맞지 않은 경우
		if (!CheckMaxWeightForm(inDataVec[1])) continue; //층 최대 무게 형식이 맞지 않은 경우
		//if (!CheckRealLocation(inDataVec[0], dataController)) continue; //입력한 위치가 존재하지 않을 경우
		if (!CheckModLocation(inDataVec[0], dataController)) continue; //입력한 위치가 존재하지 않을 경우 2

		if (!CheckModWeight(inDataVec[0], inDataVec[1], dataController)) continue; //수정할 무게가 규칙 형식에 맞지 않을 경우

		dataController.FindShelf(inDataVec[0])->modMaxWeight(stoi(inDataVec[1]));

		dataController.SaveData();

		break;
	}
	cout << "수정 성공" << endl;
	system("PAUSE");
	return;
}

bool CheckMaxWeightForm(string maxWeight)
{
	//층 최대 무게는 1 ~ 3자리 정수
	//또한, 선행 0을 허락하지 않는다.

	if (maxWeight.size() < 1 || maxWeight.size() > 3) //1 ~ 3자리가 아닌 경우
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}

	for (int i = 0; i < maxWeight.size(); i++)
	{
		if (isdigit(maxWeight[i]) == 0) //정수가 아닌 문자가 있을 경우
		{
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
			return false;
		}
	}

	if (maxWeight[0] == '0') //선행 0인 경우
	{
		cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
		return false;
	}

	return true;
}

bool CheckModLocation(string location, DataController& dataController)
{
	//위치가 수정 가능한 곳인지 확인
	string in_location = location;
	vector<int> locationVec;

	for (int i = 0; i < in_location.size(); i++)
	{
		int temp = in_location.at(i) - '0';
		locationVec.push_back(temp);
	}

	//입력한 위치가 존재하지 않으면(수정 가능하지 않으면)
	if (!dataController.getWarehouses()[locationVec[0] - 1].getIsUse())
	{
		cout << "※ 오류! 현재 위치는 없는 위치 정보입니다.\n" << endl;
		return false;
	}

	if (!dataController.getWarehouses()[locationVec[0] - 1].getShelfs()[locationVec[1] - 1][locationVec[2] - 1][locationVec[3] - 1].getIsUse())
	{
		cout << "※ 오류! 현재 위치는 없는 위치 정보입니다.\n" << endl;
		return false;
	}

	return true;
}

bool CheckModWeight(string location, string weight, DataController& dataController)
{
	//수정하려는 무게가 지금 존재하는 물품들의 합보다 낮을 경우
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
		cout << "※ 오류! 해당 위치의 최대 무게와 동일합니다.\n" << endl;
		return false;
	}

	if (dataController.getWarehouses()[locationVec[0] - 1].getShelfs()[locationVec[1] - 1][locationVec[2] - 1][locationVec[3] - 1].getCurWeight()
	> (double)int_weight)
	{
		cout << "※ 오류! 수정할 최대 무게가 해당 위치에 저장된 물품의 무게보다 작습니다.\n" << endl;
		return false;
	}

	return true;
}

int menu6(DataController& dataController) {

	int num;
	string input = "";

	atexit(printmenu);

	cout << "[Inventory Management Program]\n";
	cout << "어떤 설정을 수행할 것인지 선택하세요.\n";
	cout << "(1) 추가   (2) 삭제  (3) 수정\n";
	cout << "(메뉴로 돌아가려면 \'q\'를 입력하세요)\n";

	while (true) {
		//system("cls");
		getline(cin, input);

		if (input == "") getline(cin, input);

		if (input == "1" || input == "추가")
		{
			num = 1;
			break;
		}
		else if (input == "2" || input == "삭제")
		{
			num = 2;
			break;
		}
		else if (input == "3" || input == "수정")
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
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n";
			cout << "[Inventory Management Program]\n";
			cout << "어떤 설정을 수행할 것인지 선택하세요.\n";
			cout << "(1) 추가   (2) 삭제  (3) 수정\n";
			cout << "(메뉴로 돌아가려면 \'q\'를 입력하세요)\n";
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
		cout << "삭제할 창고의 위치를 입력하세요\n";
		cout << "(메뉴로 돌아가라면 \'q\'를 입력하세요)\n";
		getline(cin, locaToRemove);
		cin.clear();
		if (locaToRemove == "q") {
			return;
		}
		if (locaToRemove.length() > 4) {
			cout << "다시 입력해주세요\n";
		}
		else {
			int flag = 1;
			for (int i6 = 0; i6 < locaToRemove.length(); i6++) {
				if (isdigit(locaToRemove[i6]) == 0 || locaToRemove[i6] == '0') {
					flag = 0;
					cout << "다시 입력해주세요\n";
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
			cout << "※ 오류! 해당 위치에 창고가 존재하지 않습니다.\n";
			removeWarehouse(dataController);
		}
		else if (flag6_2 == 0) {
			cout << "[Inventory Management Program]\n";
			cout << "※ 오류! 해당 위치에 물품이 존재 해 삭제할 수 없습니다.\n";
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


			cout << "삭제 성공\n";
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
			cout << "※ 오류! 해당 위치에 창고가 존재하지 않습니다.\n";
			removeWarehouse(dataController);
		}
		else if (flag6_2 == 0) {
			cout << "[Inventory Management Program]\n";
			cout << "※ 오류! 해당 위치에 물품이 존재 해 삭제할 수 없습니다.\n";
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


			cout << "삭제 성공\n";
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
			cout << "※ 오류! 해당 위치에 창고가 존재하지 않습니다.\n";
			removeWarehouse(dataController);
		}
		else if (flag6_2 == 0) {
			cout << "[Inventory Management Program]\n";
			cout << "※ 오류! 해당 위치에 물품이 존재 해 삭제할 수 없습니다.\n";
			removeWarehouse(dataController);
		}
		else {
			string p6 = locaToRemove;

			for (int i62 = 1; i62 <= 9; i62++) {
				string p6 = locaToRemove + to_string(i62);
				dataController.FindShelf(p6)->setIsUse(false);
			}

			dataController.SaveData();
			cout << "삭제 성공\n";
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
			cout << "※ 오류! 해당 위치에 창고가 존재하지 않습니다.\n";
			removeWarehouse(dataController);
		}
		else if (flag6_2 == 0) {
			cout << "[Inventory Management Program]\n";
			cout << "※ 오류! 해당 위치에 물품이 존재 해 삭제할 수 없습니다.\n";
			removeWarehouse(dataController);
		}
		else {

			string p6 = locaToRemove;
			dataController.FindShelf(p6)->setIsUse(false);


			dataController.SaveData();
			cout << "삭제 성공\n";
			read.open("./Inventory_Files/SettingWarehouses.txt");
			if (read.peek() == ifstream::traits_type::eof())
			{
				setwarehouse();
			}
			read.close();
		}
	}
}

//진우
bool CheckMaxWeightForm_add(string maxWeight)
{
	//층 최대 무게는 1 ~ 3자리 정수
	//또한, 선행 0을 허락하지 않는다.

	if (maxWeight.size() < 1 || maxWeight.size() > 3) //1 ~ 3자리가 아닌 경우
	{
		return false;
	}

	for (int i = 0; i < maxWeight.size(); i++)
	{
		if (isdigit(maxWeight[i]) == 0) //정수가 아닌 문자가 있을 경우
		{
			return false;
		}
	}

	if (maxWeight[0] == '0') //선행 0인 경우
	{
		return false;
	}

	return true;
}

// 창고 추가, 진우
int add_Warehouses()
{
	//atexit(printmenu);
	bool flag = true;

	string input;								// '창고-최대 무게'가 들어갈 문자열 변수
	while (1)
	{
		try
		{
			// 입력 받기
			cout << "[Inventory Management Program]" << endl;
			cout << "추가할 창고의 위치와 층의 최대 무게를 입력하세요.(위치-최대 무게)" << endl;
			cout << "(메뉴로 돌아가려면 'q'를 입력하세요)" << endl;
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
				cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
				continue;
			}

			// 창고 - 최대 무게 형식 검사
			if (input[4] != '-')
			{
				cout << "\n[Inventory Management Program]" << endl;
				cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
				continue;
			}

			vector<string> output = split(input, '-'); // output = [location, weight] 꼴
			string location = output.at(0);
			string weight = output.at(1);

			// location, weight 입력 규칙 확인(weight 규칙 추가 필요)
			if ((flag = CheckLocationForm(location)) && (CheckMaxWeightForm_add(weight)))
			{

				int n = static_cast<int>(location.at(0)) - 48;					// 창고 번호(n)
				int i = static_cast<int>(location.at(1)) - 48;					// 구역 번호(i)
				int j = static_cast<int>(location.at(2)) - 48;					// 선반 번호(j)
				int k = static_cast<int>(location.at(3)) - 48;					// 층 번호(k)


				// 이미 창고가 존재하는지 파악해야함
				//if (!dataController.getWarehouses()[n - 1].getIsUse() && !(dataController.getWarehouses()[n - 1].getShelfs()[i - 1][j - 1][k - 1].getIsUse()))
				if (!(dataController.getWarehouses()[n - 1].getShelfs()[i - 1][j - 1][k - 1].getIsUse()))
				{
					ofstream ofs("Inventory_Files/SettingWarehouses.txt", ios::app);
					// SettingWarehouses 열기 실패
					if (!ofs)
					{
						cerr << "SettingWarehouses open fail" << endl;
						exit(1);
					}


					dataController.getWarehouses()[n - 1].setIsUse(true);		// n번 창고 만들었으니 true로 변환
					dataController.getWarehouses()[n - 1].getShelfs()[i - 1][j - 1][k - 1].setIsUse(true);		// n번 창고의 i구역 j번 선반 k층 true로 변환
					dataController.getWarehouses()[n - 1].getShelfs()[i - 1][j - 1][k - 1].modMaxWeight(stoi(weight));
					ofs << '\n' + location + '-' + weight;
					cout << "창고 추가 완료\n" << endl;
					continue;
				}

				// 창고가 이미 존재함
				else
				{
					cout << "\n[Inventory Management Program]" << endl;
					cout << "※ 오류! 해당 위치에 이미 창고가 존재합니다.\n" << endl;
					continue;
				}
			}

			// location, weight 입력 규칙 벗어남
			else
			{
				if (flag) {
					cout << "\n[Inventory Management Program]" << endl;
					cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
				}
				continue;
			}
		}
		catch (const std::exception& expn)
		{
			cout << "\n[Inventory Management Program]" << endl;
			cout << "※ 오류! 문법 및 입력 규칙을 벗어난 입력입니다.\n" << endl;
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