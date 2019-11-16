#pragma once
#include <string>

using namespace std;

class Book
{
public:
	Book(string title, string author, size_t year, int price) : m_title(title), m_author(author), m_year(year), m_price(price)
	{
		cout << __FUNCSIG__ << endl;
	}

	Book(const Book& ref) : m_title(ref.m_title), m_author(ref.m_author), m_year(ref.m_year), m_price(ref.m_price)
	{
		cout << __FUNCSIG__ << endl;
	}

	Book()
	{
		cout << __FUNCSIG__ << endl;
	}

	friend std::ostream& operator<<(std::ostream& out, const Book& ref);

public:
	string m_title;
	string m_author;
	size_t m_year = 0;
	int m_price = 0;
};

std::ostream& operator<<(std::ostream& out, const Book& ref)
{
	out << "Book is: " << ref.m_title << ", " << ref.m_author << ", " << ref.m_year << ", " << ref.m_price << endl;
	return out;
}