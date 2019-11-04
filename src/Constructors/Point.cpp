#include <iostream>
#include "Point.h"

Point::Point() : m_x(0), m_y(0) // default constructor - without parameters () or with default parameters (x=0, y=0)
{
	std::cout << "Called default constructor Point." << std::endl;
}

Point::Point(int x, int y) : m_x(x), m_y(y) // constructor with paramethers
{
	std::cout << "Called constructor with paramethers Point." << std::endl;
}

Point::Point(const Point& rPoint) : m_x(rPoint.getX()), m_y(rPoint.getY()) // copy constructor
{
	std::cout << "Called copy constructor Point." << std::endl;
}

Point::Point(int x) : m_x(x), m_y(0) // converting constructor in C++03 - constructor without explicit and with only single parameter
								  // in C++11 - without explicit
{
	std::cout << "Called convertion constructor Point." << std::endl;
}

Point& Point:: operator= (const Point& rhs)
{
	// this points on left side of assignment operator
	// rhs points on right of assignment operator
	m_x = rhs.getX();
	m_y = rhs.getY();

	std::cout << "Called assignment operator Point." << std::endl;
	return *this;
}

int Point::getX() const
{
	return m_x;
}

int Point::getY() const
{
	return m_y;
}

void Point::setX(int x)
{
	m_x = x;
}

void Point::setY(int y)
{
	m_y = y;
}

Point operator+(const Point &point1, const Point &point2)
{
	return Point(point1.m_x + point2.m_x, point1.m_y + point2.m_y);
}

std::ostream& operator<< (std::ostream& out, const Point& point)
{
	out << "Point(" << point.m_x << ", " << point.m_y << ")";
	return out;
}

Point operator-(const Point& lhs_point, const Point& rhs_point)
{
	return Point(lhs_point.getX() - rhs_point.getX(), lhs_point.getY() - rhs_point.getY());
}

Point& Point::operator++()
{
	++m_x;
	++m_y;
	return *this;
}

Point& Point::operator--()
{
	--m_x;
	--m_y;
	return *this;
}

Point Point::operator++(int)
{
	Point temp(*this);
	++(*this);
	return temp;
}

Point Point::operator--(int)
{
	Point temp(*this);
	--(*this);
	return temp;
}

