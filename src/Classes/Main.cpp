#include <iostream>
#include "Car.h"
#include "Renault.h"
#include "Peugeot.h"
#include "Citroen.h"

#include "Engine.h"
#include "Mechanic.h"

#include "MyFunctor.h"
#include <vector>
#include <cstdlib>
#include <algorithm>

void test_drive(Car* ptr)
{
	// dynamic polymorphism is using here
	bool usage = ptr->is_accaptable_for_usage();

	if (usage)
		std::cout << "Car can be using" << std::endl;
	else
		std::cout << "Car can't be using, POLUTION RATE OVER LIMIT" << std::endl;


		if (usage && ptr->start_engine())
		{
			ptr->set_parking_break(false);
			ptr->set_gear(1);
			ptr->accelerate();
			ptr->set_gear(2);
			ptr->accelerate();
			ptr->put_break();
			ptr->set_gear(1);
			ptr->set_parking_break(true);
			ptr->stop_engine();
		}
}

std::ostream& operator<<(std::ostream& cout, const std::vector<int>& input)
{
	for (auto const& i : input) {
		cout << i << " ";
	}
	return cout;
}

int main()
{
	Car* pRenault = new Renault(20);
	test_drive(pRenault);
	delete pRenault;
	std::cout << std::endl;

	Peugeot* pPeugeot = new Peugeot(0);
	test_drive(pPeugeot);
	delete pPeugeot;
	std::cout << std::endl;

	Citroen* pCitroen = new Citroen(50);
	test_drive(pCitroen);
	delete pCitroen;
	std::cout << std::endl;

	Engine* pEngine = new Engine(4, 2000, 2006, Diesel);
	Mechanic object;
	object.print_configuration(*pEngine);
	print_configuration(*pEngine);
	delete pEngine;
	std::cout << std::endl;

	int lowerBound = 40, upperBound = 60;

	std::vector<int> myVector;
	for (int i = 0; i < 10; i++)
	{
		myVector.push_back(rand() % 100 + 1);
	}

	std::cout << "Vector contain next elements : " << myVector << std::endl;

	// example of using lambda function
	int result = std::count_if(myVector.begin(), myVector.end(), 
		[lowerBound, upperBound](int n) {
			return (n > lowerBound && n < upperBound);
		});
	std::cout << result << std::endl;

	// example of using Functor
	MyFunctor functor(lowerBound, upperBound);
	std::cout << count(myVector, functor);

	std::vector<int> original = { 1,2,3,4,5,6,7,8,9 };
	std::vector<int> modified; // {10,20,30,40,50,60,70,80,90}
	modified.resize(original.size());

	std::transform(original.begin(), original.end(), modified.begin(), [](int n) {
		return n * 10; // [](int n){return n*10;} - lambda function
		});

	return EXIT_SUCCESS;
}