#include <iostream>
#include <type_traits>

class C
{
private:
    class integral {};
    class floatingpoint {};
    class cstring {};

    template<bool sw, typename T1, typename T2>
    using Sel = typename std::conditional<sw, T1, T2>::type;

    template<typename T>
    using Sel2 = Sel<std::is_convertible<T, char const*>::value, cstring, void>;
    template<typename T>
    using Sel1 = Sel<std::is_floating_point<T>::value, floatingpoint, Sel2<T>>;
    template<typename T>
    using SelectOverload = Sel<std::is_integral<T>::value, integral, Sel1<T>>;

public:
    template<typename T, typename Overload = SelectOverload<T>>
    explicit C(T&& value)
    {
        init(std::forward<T>(value), Overload());
    }

private:    
    template<typename T>
    void init(T&& value, integral)
    {
        std::cout << "integral" << std::endl;
    }
    
    template<typename T>
    void init(T&& value, floatingpoint)
    {
        std::cout << "floating point" << std::endl;
    }
    
    template<typename T>
    void init(T&& value, cstring)
    {
        std::cout << "cstring" << std::endl;
    }
};

int main()
{
    C z(0);
    C a(1);
    C b(1.0);
    C c("");
}

