//ForwardList
#include<iostream>
using namespace std;

#define tab "\t"

class ForwardList;

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static unsigned int count;
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
	friend class Iterator;
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

unsigned int Element::count = 0;	//Инициализация статической переменной

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
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
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}

}; 
class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Element* getHead()const { return Head; }
	unsigned int get_size()const { return size; }
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
		Head = nullptr; //если голова указывает на 0, то список пуст, т.е. не содержит элементов
		size = 0;
	cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other): ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp=Temp->pNext)
		{
			push_back(Temp->Data);
		}*/
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other)
	{
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
	//	clear();
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//         Оператор присваивания
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for(Element* Temp =other.Head; Temp; Temp=Temp->pNext)
		{
			push_back(Temp->Data);
		}
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}

	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssigment:\t" << this << endl;
		return *this;
	}
	//          Adding elements
	void push_front(int Data)
	{
	/*	Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int index, int Data)
	{
		if (index > Head->count)
		{
			cout << "Error: Выход за пределы списка" << endl;
			return;
		}
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
			Temp->pNext = new Element(Data, Temp->pNext);
			size++;
	}

	//     Removing elements:
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}

	void pop_back()
	{
		if (Head)return;
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{

		if (index == 0)return pop_front();
		if (index == Head->count - 1)return pop_back();
		if (index >= Head->count)
		{
			cout << "Error: Выход за пределы списка" << endl;
			return;
		}
		//1) доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//2)запоминаем адрес удаляемого элемента
		Element* Erased = Temp->pNext;
		//3)Исключаем удаляемый элемент из списка
		Temp->pNext = Temp->pNext->pNext;
		//4) удаляем элемент из памяти
		delete Erased;
		size--;
	}

	void reverse()
	{
		ForwardList reverse_list;
		while (Head)
		{
			reverse_list.push_front(Head->Data);
			pop_front();
		}
		Head = reverse_list.Head;
		reverse_list.Head = nullptr;
	}

	void unique()
	{
		for (Element* Temp = Head; Temp->pNext; Temp = Temp->pNext)
		{
			for (Element* Temp2 = Temp; Temp2->pNext->pNext; Temp2 = Temp2->pNext)
			{
				//if (Temp == Temp2->pNext)continue;
				if (Temp->Data == Temp2->pNext->Data)
				{
						Element* Erased = Temp2->pNext;						
						Temp2->pNext = Temp2->pNext->pNext;
						delete Erased;
						size--;
					//Temp2 = Temp;
				}
			}
		}
	}

	//     Methods
	void print()const
	{
		/*Element* Temp = Head;//Temp - это итератор
		while (Temp)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			//for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Количество элементов списка:" << size << endl;
		cout << "Общее количество элементов: " << Head->count << endl;
	}
};
//#define CLASSWORK
//#define REVERSE_CHECK
#define UNIQUE_CHECK
//#define RANGE_BASE_FOR_ARRAY
void main()
{
	setlocale(LC_ALL, "");
#ifdef CLASSWORK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
//	list.clear();
//	list.print();
	list.push_back(123);
	list.print();

	list.pop_front();
	list.print();

	list.pop_back();
	list.print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	ForwardList list5 = { 3,4,5,8,14 };
	list5.print();
	//ForwardList list2(list);
	//list2.print();
	//ForwardList list3;
	//list3 = list2;
	//list3.print();
#endif // CLASSWORK



#ifdef REVERSE_CHECK
	ForwardList list = { 3,5,8,13,21 };
	/*for (Iterator it = list.getHead(); it != nullptr; ++it)
	{
		cout << *it << "\t";
	}
	cout << endl;*/
	list.print();
	list.reverse();
	list.print();
#endif // REVERSE_CHECK

#ifdef UNIQUE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 10);
	}
	list.print();
	list.unique();
	list.print();
#endif // UNIQUE_CHECK

#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//range-based for:
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASE_FOR_ARRAY

	//ForwardList list = { 3,5,8,13,21 };
	//for (int i : list)
	//{
	//	cout << i << tab;
	//}
	//cout << endl;
}
