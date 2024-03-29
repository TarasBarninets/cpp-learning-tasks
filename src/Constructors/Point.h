#pragma once

class Point
{
public:
	Point();
	Point(int x, int y);
	Point(const Point& rPoint);
	Point(int x);
	Point& operator= (const Point& rhs);

	friend Point operator+(const Point &point1, const Point &point2); //overloaded operator + via friend function
	friend std::ostream& operator<< (std::ostream& out, const Point& point); //overloaded operator << via friend function
	Point& operator++(); //overloaded prefix operator ++() via class method
	Point& operator--(); //overloaded prefix operator --() via class method
	Point operator++(int); //overloaded postfix operator ++() via class method
	Point operator--(int); //overloaded postfix operator --() via class method

	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

	void forceSetX(int x) const; // test method to demonstrate how mutable works
	void forceSetY(int y) const; // test method to demonstrate how mutable works

private:
	mutable int m_x; // mutable - allow a particular data member of const object to be modified
	mutable int m_y; // mutable - allow a particular data member of const object to be modified
};

Point operator-(const Point& lhs_point, const Point& rhs_point); //overloaded operator - via function