#include "Exceptions.h"
#include <iostream>
#include <string>
#include "Logger.h"

void method1()
{
	Logger obj1(1);
	method2();
	Logger obj2(2);
}

void method2()
{
	try
	{
		std::shared_ptr<Logger> obj3(new Logger(3)); // RAII idiom - Resource Acquisition Is Initialization
		method3(); // this method generate excaption
		Logger obj4(4);
	}
	catch (std::string exception_object)
	{
		std::cout << exception_object << std::endl;
	}

	Logger obj5(5);
}

void method3()
{
	Logger obj6(6);
	throw std::string("test value");
	Logger obj7(7);
}