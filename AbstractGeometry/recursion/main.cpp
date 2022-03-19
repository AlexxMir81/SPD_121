#include<iostream>
using namespace std;

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Âû â ïîäâàëå" << endl;
		return;
	}
	cout << "Âû íà " << floor << " ýòàæå" << endl;
	elevator(floor - 1);
	cout << "Âû íà " << floor << " ýòàæå" << endl;
}
long long int factorial(int n)
{
	//if (n == 0)return 1;
	return (n==0)? 1: n * factorial(n - 1);
}

double power(double a, int n)
{
	if (n == 0)return 1;
	else if (n < 0) return power(1/a, -n);
	else return (a * power(a, n - 1));
	//return n == 0 ? 1 : n > 0 ? a * power(a, n - 1) : power(1 / a, -n);
}

//#define ELEVATOR
//#define FACTIORIAL
void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello";
	//main();
#ifdef ELEVATOR
	int floor;
	cout << "Этаж : "; cin >> floor;
	elevator(floor);
#endif // DEBELEVATORUG
#ifdef FACTORIAL
	int n;
	cout << "Введите число:" << endl; cin >> n;
	cout << "Факториал числа 20: " << factorial(n);
#endif // FACTORIAL
	int a;
	int n;
	cout << "Введите основание степени:"; cin >> a;
	cout << "Веедите показатель степени:"; cin >> n;
	cout << power(a, n);

}


