#include <iostream>



namespace custom{
    struct type;
}
namespace lib {
	void overload(custom::type);
}




// Imagine this is provided by some lib
namespace lib
{
	struct type {};

	template<class T>
	struct specialization
	{
		static void call()
		{
			std::cout << "specialization-default\n";
		}
	};

	template<>
	struct specialization<type>
	{
		static void call()
		{
			std::cout << "specialization(type)\n";
		}
	};

	template<class T>
	void overload(T)
	{
		std::cout << "overload-default\n";
	}

	void overload(type)
	{
		std::cout << "overload(type)\n";
	}

	template<class T>
	void call_overload()
	{
		overload(T());
	}

	template<class T>
	void call_specialization()
	{
		specialization<T>::call();
	}
}

// Imagine this is your custom namespace
namespace custom
{
	struct type {};
}

// Imagine now you want to extend the lib with your custom type
namespace lib
{
	void overload(custom::type)
	{
		std::cout << "overload(custom::type)\n";
	}

	template<>
	struct specialization<custom::type>
	{
		static void call()
		{
			std::cout << "specialization(custom::type)\n";
		}
	};
}

int main(int argc, char** argv) {
	// now see what will happen...
	lib::call_overload<custom::type>();
	lib::call_specialization<custom::type>();
	return 0;
}