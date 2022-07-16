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

//hàm kt rỗng
bool isEmpty(doubList& list)
{
	if (list.first == NULL)
		return true;
	return false;
}

//thêm thông tin vào đầu ds
void add_Head(doubList& list,Book data)
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
void add_Tail(doubList& list,Book data)
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

//KT ID của sách xem có trùng hay không,không trùng => true,trùng => false
bool checkID(doubList list, int id)
{
	Node* p = list.first;
	while (p != NULL && p->info.id != id)
		p = p->next;
	if (p == nullptr)
		return true;
	return false;
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
		while (p != NULL)
		{
			ghiFile(p->info, outF);
			p = p->next;
		}
	}
	else
		cout << "Khong mo duoc file\n";
	outF.close();
}

//gán toàn bộ thông tin trong file vào dslk
void readFile(doubList& list,string url)
{
	ifstream inF;//khởi tạo file muốn đọc
	inF.open(url);//mở file

	if (inF.is_open())
	{
		while (!inF.eof())
		{
			Book data;//khởi tạo data

			docFile(data,inF);//cập nhập data
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
	outF.open(url,ios::app);
	if (outF.is_open())
	{
		Book data;
		
		do//KT id
		{
			nhap1Sach(data);
			if (!checkID(list, data.id))
				cout << "ID da ton tai,vui long chon id khac\n";
		} while (!checkID(list, data.id));
		add_Tail(list, data);
		ghiFile(data, outF);
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

//sao chép hoặc update thông tin từ dslk đơn qua file
void updateFile(doubList list, string url)
{
	del_all_file(url);
	writeToFile(list, url);
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
