#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

class Element
	
{

protected:
	int Data;//значение элемента
	Element* pNext; //указатель на следующий элемент
	static int count;
public:
	
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};
int Element::count = 0;
class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return*this;
	}
	bool operator !=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()
	{
		return Temp-> Data;
	}
};
class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		//inetialazer_list - это контейнер 
		//контейнер - это объект, который организует хранение других объектов памяти
		//у любого контейнера в обязательном порядке есть как минимум два метода
		//begin() -возврацает итератор на начало контейнера
		//end - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
		//initializer_list- всякий раз неявно создается когда мы перечисляем значения 
		//в {} через запятую
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;	//здесь просто вызываем CopyAssignment
		cout << "LCopyConstructor:" << this << endl;
	}
	ForwardList(ForwardList&& other) noexcept : Head(other.Head), size(other.size)
	{
		other.Head = nullptr;
		other.size = 0;
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head) pop_front();
		pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}


	ForwardList& operator=(ForwardList&& other) noexcept
	{
		if (this == &other) return *this;
		while (Head) pop_front();
		Head = other.Head;
		size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;
	}

	//				Adinng elements
	void push_front(int Data)
	{
		//1) Создаем новый элемент
		Head = new Element(Data, Head);
		//2) Включает новый элемент 
		//New->pNext = Head;
		//3) Переводи Голову на новый элемент:
		//Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);;
		size++;
	}
	//			Remove elements
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* Remove = Head; //1)запоминаем адрес удаляемого объекта
		Head = Head->pNext;//2) Смещаем голову на следующий элемент(исключаем элемонт из списка
		delete Remove; //3) удаляеи элемент из памяти
		size++;

	}
	void pop_back()
	{
		//1) доходим до предпоследнего элемента списка 
		if (Head == nullptr || Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) удаляем последний элемент из памяти
		delete Temp->pNext;
		//зануляем указатель на предпоследний элемент
		Temp->pNext = nullptr;
		size++;
	}
	void insert(int index, int Data)
	{
		if (index > Head ->count)return;
		//1)доходим до нужного элемента 
		if (index == 0)return push_front(Data);
		
		Element* Temp = Head;
		for(int i = 0; i < index - 1; i++)
		{
			
			Temp = Temp->pNext;
		}
		if (Temp->pNext == nullptr) return;
		//2)Создаем новый элемент:
		//3)Включаем элемент в список
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();
		//1) Доходим до элементаЮ перед удаляемым:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		//2) Запоминаем адрес удаляемого элемента:
		Element* erased = Temp->pNext;
		//3) Исключаем удаляемый элемент из списка:
		Temp->pNext = Temp->pNext->pNext;
		//4) Удаляем элемент из памяти:
		delete erased;

		size--;
	}

	//				Methods:
	void reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}
	void print() const
	{
		cout << "Head:\t" << Head << endl;
		//Element* Temp = Head; //Temp - это итератор
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //Переход на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
		//cout << "Общее количество элементов списка: " << Head->count << endl;
			
	}

};
//#define BASE_CHECK
//#define PERFORMANCE_CHECK
//#define RENGE_BASED_FOR_ARRAY
#define RENGE_BASED_FOR_LIST
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
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
	/*list.pop_front();
	list.print();
	list.pop_back();
	list.print();*/
	int position, value;
	cout << "Введите позицию добавляемого элемента:"; cin>> position;
	cout << "Введите значение добавляемого элемента:"; cin>> value;
	list.insert(position, value);
	list.print();
	cout << "Введите позицию удаляемого элемента:"; cin >> position;
	list.erase(position);
	list.print();
#endif // BASE_CHECK

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите количество элементов"; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);

	}
	cout << "List filled" << endl;
	//list.print();
	cout << "Making copy" << endl;

	ForwardList list2 = list;	//CopyConstructor
	//ForwardList list2;
	//list2 = list;
	//list2.print();
	cout << "Copy DONE" << endl;
#endif // PERFORMANCE_CHECK

#ifdef RENGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	//Range-based for:
	//Range(диапазон) в данном случае понимается как контейнер 
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RENGE_BASED_FOR_ARRAY
#ifdef RENGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RENGE_BASED_FOR_LIST

	
}