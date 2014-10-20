#include <iterator>

using std::begin;
using std::end;

static const char data[] = "Hello world!";

struct X { 
    friend char const* begin(X const&)   { return data; }
    friend char const* end  (X const& x) { return data + sizeof(data); }
};

char const* begin(X const&)   { return data; }
char const* end  (X const& x) { return data + sizeof(data); }

#include <iostream>

int main()
{
    for (auto ch : X())
       std::cout << ch;
}