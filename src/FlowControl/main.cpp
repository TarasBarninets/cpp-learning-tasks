#include <iostream>

bool ret_true()
{
	std::cout << "true" << std::endl;
	return true;
}

bool ret_false()
{
	std::cout << "false" << std::endl;
	return false;
}

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

	// logical operations
	if (ret_true() && ret_true() && ret_true() || ret_false() && ret_true())
		std::cout << "result true" << std::endl;
	else
		std::cout << "result false" << std::endl;

	if (ret_false() && ret_true() && ret_true() && ret_true() && ret_true())
		std::cout << "result true" << std::endl;
	else
		std::cout << "result false" << std::endl;

	int* pCat = nullptr;
	int* pDog = nullptr;

	if (pCat && pDog)
	{
		// make some calls with pCat and pDog
		// pCat->call()
		// pDog->method2()
	}
	else
	{
		// pCat or pDog is an invalid pointer
	}

	return EXIT_SUCCESS;
}