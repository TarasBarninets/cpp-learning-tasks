#pragma once
#include <iostream>

class Car
{
public:
	Car(unsigned char fuel_level) : m_fuel_level(fuel_level)
	{
		std::cout << "Abstract car constructor is called" << std::endl;
	}

	virtual ~Car()
	{
		std::cout << "Abstract car destructor is called" << std::endl;
	}

	virtual bool start_engine() = 0;
	virtual bool stop_engine() = 0;
	virtual void set_gear(unsigned char gear) = 0;
	virtual void set_parking_break(bool value) = 0;
	virtual void accelerate() = 0;
	virtual void put_break() = 0;
	virtual void add_fuel(unsigned char value) = 0;
	virtual bool is_accaptable_for_usage() = 0;

protected:
	bool m_parking_break = true;
	unsigned char m_gear_status = 0;
	unsigned char m_fuel_level = 0;
};

