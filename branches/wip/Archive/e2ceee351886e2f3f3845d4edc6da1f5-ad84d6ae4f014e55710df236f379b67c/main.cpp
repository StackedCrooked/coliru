class Empty
{};
class Derived4 : virtual public Empty
{
    char c;
};

void f(Derived4*) { }