#pragma once
#include <iostream>
class Logger
{
public:
	// default constructor
	Logger() : m_index(-1)
	{
		std::cout << "Default constructor of class Logger " << m_index << std::endl;
	}

	// parameterized constructor
	Logger(int x) : m_index(x)
	{
		std::cout << "Parametrized constructor of class Logger " << m_index << std::endl;
	}

	// copy constructor
	Logger(const Logger& ref)
	{
		m_index = ref.m_index;
		std::cout << "Copy constructor of class Logger " << m_index << std::endl;
	}

	// assignement operator
	Logger& operator=(const Logger& right_side)
	{
		m_index = right_side.m_index;
		std::cout << "Assigment operator of class Logger " << m_index << std::endl;
		return *this;
	}

	// destructor
	~Logger()
	{
		std::cout << "Destructor of class Logger " << m_index << std::endl;
	}

private:
	int m_index;
};