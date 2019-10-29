#include <iostream>
#include "Car.h"
#include "Renault.h"
#include "Peugeot.h"
#include "Citroen.h"

#include "Engine.h"
#include "Mechanic.h"

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

	return EXIT_SUCCESS;
}