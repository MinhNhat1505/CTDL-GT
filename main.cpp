#include<iostream>
#include<conio.h>
#include "node.h"
using namespace std;

void menu();

int main()
{
	int chon;
	doubList list1;
	
	init(list1);
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
			readFile(list1, "DS_sach.txt");
			cout << "Lay thong tin tu file thanh cong\n";
			break;
		case 2:
			process_list(list1);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			int x;
			do
			{
				addFileFromTail(list1, "DS_sach.txt");
				cout << "Ban co muon tiep tuc?(bam 0 de thoat): ";
				cin >> x;
			} while (x != 0);
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
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
	cout << "***************QUAN LI SACH TRONG THU VIEN***************\n"
		<< "**     1.Nhap muc sach tu file                         **\n"
		<< "**     2.Tim kiem sach theo ma,ten sach                **\n"
		<< "**     3.In sach theo ten tac gia                      **\n"
		<< "**     4.In sach theo nha xuat ban                     **\n"
		<< "**     5.Them sach                                     **\n"
		<< "**     6.Xoa 1 quyen sach theo ma sach                 **\n"
		<< "**     7.Xoa tat ca sach theo ten tac gia              **\n"
		<< "**     8.In danh muc sach theo ten sach                **\n"
		<< "**     9.In danh muc sach theo nam xuat ban            **\n"
		<< "**     10.In danh sach thong ke so luong sach theo NXB **\n"
		<< "**     11.Thoat                                        **\n"
		<< "*********************************************************\n";
}