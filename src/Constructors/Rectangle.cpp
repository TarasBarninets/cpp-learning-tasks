#include<iostream>
#include"Rectangle.h"
#include "Color.h"

Rect::Rect(const Point& left_bottom_corner, const Point& right_top_corner) 
	: m_left_bottom_corner(left_bottom_corner), m_right_top_corner(right_top_corner)
{
	std::cout << "Called parametrized constructor of Rect class" << std::endl;
	m_color = new Color(0,0,0);
}

Rect::Rect(const Rect& rectObject) : m_left_bottom_corner(rectObject.m_left_bottom_corner), 
									 m_right_top_corner(rectObject.m_right_top_corner),
									 // m_color(rectObject.m_color) // this code makes shallow copy
									 m_color(new Color(*rectObject.m_color)) // make deep copy that call copy constructor of Color
{
	std::cout << "Called copy constructor Rect class" << std::endl;
}

Rect::~Rect()
{
	delete m_color;
}

Rect& Rect::operator=(const Rect& rectObject)
{
	std::cout << "Called assign operator Rect class" << std::endl;

	m_left_bottom_corner = rectObject.m_left_bottom_corner;
	m_right_top_corner = rectObject.m_right_top_corner;

	if (this == &rectObject)
		return *this;

	// m_color = rectObject.m_color; this code make shallow copy because copies pointers instead of calling assign operator of Color class
	*m_color = *rectObject.m_color; // make deep copy that calls assign operator of Color 

	return *this;
}

void Rect::printColor()
{
	std::cout << "RGB(" << (unsigned short)m_color->getRed() << ";"
		<< (unsigned short)m_color->getGreen() << ";"
		<< (unsigned short)m_color->getBlue() << ")" << std::endl;
}

void Rect::setColor(unsigned char red, unsigned char green, unsigned char blue)
{
	m_color->setRed(red);
	m_color->setGreen(green);
	m_color->setBlue(blue);
}
