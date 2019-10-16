#pragma once
#include "Point.h"

class Color;

class Rect
{
public:
	Rect(const Point& left_bottom_corner, const Point& right_top_corner);
	Rect(const Rect& rectObject);
	~Rect();
	Rect& operator=(const Rect& rectObject);

	void printColor();
	void setColor(unsigned char red, unsigned char green, unsigned char blue);

private:
	Point m_left_bottom_corner;
	Point m_right_top_corner;
	Color* m_color;
};