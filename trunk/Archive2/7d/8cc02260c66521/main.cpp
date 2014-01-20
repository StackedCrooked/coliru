#include <utility>

struct PtrClass
{
    int *p = nullptr;
    
    PtrClass()
    {
        p = new int;
    }
    
    PtrClass(PtrClass&& rhs) : p(rhs.p)
    {
        rhs.p = nullptr;
    }
    
    ~PtrClass()
    {
        delete p;
    }
};

void DefArgFunc(PtrClass x = {})
{
    PtrClass x2{std::move(x)};
}

int main()
{
    DefArgFunc();
    return 0;
}