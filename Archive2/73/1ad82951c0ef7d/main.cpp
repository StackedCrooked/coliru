#include <cstdio> 


template<typename T> void do_test(const T&) { puts("1"); }
template<typename T> void test(const T& t) { do_test(t); }

struct Item { };
namespace ns { struct Item {}; }

int main()
{
    test(ns::Item{});
    test(::Item{});
    test("Item");
}

void do_test(Item) { puts("2"); }
namespace ns { void do_test(Item) { puts("3"); } }

