#include "MyFunctor.h"
#include <iostream>

using namespace std;

MyFunctor::MyFunctor(int _lowerBound, int _upperBound) : m_lowerBound(_lowerBound), m_upperBound(_upperBound)
{
	cout << __FUNCTION__ << endl;
}

bool MyFunctor::operator()(int _n) const
{
	bool result = m_lowerBound <= _n && _n <= m_upperBound;
	cout << __FUNCTION__ << "n =" << _n << " result = " << result << endl;
	return result;
}

int MyFunctor::getLowerBound() const
{
	return m_lowerBound;
}

int MyFunctor::getUpperBound() const
{
	return m_upperBound;
}