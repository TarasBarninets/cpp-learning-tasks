#include <iostream>

// forward declaration
struct Resource2;

struct Resource1
{
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

struct Resource2
{
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

	return EXIT_SUCCESS;
}