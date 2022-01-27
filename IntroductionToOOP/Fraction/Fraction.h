#pragma once
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;



/// ///////////////////////////////////////////////////////////////////////////////////////////////
/// ////////////////////////    CLASS DECLARACTION (ÎÁÚßÂËÅÍÈÅ ÊËÀÑÑÀ)               //////////////
/// ///////////////////////////////////////////////////////////////////////////////////////////////

class Fraction;	//Ïðîñòî îáúÿâëåíèå êëàññà
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);

class Fraction	//Îáúÿâëåíèå è îïèñàíèå êëàññà
{
	int integer;		//Öåëàÿ ÷àñòü
	int numerator;		//×èñëèòåëü
	int denominator;	//Çíàìåíàòåëü
public:
	int get_integer()const;
	int get_numerator()const;
	int get_denominator()const;
	void set_integer(int integer);
	void set_numerator(int numerator);
	void set_denominator(int denominator);

	//				Constructors:
	Fraction();
	explicit Fraction(int integer);
	Fraction(double decimal);
	Fraction(int numerator, int denominator);
	Fraction(int integer, int numerator, int denominator);
	Fraction(const Fraction& other);
	~Fraction();

	//				Operators:
	Fraction& operator=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);

	//				Type-cast operators:
	explicit operator int()const;
	explicit operator double()const;

	//				Methods:
	Fraction& reduce();
	Fraction& to_proper();
	Fraction& to_improper();
	Fraction inverted();

	void print()const;
};
istream& operator>>(istream& is, Fraction& obj);
ostream& operator<<(ostream& os, const Fraction& obj);
/// ///////////////////////////////////////////////////////////////////////////////////////////////
/// ////////////////////////    CLASS DECLARACTION END (ÊÎÍÅÖ ÎÁÚßÂËÅÍÈß ÊËÀÑÑÀ)     //////////////
/// ///////////////////////////////////////////////////////////////////////////////////////////////