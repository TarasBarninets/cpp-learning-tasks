#include <iostream>
#include "../MemoryManagment/Logger.h"

// template function with two input T1, T2 parameters
template<typename T1, typename T2 = float>
bool objectTypeComparison(const T1& objectT1, const T2& objectT2)
{
	std::cout << "This is call of general template function objectTypeComparison(), and result is " << (sizeof(objectT1) > sizeof(objectT2)) << std::endl;
	return (sizeof(objectT1) > sizeof(objectT2));
}

// partial template specilzation, second argument is explicit int
template<typename T1>
bool objectTypeComparison(T1 objectT1, int objectT2)
{
	std::cout << "This is call of partial specialization of template function objectTypeComparison()";
	return true; // just for test
}

// template function
template<typename T>
T add(const T& number1, const T& number2)
{
	static size_t calls_count = 0; // local static variables exist for each instantiation
	std::cout << "Add calls count : " << calls_count << std::endl;
	calls_count++;

	std::cout << "This is call of general template function add() ";
	return (number1 + number2);
}

// template specialization for char type
template<>
char add(const char& number1, const char& number2)
{
	std::cout << "This is call of template specialization function add() for char type";
	return (number1 + number2);
}

// template class
template<class T>
class Point
{
private:
	T m_x;
	T m_y;

public:
	void setX(T x)
	{
		m_x = x;
	}
	void setY(T y)
	{
		m_y = y;
	}
	T getX()
	{
		return m_x;
	}
	T getY()
	{
		return m_y;
	}
	void printPointCoordinates()
	{
		std::cout << "Coordinates of object is " << "(m_x = " << m_x << ", m_y = " << m_y << ");" << std::endl;
	}
};


// template class with NON-TYPE(VALUE) templates argument
template<class ArrayType, size_t size>
class Array
{
public:
	Array()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

private:
	ArrayType array[size];
};

int main()
{
	int i = add(4, 9); // template instantiation - generate function for int type - int add(const int&, const int&)
	std::cout << "Sum of integer numbers = " << i << std::endl;

	float f = add(4.25f, 4.251f);
	std::cout << "Sum of float numbers = " << f << std::endl;

	double d = add(4.5, 3.1);
	std::cout << "Sum of double numbers = " << d << std::endl;

	double d2 = add(41.25, 78.251);
	std::cout << "Sum of double 2nd numbers = " << d2 << std::endl;

	char c = add('a', 'b'); 
	std::cout << "Sum of char numbers = " << static_cast<unsigned int>(c) << std::endl;

	//---------------------------------------------------------
	Point<int> integer_point;
	integer_point.setX(1);
	integer_point.setY(2);
	integer_point.printPointCoordinates();

	Point<double> double_point;
	double_point.setX(12.5);
	double_point.setY(18.7);
	double_point.printPointCoordinates();

	objectTypeComparison(integer_point, double_point);
	objectTypeComparison(integer_point, i);

	Array<Logger, 10> customArray; // template instantiation
	return 0;
}