#include "Renault.h"
#include <iostream>

Renault::Renault(unsigned char fuel_level) : Car(fuel_level)
{
	std::cout << "Renault car is constructed" << std::endl;
}

Renault::~Renault()
{
	std::cout << "Renault car is destroyed" << std::endl;
}

bool Renault::start_engine()
{
	if (m_fuel_level)
		std::cout << "Renault engine started." << std::endl;
	else
		std::cout << "Renault fuel level is empty. Can not start engine." << std::endl;

	return m_fuel_level;
}

bool Renault::stop_engine()
{
	if (m_parking_break)
		std::cout << "Renault engine stopped." << std::endl;
	else
		std::cout << "Renault engine can not be stopped. Please turn on parking break." << std::endl;

	return m_parking_break;
}

void Renault::set_gear(unsigned char gear)
{
	m_gear_status = gear;
	std::cout << "Renault current gear is " << (unsigned short) m_gear_status << std::endl;
}

void Renault::set_parking_break(bool value)
{
	m_parking_break = value;
	std::cout << "Renault parking break is changed to " << m_parking_break << std::endl;
}

void Renault::accelerate()
{
	if (m_fuel_level > 0)
	{
		--m_fuel_level;
		std::cout << "Renault accelerate is press. Fuel level is " << (unsigned short) m_fuel_level << std::endl;
	}
	else
	{
		std::cout << "Renault fuel tank level is empty. Can't accelerate." << std::endl;
	}
}

void Renault::put_break()
{
	std::cout << "Renault pressed breaking." << std::endl;
}

void Renault::add_fuel(unsigned char value)
{
	m_fuel_level += value;
	std::cout << "Renault fuel added." << std::endl;
}
