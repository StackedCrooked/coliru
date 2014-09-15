#include <algorithm>

class Obj
{
    int *p;
    void swap(Obj& left, Obj& right);

public:
    Obj(int x = 0) : p(new int(x)) {}
    Obj(const Obj& s);
    Obj(Obj&& s);
    Obj& operator = (Obj s);
    ~Obj() { delete p; }
};

Obj::Obj(const Obj& source) : p(new int(*source.p))
{}

Obj::Obj(Obj&& source) : p(source.p)
{
    source.p = nullptr;
}

void Obj::swap(Obj& left, Obj& right)
{
    std::swap(left.p, right.p);
}

Obj& Obj::operator=(Obj source)
{
    swap(*this, source);
    return *this;
}

int main()
{
    Obj o1(5);
    Obj o2(o1);
    Obj o3(10);
    o1 = o3;
}