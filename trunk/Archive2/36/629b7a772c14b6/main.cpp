#include <type_traits>                                                             
#include <string>
                                                                                
struct foo
{
    template<typename T>
    foo(T&& t)
    : t(std::forward<std::wstring>(t))
    {
        static_assert(std::is_convertible<T, std::wstring>::value, "");
    }
    
    std::wstring t;
};

int main()
{
    foo f1(L"test");
    foo f2(std::wstring{});
    foo f3(0);
}

