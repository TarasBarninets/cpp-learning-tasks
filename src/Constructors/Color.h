#pragma once
class Color
{
public:
	Color(unsigned char red, unsigned char green, unsigned char blue);

	void setRed(unsigned char red);
	void setGreen(unsigned char green);
	void setBlue(unsigned char blue);
	
	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();

private:
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;
};