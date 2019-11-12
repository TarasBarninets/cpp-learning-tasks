#include <iostream>
#include "MyString.h"

int main()
{
	MyString object1("bbbbbbbbbbbbbbb");
	MyString object2("aaaaa");
	object1 = object2;

	{
		MyString object2("234234234"); // object2 - contains copy, object1 - MUST NOT BE MODIFED
		object2 = "12348946516516516"; // heavy, because create MyString temp objects from const char *
	}

	MyString object3;
	MyString object4 = "object4";

	// example of using empty() method
	std::cout << object3.empty() << std::endl;
	std::cout << object4.empty() << std::endl;

	// example of using clear() method
	std::cout << object4.c_str() << std::endl;
	object4.clear();
	std::cout << object4.empty() << std::endl;

	object4 = "object4";
	MyString object5("This is test string ");
	MyString object6("test");
	MyString object7("object7");

	// example of using find() method
	size_t index = object5.find(object6);
	std::cout << index << std::endl;

	// example of using swap() method
	std::cout << object6.c_str() << std::endl;
	std::cout << object7.c_str() << std::endl;
	object7.swap(object7);
	object7.swap(object6);
	std::cout << object6.c_str() << std::endl;
	std::cout << object7.c_str() << std::endl;

	// example of using overloaded operator==
	MyString object8("test");
	MyString object9("bbbbbbbbbbbbbbb");
	std::cout << (object7 == object8) << std::endl;
	std::cout << (object1 == object9) << std::endl;
	std::cout << (object6 == object4) << std::endl;

	// example of using overloaded operator+
	MyString object10 = object8 + object9;
	MyString object11 = object5 + object7;
	std::cout << object10.c_str() << std::endl;
	std::cout << object11.c_str() << std::endl;

	// example of using overloaded operator+=
	object8 += object9;
	std::cout << object8.c_str() << std::endl;

	return EXIT_SUCCESS;
}