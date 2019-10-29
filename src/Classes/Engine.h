#ifndef _ENGINE_
#define _ENGINE_

enum FuelType
{
	LPG,
	Diesel,
	Petrol,
	Electro
};

class Mechanic;

class Engine
{
public:
	Engine(unsigned char num_cylinders, unsigned short capacity, unsigned short year, FuelType fuel_type) : 
		m_num_cylinders(num_cylinders),
		m_capacity(capacity),
		m_year(year),
		m_fuel_type(fuel_type) {};

private:
	unsigned char m_num_cylinders;
	unsigned short m_capacity;
	unsigned short m_year;
	FuelType m_fuel_type;

	friend class Mechanic;
	friend void print_configuration(const Engine& engine);
};

#endif // _ENGINE_