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
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public: 
		ConstBaseIterator(Element* Temp =nullptr):Temp(Temp){}
		~ConstBaseIterator(){}
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
	};

public:
	class ConstIterator :public ConstBaseIterator
	{

	
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;

		}
		~ConstIterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return*this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		
		// Comperison operators:
		bool operator==(const ConstIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		bool operator !=(const ConstIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		//		Dereference operators:

		const int& operator*()const
		{
			return Temp->Data;
		}
		
	};
public:
	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator (Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}
		//		Incremento/Decremento:
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		//		Comparison operators
		bool operator==(const ConstReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
		
	};
	ConstIterator begin()const
	{
		return Head;
	}
	 ConstIterator end()const
	{
		return nullptr;
	}
	ConstReverseIterator rbegin()
	{
		return Tail;
	}
	ConstReverseIterator rend()
	{
		return nullptr;
	}

	//		Constructor
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConctructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
		
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		while (Head)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//		Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return* this;
		while (Head) pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CoppyAssigment:\t" << this << endl;
		return *this;

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
		cout << "Количество элементов списка:" << size << endl;
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
		cout << "Количество элементов списка:" << size << endl;
		cout << delimiter << endl;
	}
};
List operator+(const List& left, const List& reght)
{
	List buffer = left; //CopyConstructor
	for (List::ConstIterator it = reght.begin(); it != reght.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}
//#define BASE_CHECK
#define ITERATOR_CHECK 
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите количесво элементов:"; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.revers_print();
	for (int i = 0; i < 100; i++) list.pop_back();
	int position, value;
	cout << "Введите позицию добавляемого элемента:"; cin >> position;
	cout << "Введите значение добавляемого элемента:"; cin >> value;
	list.insert(position, value);
	list.print();
	cout << "Введите позицию удаляемого элемента:"; cin >> position;
	list.erase(position);
	list.print();
#endif // BASE_CHECK
#ifdef ITERATOR_CHECK 
	List list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)
		cout << i << tab;
	cout << endl;
	for (List::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATOR_CHECK 
	List list1 = { 3,5,8,31,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	//list3.print();
	//list3.revers_print();
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
}