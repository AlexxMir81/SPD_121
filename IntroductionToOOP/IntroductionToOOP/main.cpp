#include<iostream>
using namespace std;

#define tab "\t"

class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;//Encapsulation DONE
		//this - ��� ��������� �� ������, ��� �������� ���������� �����
		//������� ������ ���������� ������ ��� �������, ��� �������� �� ����������
		//�� ������ ����� ������ ����� ����� �������.
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//					Constructors:
	/*Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}*/
	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		cout << "X = " << x << "\tY = " << y << endl;
	}
};

//#define STRUCT_POINT

void main()
{
	setlocale(LC_ALL, "");
#ifdef STRUCT_POINT
	//type name;
	int a;	//��������� ���������� 'a' ���� 'int'
	Point A;//��������� ���������� 'A' ���� 'Point'
			//������� ������ (���������) ��������� 'Point'
	A.x = 2;
	A.y = 3;
	cout << A.x << tab << A.y << endl;

	Point* pA = &A;	//������� ��������� �� ������ ����� ���������
	cout << pA->x << tab << pA->y << endl;
#endif // STRUCT_POINT

	Point A;	//DefaultConstructor
	double x, y;
	//cout << "������� ���������� �����: "; cin >> x >> y;
	//A.set_x(x);
	//A.set_y(y);
	//cout << A.get_x() << tab << A.get_y() << endl;
	A.print();

	Point B(22, 33);
	B.print();

	Point C = 5;	//Single-argument constructor
	C.print();

	Point D(0, 123);
	D.print();
}

/*
.  - �������� ������� ������� (Point operator)
-> - �������� ���������� ������� (Arrow operator)
*/
/*
1. ������������ (Encapsulation);
������������ �������:
private:	�������� ������ ������ ������.
public:
protected:
get/set-������

get (�����, ��������)	 - ��������� ������ � ���������� ������ �� ������,
						   �.�., ���������� �������� �������� ��� ��� ����
						   ����������-�����.
set (������, ����������) - ��������� ������ � ���������� ������ �� ������,
						   �.�., ��������� ������ �������� ��� ��� ����
						   ����������-�����.



2. ������������ (Inheritance);
3. �����������  (Polymorphism);
*/

/*
				SPECIAL MEMBERS
Constructor - ��� �����, ������� ������� ������. � ������, �������� ������ ��� ������,
			  � �������������� ��� ���������� �����.
~Destructor	-
operator=
*/