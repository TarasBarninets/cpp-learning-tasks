#pragma once

class Point
{
public:
	Point();
	Point(int x, int y);
	Point(const Point& rPoint);
	Point(int x);
	Point& operator= (const Point& rhs);

	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

private:
	int m_x, m_y;
};