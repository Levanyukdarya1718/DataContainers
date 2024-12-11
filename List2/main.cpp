#include"List.h"
#include "List.cpp"

//#define BASE_CHECK
//#define ITERATOR_CHECK 
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "¬ведите количесво элементов:"; cin >> n;
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
	cout << "¬ведите позицию добавл€емого элемента:"; cin >> position;
	cout << "¬ведите значение добавл€емого элемента:"; cin >> value;
	list.insert(position, value);
	list.print();
	cout << "¬ведите позицию удал€емого элемента:"; cin >> position;
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
