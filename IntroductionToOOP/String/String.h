#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

int StringLength(const char* str);

/// ///////////////////////////////////////////////////////////////////////////////////////////////
/// ////////////////////////    CLASS DECLARACTION (���������� ������)               //////////////
/// ///////////////////////////////////////////////////////////////////////////////////////////////
class String;
String operator+(const String& left, const String& right);

class String
{
	int size;	//������ ������
	char* str;	//��������� �� ������ � ������������ ������
public:
	int get_size()const;
	const char* get_str()const;
	char* get_str();

	//     Constructors:
	explicit String(int size = 80);
	String(const char* str);
	String(const String& other);
	~String();
	//					Operators:
	String& operator=(const String& other);

	String& operator+=(const String& other);
	const char& operator[](int i)const;
	char& operator[](int i);

	//					Methods:
	void print()const;
};

/// ///////////////////////////////////////////////////////////////////////////////////////////////
/// ////////////////////////    CLASS DECLARACTION END (����� ���������� ������)     //////////////
/// ///////////////////////////////////////////////////////////////////////////////////////////////
