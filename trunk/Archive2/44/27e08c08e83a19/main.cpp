#include <memory>
#include <vector>
#include <tuple>
using namespace std;

struct A
{
    A() {}
    vector<unique_ptr<int>> m;
    // A(A const&) = delete; // add this line is okay.
};

struct B
{
    tuple<A> t;
};

int main()
{
    A a;
    B b;
    return 0;
}
