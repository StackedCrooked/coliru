#include <iostream>
#include <tuple>
#include <functional>

struct Foo {};
struct Bar {};

struct NoDefault1 {
    NoDefault1(const Foo & a,const Bar & b)
    {}
    NoDefault1(const NoDefault1&) = default;
};

struct NoDefault2 {
    NoDefault2(const Foo& a,const Bar& b)
    {}
    NoDefault2(const NoDefault1&) = default;
};

// I'd wish to be able to do something like this:
/*template <class ... ARGS, class ... T>
void setData(std::tuple<ARGS ...> & t,T && ... v)
{
    t = std::make_tuple(ARGS { v ... } ...);
}*/

int main()
{
     //std::tuple<NoDefault1,NoDefault2> foo;
    // setData(foo,Foo{},Bar{});
}