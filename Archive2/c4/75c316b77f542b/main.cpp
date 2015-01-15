#include <map>
#include <utility>
#include <string>
#include <tuple>

using namespace std;

struct Foo
{
   Foo(double d, string s) {}
   Foo(const Foo&) = delete;
   Foo(Foo&&) = delete;
};

int main()
{
    std::map<int, Foo> m;
    
    m.emplace(std::piecewise_construct,
              std::forward_as_tuple(1),
              std::forward_as_tuple(2.3, "hello"));
}
