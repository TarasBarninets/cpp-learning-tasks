#include "Peugeot.h"
#include "CarConfig.h"
#include <iostream>

// add variable with static storage this means that variable is available only within this file
static const unsigned short PEUGEOT_POLUTION_RATE = 151;

Peugeot::Peugeot(unsigned char fuel_level) : Car(fuel_level)
{
	std::cout << "Peugeot car is constructed" << std::endl;
}

Peugeot::~Peugeot()
{
	std::cout << "Peugeot car is destroyed" << std::endl;
}

bool Peugeot::start_engine()
{
	if (m_fuel_level)
		std::cout << "Peugeot engine started." << std::endl;
	else
		std::cout << "Peugeot fuel level is empty. Can not start engine." << std::endl;

	return m_fuel_level;
}

bool Peugeot::stop_engine()
{
	if (m_parking_break)
		std::cout << "Peugeot engine stopped." << std::endl;
	else
		std::cout << "Peugeot engine can not be stopped. Please turn on parking break." << std::endl;

	return m_parking_break;
}

void Peugeot::set_gear(unsigned char gear)
{
	m_gear_status = gear;
	std::cout << "Peugeot current gear is " << (unsigned short)m_gear_status << std::endl;
}

void Peugeot::set_parking_break(bool value)
{
	m_parking_break = value;
	std::cout << "Peugeot parking break is changed to " << m_parking_break << std::endl;
}

void Peugeot::accelerate()
{
	if (m_fuel_level > 0)
	{
		m_fuel_level -=2;
		std::cout << "Peugeot accelerate is press. Fuel level is " << (unsigned short)m_fuel_level << std::endl;
	}
	else
	{
		std::cout << "Peugeot fuel tank level is empty. Can't accelerate." << std::endl;
	}
}

void Peugeot::put_break()
{
	std::cout << "Peugeot pressed breaking." << std::endl;
}

void Peugeot::add_fuel(unsigned char value)
{
	m_fuel_level += value;
	std::cout << "Peugeot fuel added." << std::endl;
}

bool Peugeot::is_accaptable_for_usage()
{
	return PEUGEOT_POLUTION_RATE < MAX_POLLUTION_RATE;
}
