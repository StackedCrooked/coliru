#include <boost/variant.hpp>

#include <iostream>

using namespace boost;

void foo() {
    std::cout << __FUNCTION__ << "\n";

    variant<int, std::string> v1 = 42;

    int& i1 = get<int>(v1); // returns by ref, valid
    i1 *= 2;

    // now v1 contains the updated integer value 84
    std::cout << "v1     = " << v1 << "\n";
}

void bar() {
    std::cout << __FUNCTION__ << "\n";
    std::string s = "hello";
    int answer = 42;

    variant<int&, std::string&> v2(s);
    get<std::string&>(v2) += " world"; // now s contains "hello world"

    variant<int&, std::string&> v3(answer);
    get<int&>(v3) *= 2; // now `answer` contains 84
    
    std::cout << "s      = '" << s      << "'\n";
    std::cout << "answer = "  << answer << "\n";
}

int main()
{
    foo();
    bar();
}
