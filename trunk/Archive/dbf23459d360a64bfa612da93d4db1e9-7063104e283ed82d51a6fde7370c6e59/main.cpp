#include <vector>
#include <list>
#include <memory>
struct A
{
    std::vector<std::unique_ptr<int>> v;
};
int main()
{
    std::list<A> l;
    l.sort([](const A& a1, const A& a2){ return true; });
}
