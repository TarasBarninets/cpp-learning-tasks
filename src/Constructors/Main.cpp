#include<iostream>
#include"Point.h"
#include"Rectangle.h"

using namespace std;

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
	std::cout << std::endl;

	Point q(20, 6);
	Point w(10, 4);
	Point t = q + w;
	std::cout << q << " + " << w << " = " << t << std::endl; 
	Point m = q - w;
	std::cout << q << " - " << w << " = " << m << std::endl;
	std::cout << "Prefix ++" << q << " = ";
	std::cout << ++q << std::endl;
	std::cout << "Prefix --" << w << " = ";
	std::cout << --w << std::endl;
	std::cout << "Postfix ++" << q << " = ";
	std::cout << q++ << std::endl;
	std::cout << "Postfix --" << w << " = ";
	std::cout << w-- << std::endl;

	return EXIT_SUCCESS;
}