#ifndef _MECHANIC_
#define _MECHANIC_

#include <iostream>
#include "Engine.h"

// friend class for Engine
class Mechanic
{
public:
	void print_configuration(const Engine& engine) const noexcept
	{
		// example of using friend class relationship between Engine and Mechanic clasess
		std::cout << "num of cylinders - " << static_cast<unsigned short>(engine.m_num_cylinders) << std::endl;
		std::cout << "capacity of engine - " << static_cast<unsigned short>(engine.m_capacity) << std::endl;
		std::cout << "year production - " << engine.m_year << std::endl;
		std::cout << "fuel type - " << engine.m_fuel_type << std::endl;
	}
};

// friend function for Engine
void print_configuration(const Engine& engine)
{
	std::cout << "num of cylinders - " << static_cast<unsigned short>(engine.m_num_cylinders) << std::endl;
	std::cout << "capacity of engine - " << static_cast<unsigned short>(engine.m_capacity) << std::endl;
	std::cout << "year production - " << engine.m_year << std::endl;
	std::cout << "fuel type - " << engine.m_fuel_type << std::endl;
}


#endif // _MECHANIC_