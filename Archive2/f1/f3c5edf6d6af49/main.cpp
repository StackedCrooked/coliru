#include <map>
#include <string>
#include <vector>

struct Foo
{
    explicit Foo(int); // Disallow implicit construction from ints.
};

struct Bar
{
    Bar(int); // Allow implicit construction from ints.
};

int main()
{
    std::map<Foo, double> fooMap;
    std::map<Bar, double> barMap;
 
	//typedef std::remove_reference<decltype(fooMap[0])>::type fooMapType; // double
    typedef std::remove_reference<decltype(barMap[0])>::type barMapType; // double
}