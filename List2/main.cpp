#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"
template<typename T>
class List
{
	class  Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			: Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

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
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};

public:
	class ConstIterator :public ConstBaseIterator
	{

	
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
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
			return ConstBaseIterator:: Temp->Data;
		}
		
	};
public:
	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) ;
		~ConstReverseIterator();
		//		Incremento/Decremento:
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator operator--();
		ConstReverseIterator operator--(int);
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
			return ConstBaseIterator::Temp->Data;
		}
		
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp){}

		~Iterator() {}
		T& operator*();
	};
	class  ReverseIterator : public ConstReverseIterator
	
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp){}
		~ReverseIterator() {}
		T& operator*();
	};
	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();

	//		Constructor
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();
	//		Operators:
	List<T>& operator=(const List<T>& other);

	void push_front(T Data);
	void push_back(T Data);
	//			Removing elements
	void pop_front();
	void pop_back();
	void insert(int index, T Data);
	void erase(int index);
	void print()const;
	void revers_print()const;
};
/////////////////////////////////////////////////////////////////////////
////////////				CONSR-ITERATORS			/////////////////////////

template <typename T> bool List<T> ::ConstBaseIterator:: operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template <typename T> bool List<T> ::ConstBaseIterator:: operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template <typename T> const T& List<T>  ::ConstBaseIterator:: operator*()const
{
	return Temp->Data;
}
//							Const Iterator:
	template <typename T> List<T> ::ConstIterator::ConstIterator(Element* Temp ) :ConstBaseIterator(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

	}
	template <typename T> List<T> ::ConstIterator::	~ConstIterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

	}
	template <typename T> typename List<T> ::ConstIterator& List<T>::ConstIterator:: operator++()
	{
		ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
		return*this;
	}
	template <typename T> typename List<T> ::ConstIterator List<T>::ConstIterator:: operator++(int)
	{
		ConstIterator old = *this;
		ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
		return old;
	}
	template <typename T>typename List<T> ::ConstIterator& List<T>::ConstIterator :: operator--()
	{
		ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
		return *this;
	}
	template <typename T>typename List<T> ::ConstIterator List<T>::ConstIterator :: operator--(int)
	{
		ConstIterator old = *this;
		ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
		return old;
	}

	

//							Const Reverse Iterator
template<typename T> List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp ) :ConstBaseIterator(Temp)
	{
#ifdef DEBUG
		cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

	}
template<typename T> List<T>::ConstReverseIterator::~ConstReverseIterator()
	{
#ifdef DEBUG
		cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

	}
	//		Incremento/Decremento:
	template<typename T> typename List<T>::ConstReverseIterator& List<T>:: ConstReverseIterator:: operator++()
	{
		ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
		return *this;
	}
	template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator:: operator++(int)
	{
		ConstReverseIterator old = *this;
		ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
		return old;
	}
	template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator ::operator--()
	{
		ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
		return *this;
	}
	template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator:: operator--(int)
	{
		ConstReverseIterator old = *this;
		ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
		return old;
	}
////////////				CONSR-ITERATORS			/////////////////////////
/////////////////////////////////////////////////////////////////////////

///---------------------------------------------------------------------///
/////////////////////////////////////////////////////////////////////////
////////////				ITERATORS			/////////////////////////
template<typename T> T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
template<typename T> T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
////////////				ITERATORS			/////////////////////////
/////////////////////////////////////////////////////////////////////////

/// --------------------------------------------------------------------///

/////////////////////////////////////////////////////////////////////////
////////////				List members				////////////////
template<typename T>typename List<T>::ConstIterator List<T> ::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T> ::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T> ::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T> ::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T> ::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T> ::rend()const
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T> ::rbegin()
{
	return Tail;
}
template<typename T> typename List<T>::ReverseIterator List<T> ::rend()
{
	return nullptr;
}

//		Constructor
template <typename T> List<T> ::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConctructor:\t" << this << endl;
}
template<typename T> List <T>::List(const std::initializer_list<T>& il) :List()
{

	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		push_back(*it);
	}

}
template<typename T> List<T> ::List(const List<T>& other) :List()
{
	*this = other;
	cout << "CopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	while (Head)pop_front();
	while (Head)pop_back();
	cout << "LDestructor:\t" << this << endl;
}
//		Operators:
template<typename T>List<T> & List<T>:: operator=(const List<T>& other)
{
	if (this == &other)return*this;
	while (Head) pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "CoppyAssigment:\t" << this << endl;
	return *this;

}
template<typename T>void List<T>::push_front(T Data)
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
template<typename T>void List<T>::push_back(T Data)
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
template<typename T>void List<T>:: pop_front()
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
template<typename T>void List<T>:: pop_back()
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
template<typename T>void List<T>:: insert(int index, T Data)
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
template<typename T>void List<T>::erase(int index)
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
		for (int i = 0; i < size - index - 1; i++)
		{
			Temp = Temp->pPrev;
		}
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}
template<typename T>void List<T>::print()const
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
template<typename T> void List<T>::revers_print()const
{
	cout << delimiter << endl;
	cout << "Tail:\t" << Tail << endl;

	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout
		<< Temp->pPrev << tab
		<< Temp << tab
		<< Temp->Data << tab
		<< Temp->pNext << endl;

	cout << "Head:\t" << Head << endl;
	cout << "Количество элементов списка:" << size << endl;
	cout << delimiter << endl;
}
////////////				List members				/////////////////
//////////////////////////////////////////////////////////////////////

template<typename T> List<T> operator+(const List<T>& left, const List<T>& reght)
{
	List<T> buffer = left; //CopyConstructor
	for (typename List<T>::ConstIterator it = reght.begin(); it != reght.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}
template<typename T>void Grow(List<T>& list)
{
	for (typename List<T>::Iterator it = list.begin(); it != list.end(); ++it)
		*it *= 10;
}

//#define BASE_CHECK
//#define ITERATOR_CHECK 
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
	List<int> list = { 3,5,8,13,21 };
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
	List<int> list1 = { 3,5,8,31,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;
	//list3.print();
	//list3.revers_print();
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;

	List<double> d_list1 = { 5.5,7.1,19.6,3.89 };
	for (double i: d_list1)cout << i << tab; cout << endl;
	
	List<std::string> s_list1 = { "в", "лесу","родилась", "елочка"};
	for (std::string i : s_list1)cout << i << tab; cout << endl;
	
}
