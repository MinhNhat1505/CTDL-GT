#include <iostream>
#include "function_BT5.cpp"
using namespace std;

int main()
{
	int a[MAX], front, rear, n;
	do {
		cout << "Nhap so nguyen duong: ";
		cin >> n;
		if (n < 0)
			cout << "Phai la so nguyen duong!\n";
	} while (n < 0);
	cout << "So dao nguoc cua " << n << " la: ";
	daonguocSo(a,front, rear, n);
}