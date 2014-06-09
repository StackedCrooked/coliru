#include <iostream>

using namespace std;

unsigned one = 0, two = 0, three = 1, four = 3;

template<typename F>
void for_each_occurrence_storage(F f)
{
    f("one", one); f("two", two); f("three", three); f("four", four);
}

struct Printer
{
    template<typename T>
    void operator()(const char *name, T x) const
    {
        cout << name << " : " << x << endl;
    }
};

int main()
{
    ++one;
    two = 2;
    three +=2;
    ++four;

    for_each_occurrence_storage(Printer());
}

