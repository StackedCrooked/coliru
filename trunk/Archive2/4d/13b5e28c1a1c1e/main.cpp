#include <string>
#include <map>

struct foo
{
    std::string a,b,c;
    foo(foo const&)=delete;
    foo(foo&&)=default;
    template<typename...T> foo(T&&...) {}
};


template<typename...T>
void add_foo(std::map<std::string,foo>& map, const char*name, T&&...args)
{
    map.emplace(std::piecewise_construct,      // how? perhaps like this?
            std::forward_as_tuple(name),   //   no:
            std::forward_as_tuple(args...));  //   error here
}

int main()
{
    std::map<std::string,foo> m;
    add_foo(m, "a", "b", "c");
}
