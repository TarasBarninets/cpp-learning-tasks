#pragma once

class MyString
{
public:

	MyString();
	MyString(const char* c_str);
	MyString(const MyString& str);
	~MyString();

	MyString& operator=(const MyString& rhs);
	char& operator[](size_t index) const;
	bool operator==(const MyString& rhs) const;
	MyString operator+(const MyString& rhs) const;
	MyString& operator+=(const MyString& rhs);

	size_t length() const;
	bool empty() const;
	void clear();
	size_t find(const MyString& str) const;
	void swap(MyString& str);
	const char* c_str() const;

private:
	char* m_data = nullptr;
	size_t m_size = 0;
	static const size_t m_npos = -1;
};