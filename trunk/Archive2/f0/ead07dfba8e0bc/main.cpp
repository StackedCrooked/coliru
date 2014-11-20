#include <iostream>
#include <string>
#include <array>
#include <memory>
#include <utility>
#include <math.h>

static const unsigned MaxNumberOfInputBits = 16;
static const unsigned MaxNumberOfOpcodeBits = 1 << MaxNumberOfInputBits;

struct Object
{
    Object() {}
    ~Object() {}
};

void Deconstruct(Object *const objects, size_t num_objects)
{
    while(num_objects) objects[--num_objects].~Object();
}





#define min(a,b)  ((a < b) ? a : b)

int test_it(int a, int b)
{
    return (std::min)(a, b);
}

struct Incomplete;

struct A
{
    std::unique_ptr<Incomplete> incomplete;
    
    A();
    ~A();
};

struct S
{
    int i = 123;
    S() = default;
    S(int i) : i(i) {}
};

int foo(void) { return 1; }

auto f()
{
    auto x{1,2}; // direct-initialization, initializes an initializer_list.
    return x; // returns an initializer_list, instant UB to access it
}


A::~A() {}

struct Incomplete
{
    int i = 0;
};

A::A() : incomplete(new Incomplete)
{
}


int main(int argc, char* argv[]) 
{
    std::cout << "test_it(1,3)=" << test_it(1,3) << "\n";
    
    std::cout << "sizeof(unsigned long)=" << sizeof(unsigned long) << "\n";
    A aaaa;
    std::cout << "incomplete: " << aaaa.incomplete->i << "\n";
    
    std::array<unsigned, 127> a{};
    
    a[1] = 0;
    
    S s1;
    S s2(1);
    
    std::cout << s1.i << ":" << s2.i << "\n";
    
    auto fr = f();
    auto i = fr.begin();
    std::cout << "\n" << *i << "\n";
    
    std::string maybeEscapedNetName = "some string";
    const std::string && netName = (argc > 0 && argv[0][0] == '\\') ? 
        maybeEscapedNetName.substr(1,maybeEscapedNetName.size()-2) 
        : maybeEscapedNetName;

	std::cout << netName << "\n";
    std::cout << "finished\n";
	return 0;
}
