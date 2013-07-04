#include <list>
#include <iostream>

namespace test
{
    class vehicle
	{
		public:

			virtual void foo()
			{
				std::cout << "foo" << std::endl;
			}
	};

	class car : public vehicle
	{
		public:

			void bar()
			{
				std::cout << "bar" << std::endl;
			}
	};

	class bicycle : public vehicle
	{
		public:

			void foobar()
			{
				std::cout << "foobar" << std::endl;
			}
	};
}

int main()
{
	std::list<test::vehicle*> vehicles;

	for (unsigned int count = 0; count < 10; count++)
	{
		vehicles.push_back(new test::car());
	}

	for (unsigned int count = 0; count < 5; count++)
	{
		vehicles.push_back(new test::bicycle());
	}

	// Loop through all bicycles in vehicles.

	for (test::vehicle* vehicle : vehicles)
	{
		test::bicycle* bike = dynamic_cast<test::bicycle*>(vehicle);

		if (bike)
		{
			std::cout << "bicycle!" << std::endl;
		}
	}

	// Loop through all cars in vehicles.

	for (test::vehicle* vehicle : vehicles)
	{
		test::car* car = dynamic_cast<test::car*>(vehicle);

		if (car)
		{
			std::cout << "car!" << std::endl;
		}
	}
}