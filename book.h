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

void xoaKhoangTrang(string& a)
{
	//xóa đầu
	while (a[0] == ' ')
		a.erase(0, 1);

	//xóa cuối
	while (a[a.size() - 1] == ' ')
		a.erase(a.size() - 1, 1);


	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == ' ' && a[i + 1] == ' ')
		{
			a.erase(i, 1);
			i--;
		}
	}
}

void ChuanHoaChuoi(string& a)
{
	int i = 0;
	while (a[i] != '\0')
	{
		if (i == 0)
		{
			if (a[i] < 'A' || a[i]>'Z')
				a[i] = a[i] - 32;
		}
		else
		{
			if (a[i - 1] == ' ' && a[i] != ' ' && a[i] >= 'a' && a[i] <= 'z')
				a[i] = a[i] - 32;
			else if (a[i] >= 'A' && a[i] <= 'Z' && (a[i - 1] != ' '))
				a[i] = a[i] + 32;
		}
		i++;
	}
}

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

	xoaKhoangTrang(book.ten);
	xoaKhoangTrang(book.tacGia);
	xoaKhoangTrang(book.NXB);
	ChuanHoaChuoi(book.ten);
	ChuanHoaChuoi(book.tacGia);
	ChuanHoaChuoi(book.NXB);
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
	xoaKhoangTrang(book.ten);
	xoaKhoangTrang(book.tacGia);
	xoaKhoangTrang(book.NXB);
	ChuanHoaChuoi(book.ten);
	ChuanHoaChuoi(book.tacGia);
	ChuanHoaChuoi(book.NXB);

	fileOut << endl << book.id << "#"
		<< book.ten << "#"
		<< book.tacGia << "#"
		<< book.NXB << "#"
		<< book.nam;
}
