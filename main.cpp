#include<iostream>
#include<conio.h>
#include "node.h"
#include<vector>
using namespace std;

void menu();
void add_Publisher_to_vector(string name, vector<string>& publisher, vector<int>& number);
bool getPublisher(doubList list, vector<string>& publisher, vector<int>& number);
bool sort_num_of_Publisher(vector<string>& publisher, vector<int>& number);
void print_Publisher_list(vector<string>& publisher, vector<int>& number);

int main()
{
	int chon;
	bool openFile = false, get_Publisher = false;

	/*
	list1:list chính
	list2:list chứa sách được xếp theo tên sách tăng dần(dùng cho mục 8)
	list3:list chứa sách đc xếp theo năm giảm dần(mục 9)
	publisher - number: mảng chứa tên nhà xuất bản / chứa số lượng cuốn sách mà của NXB đó (dùng cho mục 10)
	*/
	doubList list1, list2, list3;
	vector<string>publisher;
	vector<int>number;

	bool needUPdList2 = false,
		needUpdList3 = false,
		needUpPublisher = false;

	init(list1);
	init(list2);
	init(list3);
	do
	{
		system("cls");
		menu();

		do
		{
			cout << "Ban chon: ";
			cin >> chon;
		} while (chon <= 0 || chon > 11);

		switch (chon)
		{
		case 1:
			if (!openFile)
			{
				readFile(list1, "DS_sach.txt");
				cout << "Lay thong tin tu file thanh cong\n";
				openFile = true;
			}
			else
				cout << "Ban da mo file roi!\n";
			break;
		case 2:
			if (openFile)
			{
				int choice;
				system("cls");
				do
				{
					cout << "Ban muon tim sach theo id hay theo ten?\n"
						<< "Ban chon(1:id/2:sach): ";
					cin >> choice;
				} while (choice != 1 && choice != 2);

				if (choice == 1)
				{
					int id;
					cout << "Nhap id can tim: ";
					cin >> id;
					Find_Book_by_id(list1, id);
				}
				else
				{
					string n;
					cout << "Nhap ten sach: ";
					cin.ignore();
					getline(cin, n);
					Find_Book_by_name(list1, n);
				}
			}
			else
				cout << "Vui long nhap du lieu tu file!\n";
			break;
		case 3:
			if (openFile)
			{
				string n;
				cout << "Nhap ten tac gia ban muon tim: ";
				cin.ignore();
				getline(cin, n);
				print_author(list1, n);
			}
			else
				cout << "Vui long nhap du lieu tu file!\n";
			break;
		case 4:
			if (openFile)
			{
				string n;
				cout << "Nhap nha xuat ban ma ban muon tim: ";
				cin.ignore();
				getline(cin, n);
				print_publisher(list1, n);
			}
			else
				cout << "Vui long nhap du lieu tu file!\n";
			break;
		case 5:
			if (openFile)
			{
				int x;
				do
				{
					addFileFromTail(list1, "DS_sach.txt");
					cout << "Ban co muon thoat?(bam 0 de thoat): ";
					cin >> x;
				} while (x != 0);

				//nếu như chọn mục 8/9/10 mà quay lại mục 5 thì update list của mục 8/9/10
				if (!isEmpty(list2))
					needUPdList2 = true;
				if (!isEmpty(list3))
					needUpdList3 = true;
				if (publisher.size() != 0)
					needUpPublisher = true;
			}
			else
				cout << "Vui long nhap du lieu tu file!\n";
			break;
		case 6:
			if (openFile)
			{
				if (isEmpty(list1))
					cout << "Khong co data de xu li!\n";
				else
				{
					int id;
					do
					{
						cout << "Nhap id sach ban muon xoa: ";
						cin >> id;
						bool check = del_book_by_ID(list1, id);
						if (!check)
						{
							cout << "ID ban nhap khong ton tai,vui long nhap lai!\n";
						}
						else
							break;
					} while (true);
					cout << "Xoa thanh cong\n";
					updateFile(list1, "DS_sach.txt");
					//nếu như chọn mục 8/9/10 mà quay lại mục 6 thì update list của mục 8/9/10
					if (!isEmpty(list2))
						needUPdList2 = true;
					if (!isEmpty(list3))
						needUpdList3 = true;
					if (publisher.size() != 0)
						needUpPublisher = true;
				}
			}
			else
				cout << "Vui long nhap du lieu tu file!\n";
			break;
		case 7:
			if (openFile)
			{
				string ten;
				cout << "Nhap ten tac gia: ";
				cin.ignore();
				getline(cin, ten);
				if (del_book_by_author(list1, ten))
				{
					updateFile(list1, "DS_sach.txt");
					cout << "Xoa thanh cong!\n";

					//nếu như chọn mục 8/9/10 mà quay lại mục 7 thì update list của mục 8/9/10
					if (!isEmpty(list2))
						needUPdList2 = true;
					if (!isEmpty(list3))
						needUpdList3 = true;
					if (publisher.size() != 0)
						needUpPublisher = true;
				}
				else
					cout << "Ten tac gia ban nhap khong ton tai!\n";
			}
			else
				cout << "Vui long nhap du lieu tu file!\n";
			break;
		case 8:
			if (openFile)
			{
				system("cls");
				if (needUPdList2 && !isEmpty(list2))
				{
					needUPdList2 = false;
					del_list(list2);
				}
				if (isEmpty(list2))
				{
					copyList(list1, list2);
					sortList_Book(list2);
				}
				process_list(list2);
			}
			else
				cout << "Vui long nhap du lieu tu file!\n";
			break;
		case 9:
			if (openFile)
			{
				system("cls");

				if (needUpdList3 && !isEmpty(list3))
				{
					needUpdList3 = false;
					del_list(list3);
				}

				if (isEmpty(list3))
				{
					copyList(list1, list3);
					sortList_year(list3);
				}

				process_list(list3);
			}
			else
				cout << "Vui long nhap du lieu tu file!\n";
			break;
		case 10:
			if (openFile)
			{
				if (needUpPublisher)
				{
					needUpPublisher = false;
					publisher.erase(publisher.begin(), publisher.end());
					number.erase(number.begin(), number.end());
				}

				if (publisher.size() == 0)
				{
					getPublisher(list1, publisher, number);
					sort_num_of_Publisher(publisher, number);
				}
				system("cls");
				print_Publisher_list(publisher, number);
			}
			else
				cout << "Vui long nhap du lieu tu file!\n";
			break;
		default:
			cout << "Ban chon thoat!\n";
			break;
		}
		(void)_getch();
	} while (chon > 0 && chon < 11);
}

