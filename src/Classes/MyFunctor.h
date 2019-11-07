#pragma once
#include <vector>

class MyFunctor
{
public:
	MyFunctor(int _lowerBound, int _upperBound);

	bool operator()(int _n) const;

	int getLowerBound() const;
	int getUpperBound() const;

private:
	int m_lowerBound, m_upperBound;
};

template<typename T>
size_t count(std::vector<int>& vector, const T& functor)
{
	size_t num = 0;

	for (auto element : vector)
	{
		if (functor(element))
		{
			std::cout << element << " in range [" << functor.getLowerBound() << "," << functor.getUpperBound() << "]";
			++num;
		}
	}
	return num;
}