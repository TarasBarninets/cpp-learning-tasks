#include <iostream>
#include <algorithm>

using namespace std;

class MyString
{
public:
	MyString()
	{

	}

	MyString(const char* c_str)
	{
		std::cout << __FUNCSIG__ << std::endl;

		m_size = strlen(c_str) + 1;
		m_data = new char[m_size];

		// make deep copy of c-string from literal to heap
		for (int i = 0; i < m_size; i++)
		{
			*(m_data + i) = *(c_str + i); // m_data[i] = c_str[i], ptr[i] = *(ptr + i)
		}
		// memcpy(m_data, c_str, m_size);
	}

	MyString(const MyString& str)
	{
		std::cout << __FUNCSIG__ << std::endl;

		m_size = str.m_size;

		// example of shallow copy is m_data = str.m_data;
		// deep copy is :
		m_data = new char[m_size];
		for (int i = 0; i < m_size; i++)
		{
			*(m_data + i) = *(str.m_data + i);
		}
	}

	~MyString()
	{
		std::cout << __FUNCSIG__ << std::endl;

		delete[] m_data;
	}

	MyString& operator=(const MyString& rhs)
	{
		if (this != &rhs) // 0. make sure that we do not assign to ourself, otherwise we will free memory incorrectly
		{
			// 1. delete memory of old c-string
			delete[] this->m_data;
			this->m_data = nullptr;

			// 2. allocate memory for new c-string for rhs
			this->m_data = new char[rhs.m_size];

			// 3. deep copy of rhs c-string (m_data)
			for (int i = 0; i < rhs.m_size; i++)
			{
				*(this->m_data + i) = *(rhs.m_data + i);
			}

			this->m_size = rhs.m_size;
		}

		return *this;
	}

	char& operator[](size_t index) const
	{
		std::cout << __FUNCSIG__ << std::endl;
		return *(m_data + index);
	}

	bool operator==(const MyString& rhs)
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

	MyString operator+(const MyString& rhs)
	{
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

	MyString& const operator+=(const MyString& rhs)
	{
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

	size_t length() const
	{
		std::cout << __FUNCSIG__ << std::endl;
		return m_size;
	}

	bool empty() const
	{
		std::cout << __FUNCSIG__ << std::endl;
		return (m_size == 0);
	}

	void clear()
	{
		std::cout << __FUNCSIG__ << std::endl;
		m_data[0] = '\0';
		m_size = 0;
	}

	size_t find(const MyString& str) const
	{
		if (this->m_size < str.m_size)
		{
			return m_npos;
		}

		size_t substring_length = str.m_size - 1;

		int i = 0, j = 0;
		for ( ; (i < this->m_size - 1) && (j < substring_length); ++i)
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

	void swap(MyString& str)
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

	const char* c_str() const
	{
		std::cout << __FUNCSIG__ << std::endl;
		return m_data;
	}
	
private:
	char* m_data = nullptr;
	size_t m_size = 0;
	static const size_t m_npos = -1;
};

int main()
{
	MyString object1("bbbbbbbbbbbbbbb");
	MyString object2("aaaaa");
	object1 = object2;

	{
		MyString object2("234234234"); // object2 - contains copy, object1 - MUST NOT BE MODIFED
		object2 = "12348946516516516"; // heavy, because create MyString temp objects from const char *
	}

	MyString object3;
	MyString object4 = "object4";

	// example of using empty() method
	std::cout << object3.empty() << std::endl;
	std::cout << object4.empty() << std::endl;

	// example of using clear() method
	std::cout << object4.c_str() << std::endl;
	object4.clear();
	std::cout << object4.empty() << std::endl;

	object4 = "object4";
	MyString object5("This is test string ");
	MyString object6("test");
	MyString object7("object7");

	// example of using find() method
	size_t index = object5.find(object6);
	std::cout << index << std::endl;

	// example of using swap() method
	std::cout << object6.c_str() << std::endl;
	std::cout << object7.c_str() << std::endl;
	object7.swap(object7);
	object7.swap(object6);
	std::cout << object6.c_str() << std::endl;
	std::cout << object7.c_str() << std::endl;

	// example of using overloaded operator==
	MyString object8("test");
	MyString object9("bbbbbbbbbbbbbbb");
	std::cout << (object7 == object8) << std::endl;
	std::cout << (object1 == object9) << std::endl;
	std::cout << (object6 == object4) << std::endl;

	// example of using overloaded operator+
	MyString object10 = object8 + object9;
	MyString object11 = object5 + object7;
	std::cout << object10.c_str() << std::endl;
	std::cout << object11.c_str() << std::endl;

	// example of using overloaded operator+=
	object8 += object9;
	std::cout << object8.c_str() << std::endl;

	return EXIT_SUCCESS;
}