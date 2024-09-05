#pragma once

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
	} *Head, * Tail;
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
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
			return ConstBaseIterator::Temp->Data;
		}

	};
public:
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
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
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}

		~Iterator() {}
		T& operator*();
	};
	class  ReverseIterator : public ConstReverseIterator

	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
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