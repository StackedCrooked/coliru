#include <cstdio>
#include <utility>

struct Ref
{
    Ref(int** value) : value(value) {}
    int** value;
};

struct Container
{
    Ref const operator [](int i) { return Ref(&value); }

    void push_back(Ref&&)      { printf("push_back(Ref&&)\n"); }
    void push_back(Ref const&) { printf("push_back(Ref const&)\n"); }

    int* value = nullptr;
};

namespace std
{
    Ref&& move(Ref const&& r) { return const_cast<Ref&&>(r); }
}

int main()
{
    Container c;
    c.push_back(c[0]);
    c.push_back(std::move(c[0]));
    return 0;
}
