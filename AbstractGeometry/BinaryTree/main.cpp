#include<iostream>
using namespace std;

#define tab "\t"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root; //Корень дерева, указатель на корневой элемент
public:
	Element* getRoot()const
	{
		return this->Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il):Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			insert(*it);
	}
	Tree(const Tree& other)
	{
		*this = other;
	}

	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}

	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}

	int sum()const
	{
		return sum(Root);
	}
	 
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}

	void print()const
	{
		print(Root);
		cout << endl;
	}
	void clear()
	{
		return clear(Root);
	}

	Tree& operator=(const Tree& other)
	{
		if (this->Root == other.Root) return *this;
		clear();
		this->Root = new Element(other.Root->Data);
		copy(other.Root->pLeft);
		copy(other.Root->pRight);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}


private:

	void copy(Element* Root)
	{
		if (Root == nullptr)return;
		copy(Root->pLeft);
		insert(Root->Data);
		copy(Root->pRight);
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	int minValue(Element* Root)const
	{
	/*	if (Root == nullptr)return int();
		if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		//return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}
	int maxValue(Element* Root)const
	{
		//if (Root == nullptr)return int();
		//if (Root->pRight == nullptr)return Root->Data;
		//else return maxValue(Root->pRight);
		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return !Root->pRight ? Root->Data : maxValue(Root->pRight);
	}

	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/	
		return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}

	int sum(Element* Root)const
	{
	/*	if (Root == nullptr)return 0;
		else return sum(Root->pLeft) + sum(Root->pRight) + Root->Data;*/
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
public:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Среднее арифметическое: " << tree.avg() << endl;
	
	UniqueTree uniquetree;
	for (int i = 0; i < n; i++)
	{
		uniquetree.insert(rand() % 100);
	}
	uniquetree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << uniquetree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << uniquetree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << uniquetree.count() << endl;
	Tree tree3 = { 50, 25, 75, 16, 35 };
	tree3.print();

	tree3 = tree;
	tree3.print();
	Tree tree4 = tree;
	tree4.print();
}