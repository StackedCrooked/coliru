#include <cstdio>
#include <utility>

struct Ref
{
    Ref(int** value) : value(value) {}
    int** value;
};

struct Container
{
    Ref operator [](int i) { return Ref(&value); }

    void push_back(Ref&&)      { printf("push_back(Ref&&)\n"); }
    void push_back(Ref const&) { printf("push_back(Ref const&)\n"); }

    int* value = nullptr;
};

int main()
{
    Container c;
    c.push_back(c[0]);
    c.push_back(std::move(c[0]));
}
