//ForwardList
#include<iostream>
using namespace std;

class Element
{
	int Data; //значение элеиента
	Element* pNext; //Адрес следующего элемента
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
	friend class ForwardList;
};
unsigned int Element::count = 0; //инициализация статической переменной

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr; //если голова указывает на 0, то список пуст, т.е. не содержит элементов
	cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other)
	{
		this->Head = other.Head;
		if (other.Head != nullptr)
		{
			Element* Temp_new = Head;
			Element* Temp = other.Head;
			while (Temp->pNext)
			{
				Element* New = Temp;
				Temp_new = New;
				Temp = Temp->pNext;
			}
			Temp_new = Temp->pNext;
		}
		cout << "CopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		clear();
		cout << "LDestructor:\t" << this << endl;
	}
	//         Оператор присваивания
	ForwardList& operator=(const ForwardList& other)
	{
		clear();
		if (other.Head != nullptr)
		{		
			this->Head = other.Head;
			Element* Temp_new = Head;
			Element* Temp = other.Head;
			while (Temp->pNext)
			{
				Element* New = Temp;
				Temp_new = New;
				Temp = Temp->pNext;
			}
			Temp_new = Temp->pNext;
		}
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}
	//          Adding elements
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
	}

	void insert(int index, int Data)
	{
		if (index > Head->count && index!=1)
		{
			cout << "Error: Выход за пределы списка" << endl;
			return;
		}
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
			Element* New = new Element(Data);
			if (Temp == nullptr)
			{
				Head = New;
			}
			else
			{
				New->pNext = Temp->pNext;
				Temp->pNext = New;
			}
	}

	//     Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}

	void pop_back()
	{
		if (Head == nullptr)return;
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	void erase(int index)
	{
		if (index > Head->count||index<=0)
		{
			cout << "Error: Выход за пределы списка" << endl;
			return;
		}
		if (index == 1)
		{
			clear();
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
			Element* Erased = Temp->pNext;
			delete Erased;
			Temp->pNext = Temp->pNext->pNext;
			delete Erased;
	}
	void clear()
	{
		if (Head != nullptr)
		{
			Element* Temp = Head;
			while (Temp->pNext)
			{
				Element* Erased = Temp->pNext;
				Temp->pNext = Temp->pNext->pNext;
				delete Erased;
			}
			Head = Temp->pNext;
			Head->count--;
		}
	}

	//     Methods
	void print()const
	{
		Element* Temp = Head; //Temp - это итератор
		while (Temp)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка: " << Head->count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.clear();
	list.print();
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
	//list.clear();
	//list.print();
	ForwardList list2(list);
	list2.print();
	ForwardList list3;
	list3 = list2;
	list3.print();

}