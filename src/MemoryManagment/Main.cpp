#include <iostream>
#include <execution>
#include "Exceptions.h"
#include "Resource.h"

class PtrVsRef
{
public:
	int& m_ref;
	int* m_ptr;
	PtrVsRef(int& ref, int* ptr) : m_ref(ref), m_ptr(ptr) {}
};

class Base2{};

class Base 
{
	virtual void print() { std::cout << "Base" << std::endl; }
};

class Derived1: public Base 
{
	void print() { std::cout << "Derived1" << std::endl; }
};

class Derived2 : public Base
{
	void print() { std::cout << "Derived2" << std::endl; }
};

void testLocalStaticVariable()
{
	int k = 0; // on stack
	static int i = 0; // globaly in data segment

	k++;
	i++;

	std::cout << "k = " << k << std::endl;
	std::cout << "i = " << i << std::endl;
}

Logger& invalidLoggerReturn()
{
	Logger object(1);
	return object;
}

std::shared_ptr<Logger> validLoggerReturnSmarPotiner()
{
	std::shared_ptr<Logger> object(new Logger(2));

	// NEW OBJECT HAS NOT BEEN CREATED, WE JUST CREATE A POINTER ON the object, so this is INVALID using of smart_pointers
	std::shared_ptr<Logger>* object2 = &object; 

	// smart pointer ALWAYS must be return/passed BY VALUE because only on COPY constructor or ASSIGNMENT operator which modify ref counter
	return object;
}

