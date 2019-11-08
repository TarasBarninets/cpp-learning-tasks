#include <iostream>

using namespace std;

class MyString
{
public:

	MyString(const char* c_str)
	{
		std::cout << __FUNCTION__ << std::endl;

		m_size = strlen(c_str) + 1;
		m_data = new char[m_size];

		// make deep copy of c-string from literal to heap
		for (int i = 0; i < m_size; i++)
		{
			*(m_data + i) = *(c_str + i); // m_data[i] = c_str[i], ptr[i] = *(ptr + i)
		}
		// memcpy(m_data, c_str, m_size);
	}

	~MyString()
	{
		std::cout << __FUNCTION__ << std::endl;

		delete[] m_data;
	}

	size_t length()
	{
		return m_size;
	}

	const char* c_str()
	{
		return m_data;
	}
	
private:
	size_t m_size = 0;
	char* m_data;
};

int main()
{
	MyString* mystringInstance = new MyString("15784");
	const char* ptr = mystringInstance->c_str();
	delete mystringInstance;
	int k = 7;
	std::cout << ptr << std::endl;

	return EXIT_SUCCESS;
}