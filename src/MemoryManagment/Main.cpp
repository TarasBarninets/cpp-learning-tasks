#include <iostream>
#include <execution>

// forward declaration
class Resource2;

class Resource1
{
public:
	Resource1(size_t index) : m_index(index)
	{
		std::cout << "Default constructor of Resource1 class [" << m_index << "]" << std::endl;
	}
	~Resource1()
	{
		std::cout << "Destructor of Resource1 class [" << m_index << "]" << std::endl;
	}

	size_t m_index;
	std::shared_ptr<Resource2> m_Resource2Ptr;
	std::weak_ptr<Resource2> m_Resource2WeakPtr;
};

class Resource2
{
public:
	Resource2(size_t index) : m_index(index)
	{
		std::cout << "Default constructor of Resource2 class [" << m_index << "]" << std::endl;
	}
	~Resource2()
	{
		std::cout << "Destructor of Resource2 class [" << m_index << "]" << std::endl;
	}

	size_t m_index;
	std::shared_ptr<Resource1> m_Resource1Ptr;
};

class PtrVsRef
{
public:
	int& m_ref;
	int* m_ptr;
	PtrVsRef(int& ref, int* ptr) : m_ref(ref), m_ptr(ptr) {}
};

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


int main()
{
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
		int& p = x;
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

	// static_cast
	{
		Derived1 derivedObject;
		Base* ptr1Base = (Base*)&derivedObject; 
		Base* ptr2Base = static_cast<Base*>(&derivedObject); // upcasting
		Derived1* ptr1Derived1 = static_cast<Derived1*>(ptr2Base); // downcasting
		void* vPtr = static_cast<void*>(ptr1Derived1); // converting to *void
		Derived1* ptr2Derived1 = static_cast<Derived1*>(vPtr); // converting from void*
	}
	// dynamic_cast
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

	// const_cast
	{
		const int a = 7;
		int* ptr = const_cast<int*>(&a);
	}

	// reinterpret_cast
	{
		int x = 1, y = 2;
		PtrVsRef object(x, &y);
		Resource1* ptr1 = new Resource1(1);
		PtrVsRef* ptr2 = reinterpret_cast<PtrVsRef*>(ptr1);
	}

	return EXIT_SUCCESS;
}