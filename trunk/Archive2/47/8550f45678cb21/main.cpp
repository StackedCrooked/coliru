#include <cstdio> 


template<typename T> void do_test(const T&) { printf("1"); }
template<typename T> void test(const T& t) { do_test(t); }

struct Item { };
namespace ns { struct Item {}; }

int main()
{
    test(ns::Item{});
    test(::Item{});
    test("Item");
}

void do_test(Item) { printf("2"); }
namespace ns { void do_test(Item) { printf("3"); } }

