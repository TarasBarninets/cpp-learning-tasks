#include <iostream>
#include <algorithm>
#include "MyString.h"


MyString::MyString()
{
	std::cout << __FUNCSIG__ << std::endl;
}

MyString::MyString(const char* c_str)
{
	std::cout << __FUNCSIG__ << std::endl;

	m_size = strlen(c_str) + 1;
	m_data = new char[m_size];

	// make deep copy of c-string from literal to heap
	for (size_t i = 0; i < m_size; i++)
	{
		*(m_data + i) = *(c_str + i); // m_data[i] = c_str[i], ptr[i] = *(ptr + i)
	}
	// memcpy(m_data, c_str, m_size);
}

MyString::MyString(const MyString& str)
{
	std::cout << __FUNCSIG__ << std::endl;

	m_size = str.m_size;

	// example of shallow copy is m_data = str.m_data;
	// deep copy is :
	m_data = new char[m_size];
	for (size_t i = 0; i < m_size; i++)
	{
		*(m_data + i) = *(str.m_data + i);
	}
}

MyString::~MyString()
{
	std::cout << __FUNCSIG__ << std::endl;

	delete[] m_data;
}

MyString& MyString::operator=(const char* rhs)
{
	std::cout << __FUNCSIG__ << std::endl;
	m_size = strlen(rhs) + 1;
	delete[] m_data;
	m_data = new char[m_size];

	// make deep copy of c-string from literal to heap
	memcpy(m_data, rhs, m_size);

	return *this;
}

MyString& MyString::operator=(const MyString& rhs)
{
	std::cout << __FUNCSIG__ << std::endl;
	if (this != &rhs) // 0. make sure that we do not assign to ourself, otherwise we will free memory incorrectly
	{
		// 1. delete memory of old c-string
		delete[] this->m_data;
		this->m_data = nullptr;

		// 2. allocate memory for new c-string for rhs
		this->m_data = new char[rhs.m_size];

		// 3. deep copy of rhs c-string (m_data)
		for (size_t i = 0; i < rhs.m_size; i++)
		{
			*(this->m_data + i) = *(rhs.m_data + i);
		}

		this->m_size = rhs.m_size;
	}

	return *this;
}

char& MyString::operator[](size_t index) const
{
	std::cout << __FUNCSIG__ << std::endl;
	return *(m_data + index);
}

bool MyString::operator==(const MyString& rhs) const
{
	if (this->m_size != rhs.m_size)
	{
		std::cout << m_data << " != " << rhs.m_data << " ";
		return false;
	}

	for (size_t i = 0; i < m_size; i++)
	{
		if ((m_data[i] ^ rhs.m_data[i]) == 0)
			continue;
		else
			std::cout << m_data << " != " << rhs.m_data << " ";

		return false;
	}

	std::cout << m_data << " == " << rhs.m_data << " ";
	return true;
}

bool MyString::operator!=(const MyString& rhs) const
{
	return !(*this == rhs);
}

MyString MyString::operator+(const MyString& rhs) const
{
	std::cout << __FUNCSIG__ << std::endl;
	MyString returnValue;
	returnValue.m_size = m_size + rhs.m_size - 1;
	returnValue.m_data = new char[returnValue.m_size];

	for (size_t i = 0; i < m_size - 1; i++)
	{
		returnValue.m_data[i] = m_data[i];
	}

	for (size_t i = m_size - 1, j = 0; i < returnValue.m_size; i++, j++)
	{
		returnValue.m_data[i] = rhs.m_data[j];
	}

	return returnValue;
}

MyString& MyString::operator+=(const MyString& rhs)
{
	std::cout << __FUNCSIG__ << std::endl;
	char* temp = new char[m_size + rhs.m_size - 1];
	memcpy(temp, m_data, m_size - 1);
	memcpy(temp + m_size - 1, rhs.m_data, rhs.m_size);

	delete[] m_data;
	m_data = temp;
	m_size = m_size + rhs.m_size - 1;

	/*char* temp_lhs = new char[m_size];
	size_t temp_size = m_size;
	memcpy(temp_lhs, m_data, m_size);
	delete[] m_data;

	this->m_size = this->m_size + rhs.m_size - 1;
	this->m_data = new char[this->m_size];

	memcpy(m_data, temp_lhs, temp_size - 1);
	memcpy((m_data + (temp_size - 1)), rhs.m_data, rhs.m_size);
	delete[] temp_lhs;*/

	return *this;
}

size_t MyString::length() const
{
	std::cout << __FUNCSIG__ << std::endl;
	return m_size;
}

bool MyString::empty() const
{
	std::cout << __FUNCSIG__ << std::endl;
	return (m_size == 0);
}

void MyString::clear()
{
	std::cout << __FUNCSIG__ << std::endl;
	m_data[0] = '\0';
	m_size = 0;
}

size_t MyString::find(const MyString& str) const
{
	std::cout << __FUNCSIG__ << std::endl;
	if (this->m_size < str.m_size)
	{
		return m_npos;
	}

	size_t substring_length = str.m_size - 1;

	size_t i = 0, j = 0;
	for (; (i < this->m_size - 1) && (j < substring_length); ++i)
	{
		if (m_data[i] == str.m_data[j])
		{
			++j;
		}
		else
		{
			j = 0;
		}
	}

	if (substring_length == j)
	{
		return (i - substring_length);
	}
	else
	{
		return m_npos;
	}
}

void MyString::swap(MyString& str)
{
	std::cout << __FUNCSIG__ << std::endl;
	if (this == &str)
	{
		return;
	}

	// std::swap(this->m_size, str.m_size);
	size_t temp_size = this->m_size;
	this->m_size = str.m_size;
	str.m_size = temp_size;

	// std::swap(this->m_data, str.m_data);
	char* temp_data = this->m_data;
	this->m_data = str.m_data;
	str.m_data = temp_data;

	/*if (m_size < str.m_size)
	{
		char* enough_str = new char[str.m_size];
		memcpy(enough_str, this->m_data, this->m_size);
		delete[] this->m_data;
		this->m_data = enough_str;
	}
	else if (m_size > str.m_size)
	{
		char* enough_str = new char[this->m_size];
		memcpy(enough_str, str.m_data, str.m_size);
		delete[] str.m_data;
		str.m_data = enough_str;
	}

	size_t size = std::max(str.m_size, this->m_size);

	for (int i = 0; i < size; i++)
	{
		char temp_symbol = *(this->m_data + i);
		*(this->m_data + i) = *(str.m_data + i);
		*(str.m_data + i) = temp_symbol;
	}

	size_t temp_size = this->m_size;
	this->m_size = str.m_size;
	str.m_size = temp_size;*/
}

const char* MyString::c_str() const
{
	std::cout << __FUNCSIG__ << std::endl;
	return m_data;
}