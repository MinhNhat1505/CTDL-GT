#include "book.h"

struct Node
{
	Book info;
	Node* next;
	Node* pre;
};

struct doubList
{
	Node* first;
	Node* last;
};

void init(doubList& list)
{
	list.first = list.last = NULL;
}

//hàm tạo 1 node mới
Node* createNode(Book data)
{
	Node* p = new Node;
	p->info = data;
	p->next = NULL;
	p->pre = NULL;
	return p;
}

bool isEmpty(doubList& list)
{
	if (list.first == NULL)
		return true;
	return false;
}

void swap_string(string& a, string& b)
{
	string temp = a;
	a = b;
	b = temp;
}

void swap_int(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void swap_book(Book& a, Book& b)
{
	Book t = a;
	a = b;
	b = t;
}

//thêm thông tin vào đầu ds
void add_Head(doubList& list, Book data)
{
	Node* p = createNode(data);//tạo 1 node mới với data 

	if (isEmpty(list))
	{
		list.first = list.last = p;
	}
	else
	{
		list.first->pre = p;
		p->next = list.first;
		list.first = p;
	}
}

//thêm thông tin vào cuối ds
void add_Tail(doubList& list, Book data)
{
	Node* p = createNode(data);//tạo 1 node với data

	if (isEmpty(list))
	{
		list.first = list.last = p;
	}
	else
	{
		list.last->next = p;
		p->pre = list.last;
		list.last = p;
	}
}

//xóa 1 node ở đầu ds
bool del_first(doubList& list)
{
	if (list.first == NULL)//ds rỗng => trả về false
		return false;

	Node* p = list.first;
	list.first = list.first->next;
	delete p;
	if (list.first == NULL)//nếu ds hết phần tử => last = null
		list.last = NULL;
	else
		list.first->pre = NULL;
	return true;
}

//xóa 1 node ở cuối ds
bool del_last(doubList& list)
{
	if (list.last == NULL)//ds rỗng => trả về false
		return false;

	Node* p = list.last;
	list.last = list.last->pre;
	delete p;
	if (list.last == NULL)//nếu ds hết phần tử => last = null
		list.first = NULL;
	else
		list.last->next = NULL;
	return true;
}

//xóa 1 node nếu như biết thông tin của node đó
bool del_node(doubList& list, Node*& node)
{
	if (list.first == NULL)
		return false;
	if (node == list.first)
	{
		del_first(list);
		return true;
	}
	if (node == list.last)
	{
		del_last(list);
		return true;
	}
	Node* p = node->next;
	Node* q = node->pre;
	q->next = p;
	p->pre = q;
	delete node;
	return true;
}

//xóa toàn bộ thông tin của 1 dslk
bool del_list(doubList& list)
{
	if (list.first == NULL)
		return true;
	if (list.first == list.last)
	{
		del_first(list);
		return true;
	}
	while (!isEmpty(list))
		del_first(list);
	return true;
}

//KT ID của sách xem đã có tồn tại hay không,nếu có thì => true,không thì false
bool checkID(doubList list, int id)
{
	Node* p = list.first;
	while (p != NULL && p->info.id != id)
		p = p->next;
	if (p == nullptr)
		return false;
	return true;
}

//sao chép toàn bộ thông tin từ list1 sang list 2
void copyList(doubList list1, doubList& list2)
{
	if (list1.first == NULL)
		return;
	Node* p = list1.first;
	while (p != NULL)
	{
		add_Tail(list2, p->info);
		p = p->next;
	}
}

//Hàm kt file có rỗng hay không ? có => true,không => false
bool file_empty(string url)
{
	ifstream pFile(url);
	return pFile.peek() == EOF;
}

//ghi tất cả thông tin từ dslk sang file
void writeToFile(doubList list, string url)
{
	ofstream outF;
	outF.open(url);
	if (outF.is_open())
	{
		Node* p = list.first;
		if (p == NULL)//nếu dslk rỗng thì thoát
			return;
		bool first = file_empty(url);
		while (p != NULL)
		{
			if (first)
			{
				outF << p->info.id << "#"
					<< p->info.ten << "#"
					<< p->info.tacGia << "#"
					<< p->info.NXB << "#"
					<< p->info.nam;
				first = false;
			}
			else
				ghiFileVaoCuoi(p->info, outF);
			p = p->next;
		}
	}
	else
		cout << "Khong mo duoc file\n";
	outF.close();
}

//gán toàn bộ thông tin trong file vào dslk
void readFile(doubList& list, string url)
{
	ifstream inF;//khởi tạo file muốn đọc
	inF.open(url);//mở file

	if (inF.is_open())
	{
		while (!inF.eof())
		{
			Book data;//khởi tạo data

			docFile(data, inF);//cập nhập data
			add_Tail(list, data);
		}
	}
	else
	{
		cout << "Mo file khong thanh cong!\n";
	}
	inF.close();
}

//thêm dữ liệu vào cuối file
void addFileFromTail(doubList& list, string url)
{
	ofstream outF;
	outF.open(url, ios::app);
	if (outF.is_open())
	{
		Book data;

		do//KT id
		{
			nhap1Sach(data);
			if (checkID(list, data.id))
				cout << "ID da ton tai,vui long chon id khac\n";
		} while (checkID(list, data.id));
		add_Tail(list, data);
		ghiFileVaoCuoi(data, outF);
	}
	else
	{
		cout << "Mo file khong thanh cong\n";
	}
	outF.close();
}

//xóa toàn bộ thông tin trong file
bool del_all_file(string url)
{
	ofstream outf;
	outf.open(url);
	if (outf.is_open())
	{
		outf.close();
		return true;
	}
	return false;
}

//xóa sách theo id
bool del_book_by_ID(doubList& list, int data)
{
	Node* p = list.first;
	while (p != NULL && p->info.id != data)
		p = p->next;
	if (p == NULL)//chạy hết ds mà không thấy node
		return false;
	del_node(list, p);
	return true;
}

//xóa toàn bộ sách theo tên tác giả
bool del_book_by_author(doubList& list, string author)
{
	Node* p = list.first;
	if (p == NULL)
		return false;
	int check = -1;
	while (p != NULL)
	{
		if (p->info.tacGia == author)
		{
			Node* t = p;
			p = p->next;
			del_node(list, t);
			check++;
			continue;
		}
		p = p->next;
	}
	if (check != -1)
		return true;
	return false;
}

//sắp xếp dslk theo tên tăng dần
void sortList_Book(doubList& list)
{
	Node* p, * q;
	p = list.first;
	while (p != list.last)
	{
		q = p->next;
		while (q != NULL)
		{
			if (p->info.ten > q->info.ten)
				swap_book(p->info, q->info);
			q = q->next;
		}
		p = p->next;
	}
}

//sắp xếp dslk theo năm giảm dần
void sortList_year(doubList& list)
{
	Node* p, * q;
	p = list.first;
	while (p != list.last)
	{
		q = p->next;
		while (q != NULL)
		{
			if (p->info.nam > q->info.nam)
				swap_book(p->info, q->info);
			q = q->next;
		}
		p = p->next;
	}
}

//sao chép hoặc update thông tin từ dslk đơn qua file
void updateFile(doubList list, string url)
{
	del_all_file(url);
	writeToFile(list, url);
}

//xuất sách theo id
void Find_Book_by_id(doubList list, int id)
{
	Node* p = list.first;

	if (p == NULL)
	{
		cout << "Khong co du lieu!" << endl;
		return;
	}
	else
	{
		while (p != NULL && p->info.id != id)
			p = p->next;
		if (p == NULL)
			cout << "ID khong ton tai\n";
		else
		{
			cout << "danh sach da tim kiem la:\n";
			xuat1sach(p->info);
		}
	}
}

//xuất sách theo tên
void Find_Book_by_name(doubList list, string x)
{
	Node* p = list.first;

	if (p == NULL)
	{
		cout << "Khong co du lieu!" << endl;
		return;
	}
	else
	{
		int dem = 0;
		while (p != NULL)
		{
			if (p->info.ten == x)
			{
				if (dem == 0)
				{
					cout << "Danh sach da tim kiem la:\n";
				}
				dem++;
				xuat1sach(p->info);
				cout << "=====================================\n";
			}
			p = p->next;
		}
		if (dem == 0)
			cout << "Ten ban nhap khong co trong du lieu\n";
	}
}

//in danh mục sách theo tên tác giả
void print_author(doubList list, string author)
{
	Node* p = list.first;
	if (p == NULL)
	{
		cout << "Khong co du lieu!" << endl;
		return;
	}
	else
	{
		int dem = 0;
		while (p != NULL)
		{
			if (p->info.tacGia == author)
			{
				if(dem == 0)
					cout << "Danh muc sach theo tac gia: \n";
				xuat1sach(p->info);
				cout << "=====================================\n";
				dem++;
			}
			p = p->next;
		}
		if (dem == 0)
			cout << "Tac gia khong ton tai\n";
	}
}

//in danh mục sách theo năm xuất bản
void print_publisher(doubList list, string x)
{
	Node* p = list.first;
	if (p == NULL)
	{
		cout << "Khong co du lieu!" << endl;
		return;
	}
	else
	{
		int dem = 0;
		while (p != NULL)
		{
			if (p->info.NXB == x)
			{
				if (dem == 0)
					cout << "Danh muc sach theo nha xuat ban: \n";
				xuat1sach(p->info);
				cout << "=====================================\n";
				dem++;
			}
			p = p->next;
		}
		if (dem == 0)
			cout << "Nha xuat ban khong tim thay\n";
	}
}

//xuất thông tin sách theo thứ tự từ đầu đến cuối
void process_list(doubList list)
{
	Node* p = list.first;
	int dem = 1;

	if (p == NULL)
	{
		cout << "Khong co du lieu!" << endl;
		return;
	}
	while (p != NULL)
	{
		cout << "==========Thong tin sach thu " << dem << ":==========\n";
		xuat1sach(p->info);
		p = p->next;
		dem++;
	}
}