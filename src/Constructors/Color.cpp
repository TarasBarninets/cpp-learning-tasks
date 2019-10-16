#include "Color.h"
#include <iostream>

Color::Color(unsigned char red, unsigned char green, unsigned char blue) : m_red(red), m_green(green), m_blue(blue)
{
}

void Color::setRed(unsigned char red)
{
	m_red = red;
}

void Color::setGreen(unsigned char green)
{
	m_green = green;
}

void Color::setBlue(unsigned char blue)
{
	m_blue = blue;
}

unsigned char Color::getRed()
{
	return m_red;
}

unsigned char Color::getGreen()
{
	return m_green;
}

unsigned char Color::getBlue()
{
	return m_blue;
}