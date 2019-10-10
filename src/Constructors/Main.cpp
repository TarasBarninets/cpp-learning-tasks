#include<iostream>

class Point
{
public:

	Point() : m_x(0), m_y(0) // default constructor - without parameters () or with default parameters (x=0, y=0)
	{
		std::cout << "Called default constructor." << std::endl;
	}

	Point(int x, int y) : m_x(x), m_y(x) // constructor with paramethers
	{
		std::cout << "Called constructor with paramethers." << std::endl;
	}

	Point(const Point& rPoint) : m_x(rPoint.getX()), m_y(rPoint.getY()) // copy constructor
	{
		std::cout << "Called copy constructor." << std::endl;
	}

	Point(int x) : m_x(x), m_y(0) // converting constructor in C++03 - constructor without explicit and with only single parameter
								  // in C++11 - without explicit
	{
		std::cout << "Called convertion constructor." << std::endl;
	}

	Point& operator= (const Point& rhs)
	{
		// this points on left side of assignment operator
		// rhs points on right of assignment operator
		m_x = rhs.getX();
		m_y = rhs.getY();

		std::cout << "Called assignment operator." << std::endl;
		return *this;
	}

	int getX() const
	{
		return m_x;
	}

	int getY() const
	{
		return m_y;
	}

	void setX(int x)
	{
		m_x = x;
	}

	void setY(int y)
	{
		m_y = y;
	}

private:
	int m_x, m_y;
};

class Rect
{
public:
	// Consgtructor with parameters
	Rect(const Point& left_bottom_corner, const Point& right_top_corner) : m_left_bottom_corner(left_bottom_corner), m_right_top_corner(right_top_corner)
	{
		std::cout << "Called parametrized constructor of Rect class" << std::endl;

		// called assignment operators for Points members of Rect class
		// m_left_bottom_corner = left_bottom_corner;
		// m_left_bottom_corner = left_bottom_corner;
		// m_right_top_corner = right_top_corner;
	}

private:
	Point m_left_bottom_corner;
	Point m_right_top_corner;
};

int main()
{
	Point x; // default constructor
	Point a; // default constructor
	Point b(4,5); // constructor with parameters
	Point c(a); // copy constructor
	Point d = 55; // implicit converstion constructor
	Point e; // default constructor
	e = c; // assignment operator

	Rect my_rect(b, d);
	
	return EXIT_SUCCESS;
}