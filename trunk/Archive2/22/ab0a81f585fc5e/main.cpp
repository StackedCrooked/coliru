#include <functional>
#include <iostream>

struct foo
{
    void fooFunc(){}
    int fooVar = 0;
};

void bar( foo& f, std::function<void(foo)> funcPtr, std::function<void(foo&, int)> fooVarSet )
{
    funcPtr( f );
    fooVarSet(f, 13);
}

void print_fooVar(foo& f, std::function<int(foo)> varAccess)
{
    std::cout << varAccess(f) << std::endl;
}

int main()
{
    foo f;
    bar(f, std::mem_fn(&foo::fooFunc), [](foo& f, int i) {f.fooVar = i;});
    std::cout << f.fooVar << std::endl;
    
    f.fooVar = 42;
    print_fooVar(f, std::mem_fn(&foo::fooVar));
}
