#include <iostream>

using namespace std;

class MyString
{
public:
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

	size_t length()
	{
		std::cout << __FUNCSIG__ << std::endl;
		return m_size;
	}

	const char* c_str()
	{
		std::cout << __FUNCSIG__ << std::endl;
		return m_data;
	}
	
private:
	size_t m_size = 0;
	char* m_data = nullptr;
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
	
	return EXIT_SUCCESS;
}