struct S
{
    void foo() {}
};

template<typename FPtr>
union funcptr_buf
{
    FPtr fptr;
    char buf[sizeof(FPtr)];
};

template<typename FPtr>
funcptr_buf<FPtr> get_funcptr_buf(FPtr p)
{
    return {p};
}

#include <iostream>
int main()
{
    auto x = get_funcptr_buf(&S::foo);
    
    std::cout << std::hex;
    for(char c : x.buf) std::cout << (int)c << " ";
    std::cout << std::endl;
}
