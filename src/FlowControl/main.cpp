#include <iostream>

int main()
{
	int a, b;
	std::cin >> a >> b;

	short operation;
	std::cin >> operation;
	
	switch (operation) // operation allows only INTEGER numbers(char, short, int)
	{
	case 1:
		std::cout << "a + b = " << a + b << std::endl;
		break;
	case 2:
		std::cout << "a - b = " << a - b << std::endl;
		break;
	case 3:
		std::cout << "a * b = " << a * b << std::endl;
		// this is error, should be break, otherwise occurs fall through
	case 4:
		std::cout << "a / b = " << a / b << std::endl;
		break;
	default:
		std::cout << "enter correct operation" << std::endl;
		break;
	}

	do
	{
		std::cout << "Before continue" << std::endl;
		continue; // jump to the begin of the next iteration
		std::cout << "After continue" << std::endl;
	} while (true);

	return EXIT_SUCCESS;
}