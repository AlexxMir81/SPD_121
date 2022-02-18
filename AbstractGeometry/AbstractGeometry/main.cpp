#define _CRT_SECURE_NO_WORNINGS
#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x00FFFF,

		console_red = 0xCC,
		console_green = 0XAA,
		console_blue = 0x99,
		console_yellow = 0xEE,
		console_default = 0x07
	};

	class Shape
	{
	protected:
		Color color;
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;

	public:
		Color get_color()const
		{
			return color;
		}

		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 800)start_x = 800;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 800)start_y = 800;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width > 50)line_width = 50;
			this->line_width = line_width;
		}

		Shape(unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return this->side;
		}
		void set_side(double side)
		{
			if (side <= 0)side = 10;
			this->side = side;
		}
		Square(double side, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~Square() {}
		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, get_color());

			for (int i = 0; i < side; i++)
			{
				cout << "\t";
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны:" << side << endl;
			Shape::info();
		}
	};

	class Rectangle : public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width <= 0)width = 10;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length <= 0)length = 10;
			this->length = length;
		}
		Rectangle(double width, double length, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}

		double get_area()const
		{
			return width * length;
		}
		double get_perimeter()const
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow(); //получаем окно
			HDC hdc = GetDC(hwnd); //получение контекста устройства
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);

		}
		void info()
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина прямоугольника" << width << endl;
			cout << "длина прямоуголника" << length << endl;
			Shape::info();
			draw();
		}

	};

	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return radius * 2;
		}
		void set_radius(double radius)
		{
			if (radius <= 0 || radius >= 500)radius = 500;
			this->radius = radius;
		}
		Circle(double radius, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_area()const
		{
			return M_PI * pow(radius, 2);
		}
		double get_perimeter()const
		{
			return 2 * M_PI * radius;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << get_radius() << endl;
			cout << "диаметр круга: " << get_diameter() << endl;
			Shape::info();
			draw();
		}
	};

	class Triangle : public Shape
	{
	public:
		Triangle(unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color) {}
		~Triangle() {}

		virtual double get_height()const = 0;
	};
	class EquilateralTriangle : public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		void set_side(double side)
		{
			if (side < 20)side = 20;
			if (side > 500)side = 500;
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const
		{
			return side * cos(30 * M_PI / 180);
		}
		double get_area()const
		{
			return get_height() * side / 4;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT  points[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};

			Polygon(hdc, points, sizeof(points) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Соторона треугольника: " << get_side() << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
			draw();
		}
	};
	class IsoscalesTriange : public Triangle
	{
		double base;
		double base_angle;
	public:
		IsoscalesTriange(double base, double base_angle, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Triangle(start_x, start_y, line_width, color)
		{
			set_base(base);
			set_base_angle(base_angle);
		}
		void set_base(double base)
		{
			if (base < 20)base = 20;
			if (base > 200)base = 200;
			this->base = base;
		}
		void set_base_angle(double angle)
		{
			this->base_angle = angle;
		}
		double get_base()const
		{
			return base;
		}
		double get_side()const
		{
			return get_height() * sin(base_angle / 2 * M_PI / 180);
		}
		double get_base_angle()const
		{
			return base_angle;
		}
		double get_height()const
		{
			return base / 2 * tan(base_angle * M_PI / 180);
		}
		double get_area()const
		{
			return base / 2 * get_height();
		}
		double get_perimeter()const
		{
			return	get_side() * 2 + base;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT points[] =
			{
				{start_x, start_y + get_side()},
				{start_x + base, start_y + get_side()},
				{start_x + base / 2, start_y + get_side() - get_height()}
			};
			Polygon(hdc, points, sizeof(points) / sizeof(POINT));
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание треугольника: " << get_base() << endl;
			cout << "угол треугольника: " << get_base_angle() << endl;
			cout << "Сторона треугольника: " << get_side() << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
			draw();
		}
	};
}
void main()
{
	setlocale(LC_ALL, "");
	Geometry::Square square(15, 100, 100, 5, Geometry::Color::console_red);
	square.info();
	Geometry::Rectangle rect(150, 50, 500, 100, 5, Geometry::Color::blue);
	rect.info();
	Geometry::Circle circle(150, 500, 250, 5, Geometry::Color::yellow);
	circle.info();
	Geometry::EquilateralTriangle eqt(380, 900, 220, 5, Geometry::Color::green);
	eqt.info();
	Geometry::IsoscalesTriange itr(250, 65, 300, 500, 5, Geometry::Color::green);
	itr.info();
}
