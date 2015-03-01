#include <iostream>
#include <string>
#include <vector>
#include <map>

struct foo{
    foo(){}
    foo(foo&& other){};
    foo& operator=(foo&& other) { return *this; }
    ~foo() {}

private:
    foo(const foo&) = delete;
    foo& operator= (const foo&) = delete;
};

int main()
{
    foo f;
    std::map<int, foo> leMap;
    leMap.emplace(1, std::move(f));
}
