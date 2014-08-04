#include <unordered_map>

class MyClass {
public:
    MyClass(std::string const & foo, int bar) :
        my_foo(foo),
        my_bar(bar) {}
    MyClass(MyClass const&) = delete;
private:
    std::string my_foo;
    int my_bar;
};

int main()
{
    std::unordered_map<std::string, MyClass> map;
    map.emplace("foo", "bar", 2);
}
