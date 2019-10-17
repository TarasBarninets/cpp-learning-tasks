#include "Citroen.h"
#include "CarConfig.h"
#include <iostream>

// add variable with static storage this means that variable is available only within this file
static const unsigned short CITROEN_POLUTION_RATE = 145;

Citroen::Citroen(unsigned char fuel_level) : Car(fuel_level)
{
	std::cout << "Citroen car is constructed" << std::endl;
}

Citroen::~Citroen()
{
	std::cout << "Citroen car is destroyed" << std::endl;
}

bool Citroen::start_engine()
{
	if (m_fuel_level)
		std::cout << "Citroen engine started." << std::endl;
	else
		std::cout << "Citroen fuel level is empty. Can not start engine." << std::endl;

	return m_fuel_level;
}

bool Citroen::stop_engine()
{
	if (m_parking_break)
		std::cout << "Citroen engine stopped." << std::endl;
	else
		std::cout << "Citroen engine can not be stopped. Please turn on parking break." << std::endl;

	return m_parking_break;
}

void Citroen::set_gear(unsigned char gear)
{
	m_gear_status = gear;
	std::cout << "Citroen current gear is " << (unsigned short)m_gear_status << std::endl;
}

void Citroen::set_parking_break(bool value)
{
	m_parking_break = value;
	std::cout << "Citroen parking break is changed to " << m_parking_break << std::endl;
}

void Citroen::accelerate()
{
	if (m_fuel_level > 0)
	{
		m_fuel_level -=3;
		std::cout << "Citroen accelerate is press. Fuel level is " << (unsigned short)m_fuel_level << std::endl;
	}
	else
	{
		std::cout << "Citroen fuel tank level is empty. Can't accelerate." << std::endl;
	}
}

void Citroen::put_break()
{
	std::cout << "Citroen pressed breaking." << std::endl;
}

void Citroen::add_fuel(unsigned char value)
{
	m_fuel_level += value;
	std::cout << "Citroen fuel added." << std::endl;
}

bool Citroen::is_accaptable_for_usage()
{
	return CITROEN_POLUTION_RATE < MAX_POLLUTION_RATE;
}
