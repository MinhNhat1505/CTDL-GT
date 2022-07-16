#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Book
{
	int id;
	string ten, tacGia, NXB;
	int nam;
};

void nhap1Sach(Book& book)
{
	cout << "+Nhap id cua sach: ";
	cin >> book.id;
	cin.ignore();
	cout << "+Nhap ten sach: ";
	getline(cin, book.ten);
	cout << "+Nhap tac gia cua cuon sach: ";
	getline(cin,book.tacGia);
	cout << "+Nhap nha xuat ban cua cuon sach: ";
	getline(cin,book.NXB);
	cout << "+Nhap nam xuat ban cua cuon sach: ";
	cin >> book.nam;
}

void xuat1sach(Book book)
{
	cout << "+ID sach: " << book.id << endl
		<< "+Ten sach: " << book.ten << endl
		<< "+Tac gia: " << book.tacGia << endl
		<< "+Nha xuat ban: " << book.NXB << endl
		<< "+Nam xuat ban: " << book.nam << endl;
}

//hàm đọc 1 file
void docFile(Book& book,ifstream& fileIn)
{
	fileIn >> book.id;
	fileIn.ignore();
	getline(fileIn, book.ten,'#');
	getline(fileIn, book.tacGia,'#');
	getline(fileIn, book.NXB,'#');
	fileIn >> book.nam;
}

//hàm ghi thông tin vào cuối file
void ghiFileVaoCuoi(Book book, ofstream& fileOut)
{
	fileOut << endl << book.id << "#"
		<< book.ten << "#"
		<< book.tacGia << "#"
		<< book.NXB << "#"
		<< book.nam;
}

//Hàm ghi thông tin vào đầu file
void ghiFileVaoDau(Book book, ofstream& fileOut)
{
	fileOut << book.id << "#"
		<< book.ten << "#"
		<< book.tacGia << "#"
		<< book.NXB << "#"
		<< book.nam << endl;
}