Logger* validLoggerReturnRawPointer()
{
	Logger* ptr = new Logger(3);
	return ptr;
}
int main()
{
	testLocalStaticVariable(); // k = 0, i = 0
	testLocalStaticVariable(); // k = 0, i = 1
	testLocalStaticVariable(); // k = 0, i = 2

	Logger& object = invalidLoggerReturn();
	std::cout << "Invalid function return object on stack, so we can not use this object" << std::endl;

	std::shared_ptr<Logger> pLogger = validLoggerReturnSmarPotiner();
	// pLogger ref coutner is equal 1

	Logger* rawPtrLogger = validLoggerReturnRawPointer();
	delete rawPtrLogger;

	// test unique ptr
	{
		std::unique_ptr<Resource1> ptr1(new Resource1(1));
		std::unique_ptr<Resource1> ptr2(new Resource1(2));

		// ptr2 = ptr1; compilation error because unique_ptr prohibit copy and assignment
		ptr2 = std::move(ptr1); // transfer ownership from ptr1 to ptr2, ptr1 = nullptr
		ptr2.reset(); // delete ptr2 resources, ptr2 = nullptr
	}
	std::cout << "-----------------------------------------" << std::endl;

	// test shared ptr
	{
		std::shared_ptr<Resource1> ptr1(new Resource1(3));
		std::shared_ptr<Resource1> ptr2(new Resource1(4));
		std::shared_ptr<Resource1> ptr3(new Resource1(5));
		ptr2 = ptr1; // share ownership from ptr1 to ptr2, ptr2 decrement ref counter of resource 4, increment ref counter of resource 3
		ptr3 = ptr1; // share ownership from ptr1 to ptr3, ptr3 decrement ref counter of resource 4, increment ref counter of resource 3
		std::cout << "References counter of ptr1 " << ptr1.use_count() << std::endl;
		ptr3.reset(); // ptr3 release ownership of resource 3 and decrement ref counter of resource 3
		std::cout << "References counter of ptr1 " << ptr1.use_count() << std::endl;
	}
	std::cout << "-----------------------------------------" << std::endl;

	// test cross reference issue
	{
		std::shared_ptr<Resource1> ptr1(new Resource1(6));
		std::shared_ptr<Resource2> ptr2 = std::make_shared<Resource2>(7);

		ptr1->m_Resource2Ptr = ptr2;
		ptr2->m_Resource1Ptr = ptr1;

		std::cout << "ref count ptr1 = " << ptr1.use_count() << std::endl;
		std::cout << "ref count ptr2 = " << ptr2.use_count() << std::endl;
		// we get memory leak here
	}
	std::cout << "-----------------------------------------" << std::endl;

	// solve cross reference issue by using weak_ptr
	{
		std::shared_ptr<Resource1> ptr1(new Resource1(8));
		std::shared_ptr<Resource2> ptr2 = std::make_shared<Resource2>(9);

		// we use weak ptr and as result there no cross reference, because weak ptr doesnt increase ref counter
		ptr1->m_Resource2WeakPtr = ptr2; // ref counter will not be incremented because of weak_ptr
		ptr2->m_Resource1Ptr = ptr1;

		std::cout << "ref count ptr1 = " << ptr1.use_count() << std::endl;
		std::cout << "ref count ptr2 = " << ptr2.use_count() << std::endl;

		// example of using weak ptr
		std::shared_ptr<Resource2> sharedPtrOnResource2 = ptr1->m_Resource2WeakPtr.lock();
		if (sharedPtrOnResource2)
		{
			// use sharedPtrOnResource2 here
		}
	}
	std::cout << "-----------------------------------------" << std::endl;

	// pointer vs reference
	{
		int x = 1, y = 2;
		int& p = x; // this reference will be resolved at the compile time, so we will not allocate memory for p referenc on stack
		int* ptr = &x;
		PtrVsRef object(x, &y);

		std::cout << "adress of object m_ref = " << &object.m_ref << std::endl;
		std::cout << "adress of object m_ptr = " << &object.m_ptr << std::endl;
		std::cout << "adress of x = " << &x << std::endl;
		std::cout << "adress of y = " << &y << std::endl;
		std::cout << "sizeof Test = " << sizeof(PtrVsRef) << std::endl;
		std::cout << "&p = " << &p << std::endl;

		/*
		cout result:
			adress of object m_ref = 007CF710
			adress of object m_ptr = 007CF6E0
			adress of x = 007CF710
			adress of y = 007CF704
			sizeof Test = 8
			&p = 007CF710
		*/
	}
	std::cout << "-----------------------------------------" << std::endl;

	// static_cast - resolve at compile time
	{
		float f = 3.5;
		int i = static_cast<int>(f);
		Derived1 derivedObject;
		Base* ptr1Base = static_cast<Base*>(&derivedObject); // upcasting
		Derived1* ptr1Derived1 = static_cast<Derived1*>(ptr1Base); // downcasting
		void* vPtr = static_cast<void*>(ptr1Derived1); // converting to *void
		Derived1* ptr2Derived1 = static_cast<Derived1*>(vPtr); // converting from void*
		// Base2* ptr1Base2 = static_cast<Base2*>(ptr2Base); - cant make casting between classes from different hierarchy (Base and Base2)
		// In such case - get COMPILATION ERROR.
	}
	// dynamic_cast - use RTTI(embedded in Virtual table), so resolve at runtime
	{
		Derived1 objectDerived1;
		Base* ptrBase = dynamic_cast<Base*>(&objectDerived1); // upcasting
		Derived1* ptrDerived1 = dynamic_cast<Derived1*>(ptrBase); // downcasting
		if (ptrDerived1 == nullptr)
		{
			std::cout << "Casting failed" << std::endl;
		}
		else
		{
			std::cout << "Casting performed" << std::endl;
		}
		try
		{
			Derived2& refDerived2 = dynamic_cast<Derived2&>(objectDerived1);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	// const_cast - remove const from pointer and reference, can not change real const variable e.g. const int a = 7;
	{
		int a = 7;
		const int* ptr1 = &a;
		int* ptr2 = const_cast<int*>(ptr1);
		*ptr2 = 77; // changed value of a
	}

	// reinterpret_cast - do not change anything, just reinterpret bit as another type
	{
		int x = 1, y = 2;
		PtrVsRef object(x, &y);
		Resource1* ptr1 = new Resource1(1);
		PtrVsRef* ptr2 = reinterpret_cast<PtrVsRef*>(ptr1);
		PtrVsRef* ptr3 = reinterpret_cast<PtrVsRef*>(y);
	}
	std::cout << "-----------------------------------------" << std::endl;


	// exeptions - try, catch, throw
	method1();

	{
		int x = 3;
		try
		{
			if (x < 0)
				throw static_cast<bool>(x);
			else
				throw x;
		}
		catch(bool x)
		{ 
			std::cout << "Entered number less than zero!" << std::endl;
		}
		catch (int x)
		{
			std::cout << "Entered number more than zero!" << std::endl;
		}
	}

	try {
		TestException obj1;
	}
	catch (std::exception& obj)
	{
		std::cout << obj.what();
	}

	std::cout << "End of program" << std::endl;

	return EXIT_SUCCESS;
}