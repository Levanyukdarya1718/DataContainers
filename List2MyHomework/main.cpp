#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
protected:
	int Data;
	Element* pNext;
	Element* pPrev;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "Destructor:\t" << this << endl;
	}
	friend class List;
};

class List
{
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;
		}
		size++;
	}

	void print()const
	{
		for (Element* Temp = Head; Temp; Temp=Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка:" << size << endl;
	}

};
void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите количество элементов"; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
}