#include <iostream>
using namespace std;
#define tab "\t"
class Element
	
{
protected:
	int Data;//значение элемента
	Element* pNext; //указатель на следующий элемент
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//				Adinng elements
	void push_front(int Data)
	{
		//1) Создаем новый элемент
		Element* New = new Element(Data);
		//2) Включает новый элемент 
		New->pNext = Head;
		//3) Переводи Голову на новый элемент:
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Element* New = new Element(Data);
		Temp->pNext = New;
	}
	//				Methods:
	void print() const
	{
		
		cout << "Head:\t" << Head << endl;
		Element* Temp = Head; //Temp - это итератор
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //Переход на следующий элемент
		}
	}

};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите количество элементов"; cin >> n;
		ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);

	}
	list.print();
	//list.push_back(123);
	//list.print();
}