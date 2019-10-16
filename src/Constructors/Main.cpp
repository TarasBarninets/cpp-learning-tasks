#include<iostream>
#include"Point.h"
#include"Rectangle.h"

int main()
{
	Point x; // default constructor
	Point a; // default constructor
	Point b(4,5); // constructor with parameters
	Point c(a); // copy constructor
	Point d = 55; // implicit converstion constructor
	Point e; // default constructor
	e = c; // assignment operator

	Rect original_rect(d,c);
	original_rect.printColor();
	original_rect.setColor(10, 125, 200);

	Rect copy_rect(original_rect);
	original_rect.setColor(1, 1, 1);
	copy_rect.printColor(); // still 10, 125, 200 because copy_rect has own instance of Color

	Rect second_copy_rect(d,e);
	second_copy_rect = copy_rect;
	second_copy_rect.printColor(); 
	copy_rect.setColor(2, 2, 2);
	second_copy_rect.printColor(); // still 10, 125, 200 because second_copy_rect has own instance of Color

	return EXIT_SUCCESS;
}