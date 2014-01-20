#include <iostream>
#include <string>
#include <vector>

enum Tag { A, B };

class Base {
public:
    static const std::string foo;
};

template<int E> class Templated;

template<> class Templated<Tag::A> : public Base {};
template<> class Templated<Tag::B> : public Base {};

const std::string Templated<Tag::A>::foo{ "bar" };
const std::string Templated<Tag::B>::foo{ "baz" };

int main()
{
    return 0;
}
