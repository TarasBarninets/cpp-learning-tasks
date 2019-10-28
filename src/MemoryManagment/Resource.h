#pragma once
#include <iostream>
#include <memory>

// forward declaration
class Resource2;

class Resource1
{
public:
	Resource1(size_t index) : m_index(index)
	{
		std::cout << "Constructor with parametr of Resource1 class [" << m_index << "]" << std::endl;
	}

	~Resource1()
	{
		std::cout << "Destructor of Resource1 class [" << m_index << "]" << std::endl;
	}

	size_t m_index;
	std::shared_ptr<Resource2> m_Resource2Ptr;
	std::weak_ptr<Resource2> m_Resource2WeakPtr;
};

class Resource2
{
public:
	Resource2(size_t index) : m_index(index)
	{
		std::cout << "Default constructor of Resource2 class [" << m_index << "]" << std::endl;
	}
	~Resource2()
	{
		std::cout << "Destructor of Resource2 class [" << m_index << "]" << std::endl;
	}

	size_t m_index;
	std::shared_ptr<Resource1> m_Resource1Ptr;
};