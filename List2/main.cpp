#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

class List
{
	class  Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			: Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	} *Head, *Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConctructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		while (Head)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);

		}

		else
		{/*
			Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;*/
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;*/
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	//			Removing elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
			size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
	void insert(int index, int Data)
	{
		Element* Temp;
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pNext;
			}
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}
	void erase(int index)
	{
		Element* Temp;
		if (index > size)return;
		if (index == 0)return pop_front();
		if (index == size) return pop_back();
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
			{
				Temp = Temp->pNext;
			}
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size-index-1; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}
	void print()const
	{
		cout << delimiter << endl;
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout
			<< Temp->pPrev << tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext << endl;
		cout << "Taid:\t" << Tail << endl;
		cout << "���������� ��������� ������:" << size << endl;
		cout << delimiter << endl;
	}
	void revers_print()const
	{
		cout << delimiter << endl;
		cout << "Tail:\t" << Tail << endl;

		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout
			<< Temp->pPrev<< tab
			<< Temp << tab
			<< Temp->Data << tab
			<< Temp->pNext<< endl;

		cout << "Head:\t" << Head << endl;
		cout << "���������� ��������� ������:" << size << endl;
		cout << delimiter << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ��������� ���������:"; cin >> n;
	List list;
	for (int i = 0 ;i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.revers_print();
	for (int i = 0; i < 100; i++) list.pop_back();
	int position, value;
	cout << "������� ������� ������������ ��������:"; cin >> position;
	cout << "������� �������� ������������ ��������:"; cin >> value;
	list.insert(position, value);
	list.print();
	cout << "������� ������� ���������� ��������:"; cin >> position;
	list.erase(position);
	list.print();
}