void menu()
{
	cout << "********************QUAN LI SACH TRONG THU VIEN********************\n"
		<< "**     1.Nhap muc sach tu file                                   **\n"
		<< "**     2.Tim kiem sach theo ma,ten sach                          **\n"
		<< "**     3.In sach theo ten tac gia                                **\n"
		<< "**     4.In sach theo nha xuat ban                               **\n"
		<< "**     5.Them sach                                               **\n"
		<< "**     6.Xoa 1 quyen sach theo ma sach                           **\n"
		<< "**     7.Xoa tat ca sach theo ten tac gia                        **\n"
		<< "**     8.In danh muc sach theo ten sach tang dan                 **\n"
		<< "**     9.In danh muc sach theo nam xuat ban giam dan             **\n"
		<< "**     10.In danh sach thong ke so luong sach theo NXB giam dan  **\n"
		<< "**     11.Thoat                                                  **\n"
		<< "*******************************************************************\n";
}

//thêm 1 tác giả vào vector
void add_Publisher_to_vector(string name, vector<string>& publisher, vector<int>& number)
{
	if (publisher.empty())
	{
		publisher.push_back(name);
		number.push_back(1);
	}
	else
	{
		bool input = false;
		for (int i = 0; i < publisher.size(); i++)
		{
			if (publisher[i] == name)
			{
				number[i] += 1;
				input = true;
				break;
			}
		}
		if (!input)
		{
			publisher.push_back(name);
			number.push_back(1);
		}
	}
}

//lấy toàn bộ thông tin của NXB từ dslk
bool getPublisher(doubList list, vector<string>& publisher, vector<int>& number)
{
	Node* p = list.first;
	if (p == NULL)
		return false;
	while (p != NULL)
	{
		add_Publisher_to_vector(p->info.NXB, publisher, number);
		p = p->next;
	}
	return true;
}

//sắp xếp theo thứ tự giảm dần
bool sort_num_of_Publisher(vector<string>& publisher, vector<int>& number)
{
	if (number.empty())
		return false;
	if (number.size() == 1)
		return true;
	for (int i = 0; i < number.size() - 1; i++)
		for (int j = i + 1; j < number.size(); j++)
			if (number[j] > number[i])
			{
				//doi vi tri number
				swap_int(number[i], number[j]);

				//doi vi tri publisher
				swap_string(publisher[i], publisher[j]);
			}
	return true;
}

void print_Publisher_list(vector<string>& publisher, vector<int>& number)
{
	cout << "=========================\n";
	for (int i = 0; i < publisher.size(); i++)
	{
		cout << "Nha xuat ban: " << publisher[i] << endl
			<< "so luong:" << number[i] << endl;
		cout << "=========================\n";
	}
}