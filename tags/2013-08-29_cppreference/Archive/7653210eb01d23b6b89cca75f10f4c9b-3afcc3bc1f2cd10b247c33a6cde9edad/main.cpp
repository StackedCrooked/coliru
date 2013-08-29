#include <iostream>
#include <sstream>
#include <string>

class A
{
public:

    template<class T>
    void Input(const T&);

private:
    std::string result;
};

template<class T>
void A::Input(const T& obj)
{
    //Pass object to the stream
    std::ostringstream ss;
    ss << obj;

    //After this line, result == "" with size 1 (??), no matter the input
    result = ss.str();
    std::cout << result << ' ' << result.size() << '\n';

    int test = 1234;
    ss << test;

    //Even with a test int, result == "" with size 1 (???)
    result = ss.str();
    std::cout << result << ' ' << result.size() << '\n';
}

int main() {
    A a;
    a.Input(2.3);
}