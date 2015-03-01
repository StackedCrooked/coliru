#include <iostream>
#include <string>
#include <vector>
#include <map>

struct foo{
    foo(){}
    foo(foo&& other){};
    foo operator=(foo&& other) { return other; }
    ~foo() {}

private:
    foo(const foo&);
    foo& operator= (const foo&);
};

int main()
{
    foo f;
    std::map<int, foo> leMap;
    leMap.insert(1, f);
}
