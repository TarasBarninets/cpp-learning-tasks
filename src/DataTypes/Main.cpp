#include <iostream>

void print_memory(unsigned char* memory, size_t bytes)
{
	for (size_t i = 0; i < bytes; i++)
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

	// bitwise operations and two compliment code
	int i = 8; // 0000 0000 0000 0000 0000 0000 0000 1000 - direct code
	i = 8 | 1; // 0000 0000 0000 0000 0000 0000 0000 1001 - direct code
	std::cout << i; // 9

	i = ~i; // 1111 1111 1111 1111 1111 1111 1111 0110 - two compliment code
			// 0000 0000 0000 0000 0000 0000 0000 1001 - reverse code
			// 0000 0000 0000 0000 0000 0000 0000 1010 - +1 -> direct code
			// result = - direct code = - 10

	std::cout << i; // - 10

	unsigned int k = 11; // 0000 0000 0000 0000 0000 0000 0000 1011, 0000 0000 0000 0000 0000 0000 0000 0100
	k = k ^ 4; // 0000 0000 0000 0000 0000 0000 0000 1111
	std::cout << k << std::endl; // 15

	int q = k; // 0000 0000 0000 0000 0000 0000 0000 1111
	std::cout << q << std::endl; // 15

	k = k | 0b1000'0000'0000'0000'0000'0000'0000'0000; // 1000 0000 0000 0000 0000 0000 0000 1111
	q = k; // 1000 0000 0000 0000 0000 0000 0000 1111 , MSB is - 1, we understand this bits are two compliment code
	// 0111 1111 1111 1111 1111 1111 1111 0000 , ~ - opposite code
	// 0111 1111 1111 1111 1111 1111 1111 0001 , +1 - direct code
	// result = - direct code = - 2147483633
	std::cout << q << std::endl;

	// example of using bitmask
	const unsigned int SECOND_BYTE_MASK = 0x0000FF00;
	unsigned int num = 0xABCD10EF;
	unsigned int intermid = num & SECOND_BYTE_MASK; // 0x00001000
	unsigned char data = static_cast<unsigned char>(intermid >> 8); // 0x00000010 , logical shift because UNSIGINED value

	// example of arithmetical shift
	int value = -41561616; // 0b1111'1101'1000'0101'1101'0001'1111'0000 - 0xFD85D1F0
	value = value >> 2; // 0b1111'1111'0110'0001'0111'0100'0111'1100 - 0xFF61747C

	return EXIT_SUCCESS;
}