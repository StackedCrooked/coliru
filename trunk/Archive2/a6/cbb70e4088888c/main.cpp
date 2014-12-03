#include <iostream>

class C
{
public:
    template<typename T>
    explicit C(T&& value) { init(std::forward<T>(value), typename std::is_integral<T>::type()); }

private:
    template<typename T>
    void init(T&& value, std::true_type) { std::cout << "integral" << std::endl; }
    template<typename T>
    void init(T&& value, std::false_type) { std::cout << "not integral" << std::endl; }
    
};

int main()
{
    C a(1);
    C b(1.0);
}