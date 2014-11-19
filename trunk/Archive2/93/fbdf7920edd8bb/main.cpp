#include <iostream>
#include <map>
#include <string>

class Foo
{
private:
    std::map<std::string, long long int> libFunctions;

public:
    Foo(std::string)
	{
		putInMap("hello", 1);
		putInMap("world", 2);
	}

	Foo(const Foo&)
    {
        // bugged copy constructor!
    }
    
	~Foo(void) {}

	void putInMap(const std::string& key, long long int val)
	{
		libFunctions[key] = val;
	}

    template<typename FunctionPointerType>
    FunctionPointerType getFunctionPtr(std::string functionName);
};

template<typename FunctionPointerType>
FunctionPointerType Foo::getFunctionPtr(std::string functionName)
{
    return reinterpret_cast<FunctionPointerType>(this->libFunctions[functionName]);
}

int main()
{
    // This compiler elides the copy here, but VS2012 does not.
    // I'll restructure to prevent the elision and demostrate the bug.
	// Foo f = Foo("foo");
    Foo temp("foo");
    Foo f = temp;
    
	auto one = reinterpret_cast<long long int>(f.getFunctionPtr<int(*)()>("hello"));
    auto two = reinterpret_cast<long long int>(f.getFunctionPtr<double(*)(int, char)>("world"));
    std::cout << one << "," << two;
}