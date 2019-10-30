#include <iostream>

void print_memory(unsigned char* memory, size_t bytes)
{
	for (int i = 0; i < bytes; i++)
	{
		std::cout << std::hex << static_cast<unsigned short>(*(memory + i)) << " ";
	}

	std::cout << std::endl;
}

union TestUnion
{
	int a;
	char byte[4];
};

// C++98, C++03 -> old enum (enumeration)
// has global scope
// integer type
enum FuelType
{
	LPG, // 0
	Diesel, // 1
	Petrol = 3, // 3
	Electric // 4
};

// startic from C++11 standart
// do NOT have global scope, has own NAMESPACE
// has own type, can not be converted to int
enum class Currency
{
	UAH,
	USD,
	EUR,
	HKN
};

void test(int k)
{
	std::cout << "k = " << k << std::endl;
}

int main()
{
	int x = 152; // direct code			[s][vvvvvvvvvvv...]
	int y = -17; // two compliment code	[s][ddddddddddd....]
	unsigned int z = 178; // standart form [vvvvvvvvvvvv....]
	float f = 1.4f; // IEEE-754 32 bit standart - [s(1)][e(8)][m(23)]
	double d = 1.7; // IEEE-754 64 bit standart - [s(1)][e(11)][m(52)]

	// char - short - int - float - double
	
	print_memory((unsigned char*)& x, sizeof(int));

	print_memory((unsigned char*) &y, sizeof(int));

	print_memory((unsigned char*) &z, sizeof(unsigned int));

	print_memory((unsigned char*) &f, sizeof(unsigned int));

	print_memory((unsigned char*) &d, sizeof(unsigned int));

	TestUnion object;
	object.a = 655536;

	print_memory((unsigned char*)& object, sizeof(TestUnion));
	print_memory((unsigned char*)& object.byte[3], sizeof(char));

	std::cout << "TestUnion size is " << sizeof(TestUnion) << std::endl;

	// C++03
	FuelType type = Diesel;
	test(type); // implict conversion FuelType to int
	std::cout << "Diesel size is " << sizeof(FuelType) << std::endl;

	// C++11
	Currency current = Currency::UAH;
	test(static_cast<int>(current)); // can not convert Currency to int

	return EXIT_SUCCESS;
}