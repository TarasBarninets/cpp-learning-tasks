#include <iostream>

int Fibonachi(int num)
{
	int f0 = 0, f1 = 1;
	if (num == 0)
		return f0;
	if (num == 1)
		return f1;
	else
		return (Fibonachi(num - 1) + Fibonachi(num - 2));
}

int Factorial(int num)
{
	// Recursion fall
	if (num == 0) // Recursion exit
	{
		return 1;
	}
	else
	{
		int result = Factorial(num - 1);
		result = num * result; // Recursion rise;
		return result;
	}
}

int test_recursion(int level)
{
	std::cout << "Recursion down call " << level << std::endl;

	if (level == 0)
	{
		std::cout << "Meet exit condition(base condition)" << std::endl;
		return 0;
	}

	int prev_level = test_recursion(level-1);

	std::cout << "Recursion up call " << level << std::endl;

	return prev_level;
}

int main()
{
	const int a = 1, b = 2, c = 3, d = 4, e = 5, x = 11, y = 25;

	std::cout << "Factorial " << a << " = " << Factorial(a) << std::endl;
	std::cout << "Factorial " << b << " = " << Factorial(b) << std::endl;
	std::cout << "Factorial " << c << " = " << Factorial(c) << std::endl;
	std::cout << "Factorial " << d << " = " << Factorial(d) << std::endl;
	std::cout << "Factorial " << e << " = " << Factorial(e) << std::endl;
	std::cout << "Factorial " << x << " = " << Factorial(x) << std::endl;

	std::cout << "Fibonachi " << y << " = " << Fibonachi(y) << std::endl;
	
	test_recursion(5);

	return 0;
}