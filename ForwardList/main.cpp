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
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* Remove = Head;
		Head = Head->pNext;
		delete Remove;


	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void insert(int index, int Data)
	{
		if (index == 0)return push_front(Data);
		Element* Temp = Head;
		for(int i = 0; i < index - 1; i++)
		{
			
			Temp = Temp->pNext;
		}
		if (Temp->pNext == nullptr) return;
		Temp->pNext = new Element(Data, Temp->pNext);
	}
	void erase(int index)
	{
		if (index == 0)return pop_front();
		Element* Temp = Head;
		for(int i = 0; i < index - 1; i++)
		{
			
			Temp = Temp->pNext;
		}
	
		Element* Remove = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Remove;
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
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	int position, value;
	cout << "Введите позицию добавляемого элемента:"; cin>> position;
	cout << "Введите значение добавляемого элемента:"; cin>> value;
	list.insert(position, value);
	list.print();
	cout << "Введите позицию удаляемого элемента:"; cin >> position;
	list.erase(position);
	list.print();
}